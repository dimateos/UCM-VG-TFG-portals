#include "SampleScene.h"

#include "../LogicNodes/ShapeNode.h"
#include "../LogicNodes/InputFreeRotation.h"
#include "../LogicNodes/InputFreeMovement.h"

#include "../LogicNodes/ScreenPostProcessing.h"
#include "../Render/RenderTarget.h"

#include "../Render/Texture.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include "../Platform/Window_SDL_GL.h"
#include "../app.h"
#include <SDL_events.h>

#include "../Render/Viewport.h"
#include "../Render/Projection.h"
#include "../Logic/Camera.h"

//some testing cor oblique
#include <gtx/string_cast.hpp>
#include <iostream>

#include <math.h> //for atan

SampleScene::SampleScene(App* app) : Scene(app) {}

SampleScene::~SampleScene() {
	//delete all new
}

bool SampleScene::init() {
	Scene::init();
	glDepthFunc(GL_LESS);

	//glDisable(GL_CULL_FACE); //cube not correct vertices atm
	//glEnable(GL_CULL_FACE);

	//SCENE INPUT
	Platform_SDL::platformEventEmitter_.registerListener(this);
	Platform_SDL::keyEventEmitter_.registerListener(this);
	Platform_SDL::mouseButtonEventEmitter_.registerListener(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//TARGETS
	screenVP_ = new Viewport(Window_SDL_GL::getWidth(), Window_SDL_GL::getHeight());
	miniViewVP_ = new Viewport(Window_SDL_GL::getWidth() * miniViewScale_, Window_SDL_GL::getHeight() * miniViewScale_);
	float resPF = 2.0f; //PostFiltering multi/down sampling
	postProcessVP_ = new Viewport(Window_SDL_GL::getWidth() * resPF, Window_SDL_GL::getHeight() * resPF);

	screenRT_ = new RenderTarget();
	screenRT_->setDefault(screenVP_);
	postProcessRT_ = new RenderTarget();
	postProcessRT_->create(postProcessVP_);

	//FRAME BUFFERING
	screenPP_ = new ScreenPostProcessing(nullptr, postProcessRT_); //out of the tree

	//CAMERA
	proj_ = new PerspectiveProjection(screenVP_->getAspect(), projFov_, projNear_, projFar_); //affects clipping on portal pannels
	cam_ = new Camera(proj_);
	Node::ROOT_CAM = cam_;
	topDownProj_ = new OrthoProjection(topDownW_, topDownW_ / screenVP_->getAspect(), topDownZoom_, projNear_, projFar_);
	topDownCam_ = new Camera(topDownProj_);
	topDownCam_->setLocalPos(topDownPos_);
	topDownCam_->rotate(-90, Transformation::BASE_RIGHT);

	//extra projections for testing
	obliquePorj_ = new PerspectiveProjection(screenVP_->getAspect(), projFov_, projNear_, projFar_);
	//modifyProjectionMatrixOptPers(p, glm::vec4());

	//AVOIDING CAMERA CLIPPING PORTALS
	initialNear_ = ((PerspectiveProjection*)proj_)->near;

	//calculating all plane points (do not need all the info but atm nice to check)
	float fovY = ((PerspectiveProjection*)proj_)->fov;
	float angleYHalf = glm::radians(fovY) / 2;

	//nearTop / near = tan(angleYHalf) and then aspect ratio to get nearRight
	float nearTop = tanf(angleYHalf) * initialNear_;
	float nearRight = nearTop * ((PerspectiveProjection*)proj_)->aspect;
	float farTop = tanf(angleYHalf) * proj_->far;
	float farRight = farTop * ((PerspectiveProjection*)proj_)->aspect;

	//calculate fov X: nearRight / near = tan(angleXHalf) so angleXHalf = atan(nearRight / near)
	float angleXHalf = atanf(nearRight / initialNear_);
	float fovX = glm::degrees(angleXHalf * 2);

	//maximun possible near corner distance + a little epsilon
	initialNearCornerDistance_ = glm::length(glm::vec3(nearTop, nearRight, initialNear_)) + 10*EPSILON;

	//RECURSION STUFF
	recTrans_.resize(REC_HARD_LIMIT);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//COMMON TEXTURES AND MATERIALS
	//really badly placed here but for now

	Texture::setFlipVerticallyOnLoad(); //texture loading
	checkersTex_.load("../Assets/checker_gray.bmp", GL_TEXTURE_2D);
	blankTex_.load("../Assets/blank_white.bmp", GL_TEXTURE_2D);

	SolidMaterial::SOLID_MAT_SHADER.build("../Shaders/V_3D_UVoptions.glsl", "../Shaders/F_solid_UVoptions.glsl");
	SolidMaterial::SOLID_MAT_SHADER.bind();
	SolidMaterial::UNIFORM_COLOR = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("color");
	SolidMaterial::UNIFORM_OPTION = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("option");
	SolidMaterial::SOLID_MAT_SHADER.setInt("texture0", 0);

	uniformModel_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("model");
	uniformView_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("view");
	uniformProj_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("projection");
	uniformPreModel_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("preModel");

	printf("UNIFORM - uniformModel_ %i\n", uniformModel_);
	printf("UNIFORM - uniformView_ %i\n", uniformView_);
	printf("UNIFORM - uniformProj_ %i\n", uniformProj_);
	printf("UNIFORM - uniformPreModel_ %i\n", uniformPreModel_);
	printf("UNIFORM - SolidMaterial::UNIFORM_COLOR %i\n", SolidMaterial::UNIFORM_COLOR);
	printf("UNIFORM - SolidMaterial::UNIFORM_OPTION %i\n", SolidMaterial::UNIFORM_OPTION);

	//COMMON meshes and materials
	cubeMesh_ = new CubeMesh();
	planeMesh_ = new PlaneMesh();
	redCheckerMat_ = new SolidMaterial(glm::vec3(0.8f, 0.2f, 0.2f), &checkersTex_);
	auto orangeCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.4f, 0.2f), &checkersTex_);
	auto blueCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.2f, 0.8f), &checkersTex_);
	auto cyanCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.8f), &checkersTex_);
	auto greenCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.2f), &checkersTex_);
	auto whiteCheckerMat = new SolidMaterial(glm::vec3(0.9f), &checkersTex_);
	auto grayCheckerMat = new SolidMaterial(glm::vec3(0.3f), &checkersTex_);

	auto axisMesh = new AxisMesh();
	pinkMat_ = new SolidMaterial(glm::vec3(0.9f, 0.3f, 0.6f), &blankTex_);

	//REFERENCE AXIS
	Node::ROOT_AXIS = new ShapeNode(nullptr, axisMesh, pinkMat_);
	auto axisSon = new Node(Node::ROOT_AXIS);
	axisSon->scale(0.25f);
	float f = 1.0f / axisSon->getLocalScaleX();
	auto cubeRight = new ShapeNode(axisSon, cubeMesh_, redCheckerMat_);
	cubeRight->translate(Transformation::BASE_RIGHT * f);
	auto cubeUp = new ShapeNode(axisSon, cubeMesh_, greenCheckerMat);
	cubeUp->translate(Transformation::BASE_UP * f);
	auto cubeBack = new ShapeNode(axisSon, cubeMesh_, blueCheckerMat);
	cubeBack->translate(Transformation::BASE_BACK * f);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//RENDER PANEL
	//auto whiteFloor = new ShapeNode(world_node_, cubeMesh_, whiteCheckerMat);
	//whiteFloor->removeFather();
	//whiteFloor->setLocalScale(glm::vec3(15.0f, 0.1f, 15.0f));
	//whiteFloor->setLocalPos(glm::vec3(5.0f, -0.5f, 18.0f));

	renderPanelRT_ = new RenderTarget();
	renderPanelRT_->create(postProcessVP_);
	renderTex_ = new Texture();
	renderTex_->createRenderTargetTexture(renderPanelRT_);
	renderMat_ = new SolidMaterial(glm::vec3(0.9f), renderTex_);

	renderPanel_ = new ShapeNode(world_node_, planeMesh_, renderMat_);
	renderPanel_->removeFather();
	renderPanel_->setLocalPos(glm::vec3(5, 2, -4));
	renderPanel_->setLocalScale(glm::vec3(2, 2, 1));

	//OTHER TESTING OBJECTS

	axis_ = new Node(world_node_);
	axis_->setLocalPos(glm::vec3(14, -0.5, 10.));
	axis_->scale(0.75);
	axis_->setDrawingAxis();

	//simple cube
	//auto cube = new ShapeNode(world_node_);
	//cube->setLocalPos(glm::vec3(2.f, 0.f, 0.f));
	//cube->setLocalScaleY(2.0f);
	//cube->pitch(180.0f);
	//cube->yaw(90.0f);

	//transforming a father to see how transforms chain
	//auto cubeFather = new Node(world_node_);
	//cubeFather->setLocalPos(glm::vec3(1.f, 1.f, 1.f));
	//cubeFather->yaw(45.0f);
	//cubeFather->setLocalScaleY(0.5f);
	//actualy set the father in order to see results
	//cube->setFather(cubeFather);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//BLUE PORTAL
	bPortalRT_ = new RenderTarget();
	bPortalRT_->create(postProcessVP_);
	bPortalTex_ = new Texture();
	bPortalTex_->createRenderTargetTexture(bPortalRT_);
	bPortalMat_ = new SolidMaterial(glm::vec3(1.0f), bPortalTex_);
	bPortalMat_->option_ = 1;

	bPortalRoot_ = new Node(world_node_);
	//bPortalRoot_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalRoot_->translateY(0.865);
	bPortalRoot_->translateZ(4);
	//bPortalRoot_->yaw(180.f);

	bPortalSurface_ = new ShapeNode(bPortalRoot_, cubeMesh_, bPortalMat_);
	//bPortalSurface_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalSurface_->setLocalScale(glm::vec3(2.62, 2.62, EPSILON));
	bPortalSurface_->setLocalPosZ(-bPortalSurface_->getLocalScaleZ() * 0.5);
	sqCloseDistance_ = bPortalSurface_->getLocalScaleX() * 0.5 + minPlayerWidth_ * 0.5;
	sqCloseDistance_ *= sqCloseDistance_;

	bPortalFrames_ = new Node(bPortalRoot_);
	//bPortalFrames_->removeFather();
	bPortalFrames_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalFrames_->scale(0.25f);
	float separation = 1.5f / bPortalFrames_->getLocalScaleX();
	float rescale = 3 / bPortalFrames_->getLocalScaleX();
	auto bPortalBorderL = new ShapeNode(bPortalFrames_, cubeMesh_, blueCheckerMat);
	bPortalBorderL->translate(-Transformation::BASE_RIGHT * separation);
	bPortalBorderL->setLocalScaleY(rescale);
	auto bPortalBorderR = bPortalBorderL->getCopy();
	bPortalBorderR->translate(2.0f*Transformation::BASE_RIGHT * separation);
	auto bPortalBorderU = new ShapeNode(bPortalFrames_, cubeMesh_, blueCheckerMat);
	bPortalBorderU->translate(Transformation::BASE_UP * separation);
	bPortalBorderU->setLocalScaleX(rescale);
	bPortalFramesBot_ = bPortalBorderU->getCopy();
	bPortalFramesBot_->translate(2.0f * -Transformation::BASE_UP * separation);

	//RED PORTAL (mostly copies)
	rPortalPanelRT_ = new RenderTarget();
	rPortalPanelRT_->create(screenVP_);
	rPortalTex_ = new Texture();
	rPortalTex_->createRenderTargetTexture(rPortalPanelRT_);
	rPortalMat_ = new SolidMaterial(glm::vec3(1.0f), rPortalTex_);
	rPortalMat_->option_ = 1;

	rPortalRoot_ = bPortalRoot_->getCopy();
	//rPortalRoot_->mesh_ = nullptr;
	rPortalRoot_->translateX(10);
	//rPortalRoot_->yaw(180.f);
	//bPortalRoot_->translateZ(6);
	//rPortalRoot_->pitch(180.f);

	//need to set blue materials
	auto childs = rPortalRoot_->getChildren();
	rPortalSurface_ = (ShapeNode*)childs.front();
	rPortalSurface_ ->mat_ = rPortalMat_;
	rPortalSurface_->setLocalScaleZ(minPortalWidth_);
	rPortalFrames_ = (ShapeNode*)childs.back();
	for (auto & n : rPortalFrames_->getChildren()) ((ShapeNode*)n)->mat_ = redCheckerMat_;
	rPortalFramesBot_ = rPortalFrames_->getChildren().back();

	//default non active
	bPortalFramesBot_->removeFather();
	rPortalFramesBot_->removeFather();

	//FORWARD POINT FOR PORTALS
	////Blue
	//auto bPortalBorderF = new ShapeNode(bPortalFrames_, cubeMesh_, cyanCheckerMat);
	//bPortalBorderF->translate(Transformation::BASE_UP * separation);
	//bPortalBorderF->translateZ(-0.55);
	//bPortalBorderF->scale(0.70);
	//bPortalBorderF->setLocalScaleZ(2);
	////Red copy
	//auto rPortalBorderF = bPortalBorderF->getCopy();
	//rPortalBorderF->setFather(rPortalFrames_);
	//((ShapeNode*)rPortalBorderF)->mat_ = orangeCheckerMat;

	//SCENE OBJECTS
	wall_ = new ShapeNode(world_node_, cubeMesh_, whiteCheckerMat);
	wall_->removeFather();
	wall_->setLocalPos(bPortalRoot_->getLocalPos());
	//wall_->translateX(5);
	wall_->translateZ(-0.45);
	wall_->setLocalScale(glm::vec3(10.0f, 10.0f, 0.5f));

	midWall_ = new ShapeNode(world_node_, cubeMesh_, whiteCheckerMat);
	midWall_->removeFather();
	midWall_->setLocalPos(bPortalRoot_->getLocalPos());
	midWall_->translateX(5);
	midWall_->setLocalScale(glm::vec3(0.5f, 10.0f, 16.0f));

	redCube_ = new ShapeNode(world_node_, cubeMesh_, redCheckerMat_);
	//redCube_->translateZ(1.0f);
	//redCube->setDrawingAxis();
	auto redFloor = new ShapeNode(world_node_, cubeMesh_, orangeCheckerMat);
	redFloor->setLocalScale(glm::vec3(7.f, 0.1f, 12.f));
	redFloor->setLocalPos(glm::vec3(0.0f, -0.5f, 4.0f));

	auto blueCube = (ShapeNode*)redCube_->getCopy();
	blueCube->mat_ = blueCheckerMat;
	blueCube->translateX(10.0f);
	auto blueFloor = (ShapeNode*)redFloor->getCopy();
	blueFloor->mat_ = cyanCheckerMat;
	blueFloor->translateX(10.0f);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//PLAYER
	player_ = new Node(world_node_);
	player_->setLocalPos(glm::vec3(0.f, 0.f, 8.f));
	//playerPrevTrans_ = player_->getLocalTrans();
	//player_->yaw(-90);
	//player->yaw(20);
	//player->scale(0.8f);

	//special material for slizing
	SolidMaterial::UNIFORM_CLIP_PLANE = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("clipPlane");
	slizableMat_ = new SolidMaterial(grayCheckerMat->color_, &checkersTex_);

	playerBody_ = new ShapeNode(player_, cubeMesh_, slizableMat_);
	//playerBody_->removeFather();
	playerBody_->scale(minPlayerWidth_);
	//playerBody_->setLocalScaleZ(4); //test longer slice

	//COPY for slicing
	playerCopy_ = new Node(world_node_);
	playerCopy_->removeFather();
	playerBodyCopy_ = (ShapeNode*)playerBody_->getCopy();
	playerCopy_->addChild(playerBodyCopy_);
	//separated copy material
	slizableMatCopy_ = new SolidMaterial(greenCheckerMat->color_, &checkersTex_);
	slizableMatCopy_->option_ = 2;
	((ShapeNode*)playerBodyCopy_)->mat_ = slizableMatCopy_;

	//edit camera
	cam_->setFather(player_);
	cam_->setLocalPos(glm::vec3(0.f, 1.f, 0.f));

	//INPUT
	movController_ = new InputFreeMovement(world_node_, player_, cam_, false);
	rotController_ = new InputFreeRotation(world_node_, cam_);

	rPortalController_ = new InputFreeMovement(nullptr, rPortalRoot_, rPortalRoot_, false);
	bPortalController_ = new InputFreeMovement(nullptr, bPortalRoot_, bPortalRoot_, false);
	topDownController_ = new InputFreeMovement(nullptr, topDownCam_, topDownCam_, false);

	//interesing points
	movController_->setCoolTrans({ player_->getLocalPos() + glm::vec3(0.f, 0.f, -4.f), Transformation::BASE_ROT, Transformation::BASE_SCALE });
	rPortalController_->setCoolTrans({ rPortalRoot_->getLocalPos() + glm::vec3(-10.f, 0.f, 3.f), Transformation::BASE_ROT, Transformation::BASE_SCALE });
	bPortalController_->setCoolTrans({ bPortalRoot_->getLocalPos() + glm::vec3(0.f, 0.f, -3.f), Transformation::BASE_ROT, Transformation::BASE_SCALE });
	//topDownController_->setCoolTrans({ glm::vec3(19.455059f, 20.734728f, 27.141794f), glm::quat(0.830934f, -0.303777f, 0.261075f, -0.092868f), Transformation::BASE_SCALE });
	topDownController_->setCoolTrans({glm::vec3(27.712460, 20.734728, 34.419983), glm::quat(0.831990, -0.242491, 0.318808, 0.082880), Transformation::BASE_SCALE });

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//testing oblique projections
	//auto camBody_ = new ShapeNode(cam_, cubeMesh_, whiteCheckerMat);
	//camBody_->scale(0.25f);
	//camBody_->setLocalPos(glm::vec3(0.f, 0.f, -5.f));
	//camBody_->yaw(89);

	//auto fore = -camBody_->back();
	//auto clipPlane = glm::vec4(
	//	fore.x, fore.y, fore.z, glm::dot(-fore, camBody_->getLocalPos())
	//);

	//obliquePorj_->updateProjMatrix();
	//auto copy = obliquePorj_->computedProjMatrix_;
	//std::cout << "test:" << glm::to_string(obliquePorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy[2]) << std::endl << std::endl;

	//std::cout << "test:" << glm::to_string(obliquePorj_->computedProjMatrix_) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy) << std::endl << std::endl;

	//modifyProjectionMatrixOptPers(obliquePorj_->computedProjMatrix_, clipPlane);
	//modifyProjectionMatrix(copy, clipPlane);
	//std::cout << "test:" << glm::to_string(obliquePorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy[2]) << std::endl << std::endl;

	//std::cout << "test:" << glm::to_string(obliquePorj_->computedProjMatrix_) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy) << std::endl << std::endl;

	//obliquePorj_->updateProjMatrix();
	//std::cout << "base:" << glm::to_string(obliquePorj_->computedProjMatrix_) << std::endl << std::endl;

	//obliquePorj_->near = 5.0;
	//obliquePorj_->updateProjMatrix();
	//std::cout << "5.0n:" << glm::to_string(obliquePorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "5.0n:" << glm::to_string(obliquePorj_->computedProjMatrix_) << std::endl << std::endl;
	//modifyProjectionMatrixOptPers(obliquePorj_->computedProjMatrix_, clipPlane);

	//PORTAL EXTRA CAMERAS
	bPortalCam_ = new Camera(proj_);
	bPortalCam_->setFather(rPortalRoot_);
	bPortalCam_->setDrawingAxis(false);

	rPortalCam_ = new Camera(proj_);
	rPortalCam_->setFather(bPortalRoot_);
	rPortalCam_->setDrawingAxis(false);

	return true;
}

bool SampleScene::handleEvent(SDL_Event const & e) {
	//quit
	if (e.type == SDL_QUIT) {
		app_->stop();
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == GlobalConfig::ACTION_escape) {
		app_->stop();
		return true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_MIDDLE) {
		((PerspectiveProjection*)proj_)->fov = projFov_ = 80.0f;
		proj_->updateProjMatrix();
		printf("MOUSE - reset zoom\n");
	}

	//mouse wheel zoom
	else if (e.type == SDL_MOUSEWHEEL) {
		projFov_ += -e.wheel.y * fovIncrement_;
		if (projFov_ > HARD_MAX_projFov_) projFov_ = HARD_MAX_projFov_;
		else if (projFov_ < HARD_MIN_projFov_) projFov_ = HARD_MIN_projFov_;

		((PerspectiveProjection*)proj_)->fov = projFov_;
		proj_->updateProjMatrix();
		return true;
	}

	bool down = e.type == SDL_KEYDOWN;
	SDL_Keycode key = e.key.keysym.sym;
	bool handled = true; //expected handled

	//Delegated to other nodes:
		//Movement + rotation (+ reset)
		//Camera movement + capture/free cursor
		//Switch post-processing effect

	//not handling any up atm
	if (!down) {
		if (e.type == SDL_KEYUP && key == lastKey_) lastKey_ = 0; //reset last key on up
		return false;
	}

	//postprocess control
	if (lastKey_ == GlobalConfig::ACTION_screenPostFilterPortal) return false;
	else if (key == GlobalConfig::ACTION_screenPostFilterPortal) lastKey_ = key;

	//other event requiring multiple keys
	else if (key == GlobalConfig::ACTION_screenPostFilterGlobal) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editPlayerWidth) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editPortalRec) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editPortalRecSteps) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editPortalWidth) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editTopDownZoom) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_editMiniViewScale) lastKey_ = key;
	else if (key == GlobalConfig::ACTION_switchPortalProblems) lastKey_ = key;

	//switch main cameras (fps or top-down)
	else if (key == GlobalConfig::ACTION_switchMainCameras) {
		renderMainTopDown_ = !renderMainTopDown_;
		//movController_->setTarget(player_, renderMainTopDown_? player_ : cam_);
		if (renderMainTopDown_) rendeMiniView_ = true;
	}
	else if (key == GlobalConfig::ACTION_toggleMiniView) {
		rendeMiniView_ = !rendeMiniView_;
		//movController_->setTarget(player_, renderMainTopDown_ ? player_ : cam_);
	}

	//global postprocessing (0-9 numbers) and other actions holding screen key
	else if (lastKey_ == GlobalConfig::ACTION_screenPostFilterGlobal) {
		if (key >= SDLK_0 && key <= SDLK_9) {
			scenePPoption_ = key - SDLK_0 == scenePPoption_ ? 0 : key - SDLK_0;
			scenePPoption_pre_ = -1;
			printf("SCREEN - set postprocessing %i\n", scenePPoption_);
		}
		//move 3 objects to cool pos
		else if (key == GlobalConfig::ACTION_COOLtransform) {
			movController_->gotoCoolTrans();
			rPortalController_->gotoCoolTrans();
			bPortalController_->gotoCoolTrans();
		}
		//start/stop controling the top down view
		else if (lastKey_ == GlobalConfig::ACTION_screenPostFilterGlobal) {
				if (topDownController_->getFather() == nullptr) {
					printf("control set to TOPDOWN CAM\n");
					topDownController_->setInitialTrans(world_node_);
					movController_->removeFather();
					rPortalController_->removeFather();
					bPortalController_->removeFather();
				}
				else {
					printf("control set to PLAYER\n");
					movController_->setInitialTrans(topDownController_->removeFather());
				}
			}
	}
	else if (key == GlobalConfig::ACTION_screenPostFilterFrame) {
		scenePPoption_ = scenePPoption_ == 5 ? 0 : 5;
		scenePPoption_pre_ = -1;
		printf("SCREEN - set postprocessing %i\n", scenePPoption_);
		rotController_->setBlocked(scenePPoption_ == 5);
	}

	//switch portal problems (show effects and fixes)
	else if (lastKey_ == GlobalConfig::ACTION_switchPortalProblems) {
		//show/hide virtual portal cameras axes
		if (key == GlobalConfig::ACTION_togglePortalCameraAxis) {
			cam_->toggleDrawingAxis();
			rPortalCam_->toggleDrawingAxis();
			bPortalCam_->toggleDrawingAxis();
			printf("AXIS - toggle cam showing axis [%s]\n", cam_->isDrawingAxis() ? "TRUE" : "FALSE");
		}

		else if (key == SDLK_1) {
			bPortalMat_->option_ == 0 ? bPortalMat_->option_ = 1 : bPortalMat_->option_ = 0;
			rPortalMat_->option_ == 0 ? rPortalMat_->option_ = 1 : rPortalMat_->option_ = 0;
			printf("PORTAL - toggle rendering screen coords [%s]\n", bPortalMat_->option_ == 1 ? "TRUE" : "FALSE");
		}
		else if (key == SDLK_2) {
			avoidCameraClip_ = !avoidCameraClip_;
			printf("PORTAL - toggle camera clip fix [%s]\n", avoidCameraClip_ ? "TRUE" : "FALSE");
		}
		else if (key == SDLK_3) {
			useObliqueProjection_ = !useObliqueProjection_;
			printf("PORTAL - toggle oblique projection clipping [%s]\n", useObliqueProjection_ ? "TRUE" : "FALSE");
		}
		else if (key == SDLK_4) {
			useSliceCopy_ = !useSliceCopy_;
			printf("PORTAL - toggle slice copy [%s]\n", useSliceCopy_ ? "TRUE" : "FALSE");
			playerBodyCopy_->setFather(useSliceCopy_ ? playerCopy_ : nullptr);
		}
		else if (key == SDLK_5) {
			cutSliceCopy_ = !cutSliceCopy_;
			printf("PORTAL - toggle CUT slice copy [%s]\n", cutSliceCopy_ ? "TRUE" : "FALSE");
			slizableMatCopy_->option_ = cutSliceCopy_ ? 2 : 0;
			slizableMat_->option_ = cutSliceCopy_ ? 2 : 0;
		}
		else if (key == SDLK_6) {
			recMode_ = recMode_ == MAPWHOLE ? STANDARD : MAPWHOLE;
			printf("PORTAL - render rec set to [%s]\n", recMode_ == STANDARD ? "STANDARD" : "MAPWHOLE");
		}
		else if (key == SDLK_7) {
			recMode_ = recMode_ == MAPFIX ? STANDARD : MAPFIX;
			printf("PORTAL - render rec set to [%s]\n", recMode_ == STANDARD ? "STANDARD" : "MAPFIX");
		}
		else if (key == SDLK_8) {
			recMode_ = recMode_ == MAPPREV ? STANDARD : MAPPREV;
			printf("PORTAL - render rec set to [%s]\n", recMode_ == STANDARD ? "STANDARD" : "MAPPREV");
		}
	}

	//start/stop controling the portal to move/rotate it locally
	else if (key == GlobalConfig::ACTION_switchControl) {
		if (movController_->getFather() != nullptr) rPortalController_->setInitialTrans(movController_->removeFather());
		else if (rPortalController_->getFather() != nullptr) bPortalController_->setInitialTrans(rPortalController_->removeFather());
		else {
			printf("control set to PLAYER\n");
			bPortalController_->removeFather();
			topDownController_->removeFather();
			movController_->setInitialTrans(world_node_);
		}
	}
	//switch between camera positions
	else if (key == GlobalConfig::ACTION_cycleBlueCamPos) {
		printf("CAM - toggle BLUE cam position\n");
		if (Node::ROOT_CAM != bPortalCam_) Node::ROOT_CAM = bPortalCam_;
		else Node::ROOT_CAM = cam_;
		setActivePortalSurfaces(Node::ROOT_CAM != bPortalCam_);
	}
	else if (key == GlobalConfig::ACTION_cycleRedCamPos) {
		printf("CAM - toggle RED cam position\n");
		if (Node::ROOT_CAM != rPortalCam_) Node::ROOT_CAM = rPortalCam_;
		else Node::ROOT_CAM = cam_;
		setActivePortalSurfaces(Node::ROOT_CAM != rPortalCam_);
	}

	//show/hide virtual portal cameras axes
	else if (key == GlobalConfig::ACTION_togglePortalCameraAxis) {
		if (lastKey_ == GlobalConfig::ACTION_editPlayerWidth) {
			playerBody_->setFather(playerBody_->getFather() == nullptr ? player_ : nullptr);
			printf("PLAYER - hidden body [%s]\n", playerBody_->getFather() == nullptr ? "TRUE" : "FALSE");
		}
		else {
			playerBody_->toggleDrawingAxis();
			bPortalFrames_->toggleDrawingAxis();
			rPortalFrames_->toggleDrawingAxis();
			printf("AXIS - toggle objects showing axis [%s]\n", playerBody_->isDrawingAxis() ? "TRUE" : "FALSE");
		}
	}

	//toggle objects
	else if (key == GlobalConfig::ACTION_togglePortalSurfaces) {
		setActivePortalSurfaces(bPortalSurface_->getFather() == nullptr);
	}
	else if (key == GlobalConfig::ACTION_togglePortalFrames) {
		bPortalFrames_->setFather(bPortalFrames_->getFather() == nullptr ? bPortalRoot_ : nullptr);
		rPortalFrames_->setFather(rPortalFrames_->getFather() == nullptr ? rPortalRoot_ : nullptr);
		printf("OBJECT - toggle portal frames [%s]\n", bPortalFrames_->getFather() != nullptr ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_toggleRedCubeAxis) {
		redCube_->toggleDrawingAxis();
		printf("OBJECT - toggle redcube axis [%s]\n", redCube_->isDrawingAxis() ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_toggleRedCubePortal) {
		redCube_->mat_ = redCube_->mat_ == redCheckerMat_ ? rPortalMat_ : redCheckerMat_;
		printf("OBJECT - toggle redcube portal material [%s]\n", redCube_->mat_ == rPortalMat_ ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_togglePortalBottom) {
		rPortalFramesBot_->setFather(rPortalFramesBot_->getFather() == nullptr ? rPortalFrames_ : nullptr);
		bPortalFramesBot_->setFather(bPortalFramesBot_->getFather() == nullptr ? bPortalFrames_ : nullptr);
		printf("OBJECT - toggle portal bot frame [%s]\n", rPortalFramesBot_->getFather() != nullptr ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_togglePortalWall) {
		wall_->setFather(wall_->getFather() == nullptr ? world_node_ : nullptr);
		printf("OBJECT - toggle portal wall [%s]\n", wall_->getFather() != nullptr ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_toggleMidWall) {
		midWall_->setFather(midWall_->getFather() == nullptr ? world_node_ : nullptr);
		printf("OBJECT - toggle mid wall [%s]\n", midWall_->getFather() != nullptr ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_toggleRenderPanel) {
		renderPanel_->setFather(renderPanel_->getFather() == nullptr ? world_node_ : nullptr);
		printf("OBJECT - toggle render panel [%s]\n", renderPanel_->getFather() != nullptr ? "TRUE" : "FALSE");
	}
	else if (key == GlobalConfig::ACTION_toggleAxis) {
		axis_->setFather(axis_->getFather() == nullptr ? world_node_ : nullptr);
		printf("OBJECT - toggle axis [%s]\n", axis_->getFather() != nullptr ? "TRUE" : "FALSE");
	}

	//Increase / decrease
	else if (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS || key == SDLK_PLUS || key == SDLK_MINUS) {
		float s = (key == SDLK_KP_PLUS || key == SDLK_PLUS) ? 1.0f : -1.0f;

		//change player width
		if (lastKey_ == GlobalConfig::ACTION_editPlayerWidth) {
			minPlayerWidth_ += s * minPlayerIncrement_;
			if (minPlayerWidth_ < HARD_LIMIT_minPlayerWidth_) minPlayerWidth_ = HARD_LIMIT_minPlayerWidth_;
			//printf("scene - w: %f\n", minPlayerWidth_);

			playerBody_->setLocalScaleZ(minPlayerWidth_);
			playerBodyCopy_->setLocalScaleZ(minPlayerWidth_);
			sqCloseDistance_ = bPortalSurface_->getLocalScaleX() * 0.6 + minPlayerWidth_ * 0.6;
			sqCloseDistance_ *= sqCloseDistance_;
		}

		//change amount of recursion
		else if (lastKey_ == GlobalConfig::ACTION_editPortalRec) {
			recLimit_ += s;
			if (recLimit_ > REC_HARD_LIMIT) recLimit_ = REC_HARD_LIMIT;
			else if (recLimit_ == 0) recLimit_ = 1;

			recSteps_ += s;
			if (recSteps_ > recLimit_) recSteps_ = recLimit_;
			else if (recSteps_ == 0) recSteps_ = 1;
		}
		//change amount of recursion
		else if (lastKey_ == GlobalConfig::ACTION_editPortalRecSteps) {
			recSteps_ += s;
			if (recSteps_ > recLimit_) recSteps_ = recLimit_;
			else if (recSteps_ == 0) recSteps_ = 1;
		}

		//change portal width
		else if (lastKey_ == GlobalConfig::ACTION_editPortalWidth) {
			minPortalWidth_ += s*minPortalIncrement_;
			if (minPortalWidth_ < HARD_LIMIT_minPortalWidth_) minPortalWidth_ = HARD_LIMIT_minPortalWidth_;
			//printf("scene - w: %f\n", minPortalWidth_);

			bPortalSurface_->setLocalScaleZ(minPortalWidth_);
			rPortalSurface_->setLocalScaleZ(minPortalWidth_);
		}

		//change topdown zoom
		else if (lastKey_ == GlobalConfig::ACTION_editTopDownZoom) {
			topDownZoom_ += -s * viewScalesIncrement_;
			if (minPortalWidth_ < viewScalesIncrement_) minPortalWidth_ = viewScalesIncrement_;
			//printf("scene - w: %f\n", topDownZoom_);

			((OrthoProjection*)topDownProj_)->zoom = topDownZoom_;
			topDownProj_->updateProjMatrix();
		}
		//change mini view scale
		else if (lastKey_ == GlobalConfig::ACTION_editMiniViewScale) {
			miniViewScale_ += s * viewScalesIncrement_;
			if (miniViewScale_ < viewScalesIncrement_) miniViewScale_ = viewScalesIncrement_;
			//printf("scene - w: %f\n", miniViewScale_);

			miniViewVP_->setSize(Window_SDL_GL::getWidth() * miniViewScale_, Window_SDL_GL::getHeight() * miniViewScale_);
		}
	}

	else handled = false;

	//control postprocess (capture unhandled number keys events)
	if (key >= SDLK_0 && key <= SDLK_9) return true;

	//else printf("scene - ignored event type: %i\n", e.type);
	return handled;
}

void SampleScene::setActivePortalSurfaces(bool active) {
	bPortalSurface_->setFather(active ? bPortalRoot_ : nullptr);
	rPortalSurface_->setFather(active ? rPortalRoot_ : nullptr);
	printf("PORTAL - toggle active surfaces [%s]\n", active ? "TRUE" : "FALSE");

	//cancel current TP
	if (!active) {
		printf("PORTAL TP - cancel (disabled any sliced clone)\n");
		bSideOld_ = 0;
		rSideOld_ = 0;
		playerCopy_->removeFather();
		slizableMat_->option_ = 0;
		bPortalSurface_->setLocalScaleZ(minPortalWidth_);
		bPortalSurface_->setLocalPosZ(0);
		rPortalSurface_->setLocalScaleZ(minPortalWidth_);
		rPortalSurface_->setLocalPosZ(0);
	}
}

void SampleScene::avoidCameraClip() {
	//avoid clipping the portal plane - only when moving because we assume worst rotation
	//strategy A: reduce near distance - downside is editting the projection matrx too much
	//strategy B: portals are small scaled cubes with face cullling off so any clipping stays within the cube
		//done within portal tp checking
		//assume worst case and only tweak when entering / exitting portal close zone
	//strategy C: could be B but dynamically adjust scale to acually the amount the near plan clipped
		//probably not worth as the B works perfectly for coherently small near planes

	//check distance to portals
	glm::vec3 rCamOffset = player_->getLocalPos() + cam_->getLocalPos() - bPortalRoot_->getLocalPos();
	float rCamDot = glm::dot(rCamOffset, bPortalRoot_->back());

	float rCamDistance = glm::abs(rCamDot);
	float diff = rCamDistance - initialNearCornerDistance_;

	//near plane is too close
	if (diff <= 0) {
		//set proportionally smaller
		proj_->near = initialNear_ + (diff * 1.25f - EPSILON); //reduce by chunks and add EPSILON for diff==0 case
		if (proj_->near < EPSILON) proj_->near = 1E-5; //minimun

		proj_->updateProjMatrix();
		printf(" rCamDistance: %f - nearCornerDistance: %f - diff: %f - new near: %f\n", rCamDistance, initialNearCornerDistance_, diff, proj_->near);
	}
	//restore plane near
	else {
		proj_->near = initialNear_;
		proj_->updateProjMatrix();
	}
}

void SampleScene::updatePortalCamerasTrans() {
	//printf("scene - updating cameras \n");

	//get position in portal local coordinates of global player's (player camera position and rotation)
		//cam matrix by inverse of portal matrix
	//set position and rotation (decomposed from matrices atm) - ignoring scale atm
		//just set local cause atm the red portal cam is already child of blue portal
	rPortalCam_->setLocalTrans(Transformation::getDescomposed(rPortalRoot_->getModelMatrix_Inversed() * cam_->getModelMatrix()));

	//calculate recursion positions and rotations - for just 1 portal atm
	glm::mat4 camMat = cam_->getModelMatrix(), portalMat_inv = bPortalRoot_->getModelMatrix_Inversed(), portalMat_base = rPortalRoot_->getModelMatrix();

	//first recursion (last recursive trans) is the base one
	glm::mat4 combinedTrans = portalMat_inv * camMat;
	recTrans_[recLimit_ - 1] = Transformation::getDescomposed(combinedTrans);
	bPortalCam_->setLocalTrans(recTrans_[recLimit_ - 1]);

	for (size_t i = 1; i < recLimit_; i++) {
		int renderOrderIndex = recLimit_ - i - 1; //inversed order - from back to front
		startIndex_ = renderOrderIndex; //atm we do all the recursions

		//local coords in the base portal to global multiply by linked portal inverse and get again in local linked portal
		combinedTrans = portalMat_inv * portalMat_base * combinedTrans;
		recTrans_[renderOrderIndex] = Transformation::getDescomposed(combinedTrans);
	}
}

void SampleScene::updatePortalTravellers() {
	//printf("scene - checking tp \n");
	static int tpc = 0;

	//atm we ignore scale
	auto playerPos = player_->getLocalPos();

	//blue portal
	auto bPortalPos = bPortalRoot_->getLocalPos();
	glm::vec3 bPortalOffset = playerPos - bPortalPos;
	//close enough
	if (glm::length2(bPortalOffset) < sqCloseDistance_) {
		int side = sgn(glm::dot(bPortalOffset, -bPortalRoot_->back()));
		//printf(" blue S: %i - So: %i - off: %f %f %f\n", side, bSideOld_, bPortalOffset.x, bPortalOffset.y, bPortalOffset.z);

		//set clone position accordingly
		playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalRoot_->getModelMatrix() * bPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));

		//diff sides so tp
		if (side * bSideOld_ == -1) {
			onPortalTravel();
			printf("PORTAL TP - tp blue (%i)\n", ++tpc);
			//player_->setLocalPos(rPortalRoot_->getLocalPos() + bPortalOffset); //no correct rotation atm

			//set correct position and rotation (decomposed from matrices for now) - ignoring scale
			Transformation t = Transformation::getDescomposed(rPortalRoot_->getModelMatrix() * bPortalRoot_->getModelMatrix_Inversed() * cam_->getModelMatrix());
			//update player pos (although atm no tp chaining)
			playerPos = t.postion - cam_->getLocalPos();
			player_->setLocalPos(playerPos);
			rotController_->setInputRot(t.rotation);

			//invalid previous sides
			bSideOld_ = 0;
			bPortalSurface_->setLocalScaleZ(minPortalWidth_);
			bPortalSurface_->setLocalPosZ(0);

			//correct linked portal panel scale
			rSideOld_ = sgn(glm::dot(playerPos - rPortalRoot_->getLocalPos(), -rPortalRoot_->back()));
			if (avoidCameraClip_) {
				rPortalSurface_->setLocalScaleZ(initialNearCornerDistance_ + minPortalWidth_);
				rPortalSurface_->setLocalPosZ(rSideOld_ * rPortalSurface_->getLocalScaleZ() / 2);
			}
			//make player copy
			printf("PORTAL TP - red clone + disabled blue clone\n");
			playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalRoot_->getModelMatrix() * rPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(rSideOld_) * -rPortalRoot_->back(), normalCopy = float(rSideOld_) * bPortalRoot_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, rPortalRoot_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, bPortalRoot_->getLocalPos()));
		}
		else if (bSideOld_ == 0) { //store new valid side - just entered the zone
			bSideOld_ = side;
			//avoid clip strategy B - modify portal scale to fit clipping near plane
			if (avoidCameraClip_) {
				bPortalSurface_->setLocalScaleZ(initialNearCornerDistance_ + minPortalWidth_);
				bPortalSurface_->setLocalPosZ(side * bPortalSurface_->getLocalScaleZ() / 2);
			}

			//make player copy
			printf("PORTAL TP - blue clone\n");
			playerCopy_->setFather(world_node_);
			if (cutSliceCopy_) slizableMat_->option_ = 2;
			playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalRoot_->getModelMatrix() * bPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(side) * -bPortalRoot_->back(), normalCopy = float(side) * rPortalRoot_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, bPortalRoot_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, rPortalRoot_->getLocalPos()));
		}
	}
	else if (bSideOld_ != 0) { //player is out of zone so invalid previous
		bSideOld_ = 0;
		//avoid clip strategy B - modify portal scale to fit clipping near plane
		bPortalSurface_->setLocalScaleZ(minPortalWidth_);
		bPortalSurface_->setLocalPosZ(0);
		printf("PORTAL TP - disabled blue clone\n");
		playerCopy_->removeFather();
		slizableMat_->option_ = 0;
	}

	//red portal
	auto rPortalPos = rPortalRoot_->getLocalPos();
	glm::vec3 rPortalOffset = playerPos - rPortalPos;
	//close enough
	if (glm::length2(rPortalOffset) < sqCloseDistance_) {
		int side = sgn(glm::dot(rPortalOffset, -rPortalRoot_->back()));
		//printf(" red S: %i - So: %i - off: %f %f %f\n", side, rSideOld_, rPortalOffset.x, rPortalOffset.y, rPortalOffset.z);

		//set clone position accordingly
		playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalRoot_->getModelMatrix() * rPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));

		//diff sides so tp
		if (side * rSideOld_ == -1) {
			onPortalTravel();
			printf("PORTAL TP - tp blue (%i)\n", ++tpc);
			//set correct position and rotation (decomposed from matrices for now) - ignoring scale
			Transformation t = Transformation::getDescomposed(bPortalRoot_->getModelMatrix() * rPortalRoot_->getModelMatrix_Inversed() * cam_->getModelMatrix());
			playerPos = t.postion - cam_->getLocalPos();
			player_->setLocalPos(playerPos);
			rotController_->setInputRot(t.rotation);

			//invalid previous sides
			rSideOld_ = 0;
			rPortalSurface_->setLocalScaleZ(minPortalWidth_);
			rPortalSurface_->setLocalPosZ(0);

			//correct linked portal panel scale
			bSideOld_ = sgn(glm::dot(playerPos - bPortalRoot_->getLocalPos(), -bPortalRoot_->back()));
			if (avoidCameraClip_) {
				bPortalSurface_->setLocalScaleZ(initialNearCornerDistance_ + minPortalWidth_);
				bPortalSurface_->setLocalPosZ(bSideOld_ * bPortalSurface_->getLocalScaleZ() / 2);
			}
			//make player copy
			printf("PORTAL TP - blue clone + disabled red clone\n");
			playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalRoot_->getModelMatrix() * bPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(bSideOld_) * -bPortalRoot_->back(), normalCopy = float(bSideOld_) * rPortalRoot_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, bPortalRoot_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, rPortalRoot_->getLocalPos()));
		}
		else if (rSideOld_ == 0) { //store new valid side - just entered the zone
			rSideOld_ = side;
			//avoid clip strategy B - modify portal scale to fit clipping near plane
			if (avoidCameraClip_) {
				rPortalSurface_->setLocalScaleZ(initialNearCornerDistance_ + minPortalWidth_);
				rPortalSurface_->setLocalPosZ(side * rPortalSurface_->getLocalScaleZ() / 2);
			}

			//make player copy
			printf("PORTAL TP - red clone\n");
			playerCopy_->setFather(world_node_);
			if (cutSliceCopy_) slizableMat_->option_ = 2;
			playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalRoot_->getModelMatrix() * rPortalRoot_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(side) * -rPortalRoot_->back(), normalCopy = float(side) * bPortalRoot_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, rPortalRoot_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, bPortalRoot_->getLocalPos()));
		}
	}
	else if (rSideOld_ != 0) { //player is out of zone so invalid previous
		rSideOld_ = 0;
		//avoid clip strategy B - modify portal scale to fit clipping near plane
		rPortalSurface_->setLocalScaleZ(minPortalWidth_);
		rPortalSurface_->setLocalPosZ(0);
		printf("PORTAL TP - disabled red clone\n");
		playerCopy_->removeFather();
		slizableMat_->option_ = 0;
	}
}

void SampleScene::onPortalTravel() {
	if (scenePPoption_ == screenPP_->getOption()) {
		scenePPoption_ = scenePPoption_pre_;
	}
	else {
		scenePPoption_pre_ = scenePPoption_;
		scenePPoption_ = screenPP_->getOption();
	}
}

void SampleScene::update() {
	Scene::update();

	//atm done within portal checking (strategy B)
	//if (diffPos) avoidCameraClip();

	//check objects entering portal zone: handle tp
		//atm separated from player - handle portal scale to avoid camera near clip
	if (movController_->getFather() != nullptr && bPortalSurface_->getFather() != nullptr) updatePortalTravellers();

	//update camera matrices
	updatePortalCamerasTrans();
}

glm::vec4 SampleScene::getClipPlane(Transformation const & panelT, Transformation const & camT) {
	//oblique near plane for each portal camera (camera is child of plane - so just inverse values atm)
	//auto planeN = -rPortalRoot_->back(); //camera is child of plane so acually no
	auto planeN = -Transformation::BASE_BACK;

	//camera must always be behind plane so check so check dot
	//float side = fsgn(glm::dot(planeN, -bPortalCam_->back()));
	float side = fsgn(glm::dot(planeN, -camT.postion));

	//plane normal and position - use position to calculate Q
	auto camRot_i = glm::conjugate(camT.rotation);
	auto clipP = camRot_i * (-camT.postion);
	auto clipN = camRot_i * (side * planeN);

	float Q = glm::dot(-clipN, clipP);
	//printf(" Q: %f - S: %f - clipN: %f %f %f - clipP: %f %f %f\n", Q, side, clipN.x, clipN.y, clipN.z, clipP.x, clipP.y, clipP.z);
	return glm::vec4(clipN.x, clipN.y, clipN.z, Q);
}

void SampleScene::render() {
	if (renderMainTopDown_) render_TOPDOWN();
	else render_FPS();

	//SCREEN PASS - with the postfilters
	screenRT_->bind(false); //3d depth test disable (no need to clear the depth buffer)
	screenPP_->render(scenePPoption_);

	//MINI VIEW PASS
	if (!rendeMiniView_) return;

	if (renderMainTopDown_) render_FPS();
	else render_TOPDOWN();

	//SCREEN PASS - with the postfilters
	screenRT_->bind(false, miniViewVP_); //3d depth test d
	screenPP_->render(sceneMiniViewOption_);
}

void SampleScene::render_FPS() {
	rPortalSurface_->mesh_ = nullptr;
	bPortalSurface_->mesh_ = cubeMesh_;

	//char loggingBuffer_[200];
	//bPortalSurface_->getLocalTrans().toBuffer(loggingBuffer_);
	//printf("bPortalSurface_ T: %s\n", loggingBuffer_);
	//rPortalSurface_->getLocalTrans().toBuffer(loggingBuffer_);
	//printf("rPortalSurface_ T: %s\n", loggingBuffer_);

	//some recursion modes (show errors)
	if (recMode_ == STANDARD) bPortalSurface_->mat_ = pinkMat_;
	else {
		bPortalSurface_->mat_ = bPortalMat_;
		bPortalMat_->option_ = recMode_;
		if (recMode_ == MAPPREV) {
			SolidMaterial::SOLID_MAT_SHADER.bind(); //common shader
			glUniformMatrix4fv(uniformPreModel_, 1, GL_FALSE, rPortalSurface_->getModelMatrix_ptr());
		}
	}

	//atm only 1 portal has recursion (and atm do all recursions event outside screen)
	for (size_t i = 0; i < recLimit_; i++) {
		//RED PORTAL pass - draw scene in the reused postfilter buffer
		SolidMaterial::SOLID_MAT_SHADER.bind(); //common shader
		postProcessRT_->bind(true); //3d depth test enabled
		postProcessRT_->clear(clearColor.x, clearColor.y, clearColor.z, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the transformation in order
		bPortalCam_->setLocalTrans(recTrans_[i]);

		//calculate oblique plane
		if (useObliqueProjection_) {
			obliquePorj_->computedProjMatrix_ = proj_->computedProjMatrix_;
			modifyProjectionMatrixOptPers(obliquePorj_->computedProjMatrix_, getClipPlane(rPortalRoot_->getLocalTrans(), bPortalCam_->getLocalTrans()));
			//load the matrix and the restore it
			glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, obliquePorj_->getProjMatrixPtr());
		}
		else glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, proj_->getProjMatrixPtr());

		glUniformMatrix4fv(uniformView_, 1, GL_FALSE, bPortalCam_->getViewMatrixPtr());
		Scene::render(); //edited virtual render_rec

		//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
		bPortalRT_->bind(false);
		screenPP_->render();

		//pink only for final iteration + other recursion modes
		if (i == 0) {
			if (recMode_ != STANDARD) bPortalMat_->option_ = 1;
			else bPortalSurface_->mat_ = bPortalMat_;
		}

		//rec steps quick exit to show distant recursions only
		if (i == recSteps_-1) break;
	}

	//BLUE PORTAL pass - draw scene in the reused postfilter buffer
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)

	//oblique near plane for each portal camera (camera is child of plane - so just inverse values atm)
	if (useObliqueProjection_) {
		obliquePorj_->computedProjMatrix_ = proj_->computedProjMatrix_;
		modifyProjectionMatrixOptPers(obliquePorj_->computedProjMatrix_, getClipPlane(bPortalRoot_->getLocalTrans(), rPortalCam_->getLocalTrans()));
		glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, obliquePorj_->getProjMatrixPtr());
	}
	else glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, proj_->getProjMatrixPtr());

	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, rPortalCam_->getViewMatrixPtr());
	postProcessRT_->bind(true); //3d depth test enabled
	postProcessRT_->clear(clearColor.x, clearColor.y, clearColor.z, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bPortalSurface_->mesh_ = nullptr;
	rPortalSurface_->mesh_ = cubeMesh_;
	rPortalSurface_->mat_ = pinkMat_;
	Scene::render(); //edited virtual render_rec

	//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
	rPortalPanelRT_->bind(false);
	screenPP_->render();

	//FPS camera active
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)
	if (Node::ROOT_CAM == cam_) glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, proj_->getProjMatrixPtr());
	else {
		glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, obliquePorj_->getProjMatrixPtr());
		obliquePorj_->computedProjMatrix_ = proj_->computedProjMatrix_;
	}
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, Node::ROOT_CAM->getViewMatrixPtr());

	bPortalSurface_->mesh_ = cubeMesh_;
	rPortalSurface_->mesh_ = cubeMesh_;
	bPortalSurface_->mat_ = bPortalMat_;
	rPortalSurface_->mat_ = rPortalMat_;

	//LAST PASS - all the portals have view textures
	postProcessRT_->bind(true); //3d depth test enabled
	postProcessRT_->clear(clearColor.x, clearColor.y, clearColor.z, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::render(); //edited virtual render_rec

	//EXTRA PASS - copy texture for the render panel (avoid writing and reading same buffer)
	//no need of model uniform in the shaders - nor camera matrices
	renderPanelRT_->bind(false);
	screenPP_->render();
}

void SampleScene::render_TOPDOWN() {
	//TOP DOWN camera active
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)
	glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, topDownProj_->getProjMatrixPtr());
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, topDownCam_->getViewMatrixPtr());

	bPortalSurface_->mesh_ = nullptr;
	rPortalSurface_->mesh_ = nullptr;

	//LAST PASS - all the portals have view textures
	postProcessRT_->bind(true); //3d depth test enabled
	postProcessRT_->clear(clearColor.x, clearColor.y, clearColor.z, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::render(); //edited virtual render_rec
}

void SampleScene::render_rec(Node * n) {
	//movable model
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, n->getModelMatrix_ptr());
	n->render();
	for (auto c : n->getChildren()) render_rec(c);
}

	//http://terathon.com/code/oblique.html
		//edited for glm matrix layout and opengl version
	void SampleScene::modifyProjectionMatrixOptPers(
		glm::mat4 & proj, glm::vec4 const & clipPlane) {

		// Calculate the clip-space corner point opposite the
			// clipping plane: (fsgn(clipPlane.x),fsgn(clipPlane.y),1,1)
			// and transform it into camera space by multiplying it
				//by the inverse of the projection matrix

		glm::vec4 q;
		//optimized multiplying by inverse:
		q.x = (fsgn(clipPlane.x) + proj[2][0]) / proj[0][0];
		q.y = (fsgn(clipPlane.y) + proj[2][1]) / proj[1][1];
		q.z = -1.0F;
		q.w = (1.0F + proj[2][2]) / proj[3][2];

		// Calculate the scaled plane vector
		glm::vec4 c = clipPlane * (2.0F / glm::dot(clipPlane, q));

		// Replace the third row of the projection matrix
		proj[0][2] = c.x;
		proj[1][2] = c.y;
		proj[2][2] = c.z + 1.0F;
		proj[3][2] = c.w;
	}

void SampleScene::modifyProjectionMatrix(glm::mat4 & proj, glm::vec4 const & clipPlane) {
	glm::vec4 q = glm::inverse(proj) * glm::vec4(
		fsgn(clipPlane.x),
		fsgn(clipPlane.y),
		1.0f,
		1.0f
	);

	// Calculate the scaled plane vector
	glm::vec4 c = clipPlane * (2.0F / (glm::dot(clipPlane, q)));

	// third row = clip plane - fourth row
	proj[0][2] = c.x - proj[0][3];
	proj[1][2] = c.y - proj[1][3];
	proj[2][2] = c.z - proj[2][3];
	proj[3][2] = c.w - proj[3][3];
}