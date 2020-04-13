#include "SampleScene.h"

#include "../LogicNodes/ShapeNode.h"
#include "../LogicNodes/InputCameraRotation.h"
#include "../LogicNodes/InputFreeMovement.h"

#include "../LogicNodes/ScreenPostFiltering.h"
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

	//glDisable(GL_CULL_FACE); //cube not correct vertices
	//glEnable(GL_CULL_FACE);

	//SCENE INPUT
	Platform_SDL::platformEventEmitter_.registerListener(this);
	Platform_SDL::keyEventEmitter_.registerListener(this);

	//TARGETS
	vp_screen_ = new Viewport(Window_SDL_GL::getWidth(), Window_SDL_GL::getHeight());
	float resPF = 2.0f; //PostFiltering multi/down sampling
	vp_PF_ = new Viewport(Window_SDL_GL::getWidth() * resPF, Window_SDL_GL::getHeight() * resPF);

	rt_screen_ = new RenderTarget();
	rt_screen_->setDefault(vp_screen_);
	rt_PF_ = new RenderTarget();
	rt_PF_->create(vp_PF_);

	//FRAME BUFFERING
	screenPF_ = new ScreenPostFiltering(nullptr, rt_PF_); //out of the tree

	//CAMERA
	proj_ = new Projection(vp_screen_->getAspect(), 75.0f, 0.1f); //affects clipping on portal pannels
	cam_ = new Camera(proj_);
	Node::ROOT_CAM = cam_;

	//extra projections for testing
	//testPorj_ = new Projection(vp_screen_->getAspect(), 90.0f, 1.0f, 15.0f);
	testPorj_ = new Projection(vp_screen_->getAspect(), 75.0f, 0.1f);
	//modifyProjectionMatrixOptPers(p, glm::vec4());

	//AVOIDING CAMERA CLIPPING PORTALS
	initialNear_ = proj_->near;

	//calculating all plane points (do not need all the info but atm nice to check)
	float fovY = proj_->fov;
	float angleYHalf = glm::radians(fovY) / 2;

	//nearTop / near = tan(angleYHalf) and then aspect ratio to get nearRight
	float nearTop = tanf(angleYHalf) * initialNear_;
	float nearRight = nearTop * proj_->aspect;
	float farTop = tanf(angleYHalf) * proj_->far;
	float farRight = farTop * proj_->aspect;

	//calculate fov X: nearRight / near = tan(angleXHalf) so angleXHalf = atan(nearRight / near)
	float angleXHalf = atanf(nearRight / initialNear_);
	float fovX = glm::degrees(angleXHalf * 2);

	//maximun possible near corner distance + a little epsilon
	initialNearCornerDistance_ = glm::length(glm::vec3(nearTop, nearRight, initialNear_)) + 10*EPSILON;

	//RECURSION STUFF
	recTrans_.resize(recLimit_);

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

	cubeMesh_ = new CubeMesh();
	planeMesh_ = new PlaneMesh();

	//OBJECTS
	auto redCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.2f, 0.2f), &checkersTex_);
	auto orangeCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.4f, 0.2f), &checkersTex_);
	auto blueCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.2f, 0.8f), &checkersTex_);
	auto cyanCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.8f), &checkersTex_);
	auto greenCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.2f), &checkersTex_);
	auto whiteCheckerMat = new SolidMaterial(glm::vec3(0.8f), &checkersTex_);

	auto redCube = new ShapeNode(world_node_, cubeMesh_, redCheckerMat);
	auto redFloor = new ShapeNode(world_node_, cubeMesh_, orangeCheckerMat);
	redFloor->setLocalScale(glm::vec3(6.0f, 0.1f, 10.0f));
	redFloor->setLocalPos(glm::vec3(0.0f, -0.5f, 4.0f));

	auto blueCube = new ShapeNode(world_node_, cubeMesh_, blueCheckerMat);
	blueCube->translateX(10.0f);
	auto blueFloor = new ShapeNode(world_node_, cubeMesh_, cyanCheckerMat);
	blueFloor->setLocalScale(glm::vec3(6.0f, 0.1f, 10.0f));
	blueFloor->setLocalPos(glm::vec3(0.0f, -0.5f, 4.0f));
	blueFloor->translateX(10.0f);

	auto whiteFloor = new ShapeNode(world_node_, cubeMesh_, whiteCheckerMat);
	whiteFloor->setLocalScale(glm::vec3(15.0f, 0.1f, 15.0f));
	whiteFloor->setLocalPos(glm::vec3(5.0f, -0.5f, 18.0f));

	//RENDER PANEL
	rt_renderPanel_ = new RenderTarget();
	rt_renderPanel_->create(vp_PF_);
	renderTex_ = new Texture();
	renderTex_->createRenderTargetTexture(rt_renderPanel_);

	pinkMat_ = new SolidMaterial(glm::vec3(0.9f, 0.3f, 0.6f), &blankTex_);
	renderMat_ = new SolidMaterial(glm::vec3(0.9f), renderTex_);

	renderPanel_ = new ShapeNode(world_node_, planeMesh_, renderMat_);
	renderPanel_->setLocalPos(whiteFloor->getLocalPos());
	renderPanel_->translateZ(5);
	renderPanel_->setLocalScale(glm::vec3(2, 2, 1));
	renderPanel_->translateY(2);
	//renderPanel->pitch(90);

	//BLUE PORTAL PANEL
	rt_bPortalPanel_ = new RenderTarget();
	rt_bPortalPanel_->create(vp_PF_);
	bPortalTex_ = new Texture();
	bPortalTex_->createRenderTargetTexture(rt_bPortalPanel_);
	bPortalMat_ = new SolidMaterial(glm::vec3(1.0f), bPortalTex_);
	bPortalMat_->option_ = 1;

	bPortalPanel_ = new Node(world_node_);
	//bPortalPanel_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalPanel_->translateY(1);
	bPortalPanel_->translateZ(6);
	//bPortalPanel_->yaw(180.f);

	bPortalCube_ = new ShapeNode(bPortalPanel_, cubeMesh_, bPortalMat_);
	//bPortalCube_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalCube_->setLocalScale(glm::vec3(2.62, 2.75, EPSILON));
	bPortalCube_->translateY(-0.07);
	bPortalCube_->setLocalPosZ(-bPortalCube_->getLocalScaleZ() * 0.5);
	sqCloseDistance_ = bPortalCube_->getLocalScaleX() * 0.6;
	sqCloseDistance_ *= sqCloseDistance_;

	auto bPortalBorders = new Node(bPortalPanel_);
	bPortalBorders->setFather(nullptr);
	bPortalBorders->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalBorders->scale(0.25f);
	float separation = 1.5f / bPortalBorders->getLocalScaleX();
	float rescale = 3 / bPortalBorders->getLocalScaleX();
	auto bPortalBorderL = new ShapeNode(bPortalBorders, cubeMesh_, blueCheckerMat);
	bPortalBorderL->translate(-Transformation::BASE_RIGHT * separation);
	bPortalBorderL->setLocalScaleY(rescale);
	auto bPortalBorderR = new ShapeNode(bPortalBorders, cubeMesh_, blueCheckerMat);
	bPortalBorderR->translate(Transformation::BASE_RIGHT * separation);
	bPortalBorderR->setLocalScaleY(rescale);
	auto bPortalBorderU = new ShapeNode(bPortalBorders, cubeMesh_, blueCheckerMat);
	bPortalBorderU->translate(Transformation::BASE_UP * separation);
	bPortalBorderU->setLocalScaleX(rescale);

	//RED PORTAL PANEL
	rt_rPortalPanel_ = new RenderTarget();
	rt_rPortalPanel_->create(vp_screen_);
	rPortalTex_ = new Texture();
	rPortalTex_->createRenderTargetTexture(rt_rPortalPanel_);
	rPortalMat_ = new SolidMaterial(glm::vec3(1.0f), rPortalTex_);
	rPortalMat_->option_ = 1;

	rPortalPanel_ = new Node(world_node_);
	//rPortalPanel_->mesh_ = nullptr;
	rPortalPanel_->setLocalTrans(bPortalPanel_->getLocalTrans());
	//rPortalPanel_->translateX(10);
	//rPortalPanel_->yaw(180.f);
	bPortalPanel_->translateZ(6);
	//rPortalPanel_->pitch(180.f);

	rPortalCube_ = new ShapeNode(rPortalPanel_, cubeMesh_, rPortalMat_);
	rPortalCube_->setLocalTrans(bPortalCube_->getLocalTrans());
	//auto rPortalWall = new ShapeNode(rPortalCube_, planeMesh_, whiteCheckerMat);
	//rPortalWall->translateZ(0.5);

	auto rPortalBorders = new Node(rPortalPanel_);
	rPortalBorders->setFather(nullptr);
	rPortalBorders->setLocalTrans(bPortalBorders->getLocalTrans());
	auto rPortalBorderL = new ShapeNode(rPortalBorders, cubeMesh_, redCheckerMat);
	rPortalBorderL->translate(-Transformation::BASE_RIGHT * separation);
	rPortalBorderL->setLocalScaleY(rescale);
	auto rPortalBorderR = new ShapeNode(rPortalBorders, cubeMesh_, redCheckerMat);
	rPortalBorderR->translate(Transformation::BASE_RIGHT * separation);
	rPortalBorderR->setLocalScaleY(rescale);
	auto rPortalBorderU = new ShapeNode(rPortalBorders, cubeMesh_, redCheckerMat);
	rPortalBorderU->translate(Transformation::BASE_UP * separation);
	rPortalBorderU->setLocalScaleX(rescale);

	//REFERENCE AXIS
	auto axisMesh = new AxisMesh();
	auto axisRGB = new ShapeNode(world_node_, axisMesh, pinkMat_);
	auto axisSon = new Node(axisRGB);
	axisSon->scale(0.25f);
	float f = 1.0f / axisSon->getLocalScaleX();
	auto cubeRight = new ShapeNode(axisSon, cubeMesh_, redCheckerMat);
	cubeRight->translate(Transformation::BASE_RIGHT * f);
	auto cubeUp = new ShapeNode(axisSon, cubeMesh_, greenCheckerMat);
	cubeUp->translate(Transformation::BASE_UP * f);
	auto cubeBack = new ShapeNode(axisSon, cubeMesh_, blueCheckerMat);
	cubeBack->translate(Transformation::BASE_BACK * f);

	//OTHER TESTING OBJECTS
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

	//SLICING TESTING
	testTraveller_ = new ShapeNode(world_node_, cubeMesh_, greenCheckerMat);
	testTraveller_->setLocalPos(whiteFloor->getLocalPos());
	testTraveller_->translateY(1);
	testTraveller_->setLocalScaleZ(4);

	//PLAYER
	player_ = new Node(world_node_);
	player_->setLocalPos(glm::vec3(0.f, 0.f, 9.f));
	//playerPrevTrans_ = player_->getLocalTrans();
	//player_->yaw(-90);
	//player->yaw(20);
	//player->scale(0.8f);

	//special material for slizing
	SolidMaterial::UNIFORM_CLIP_PLANE = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("clipPlane");
	slizableMat_ = new SolidMaterial(greenCheckerMat->color_, &checkersTex_);

	playerBody_ = new ShapeNode(player_, cubeMesh_, slizableMat_);
	playerBody_->scale(0.5);
	//playerBody_->setLocalScaleZ(4); //test longer slice

	//COPY for slicing
	playerCopy_ = new Node(world_node_);
	auto bodyCopy = new ShapeNode(*playerBody_);
	playerCopy_->addChild(bodyCopy);
	//separated copy material
	slizableMatCopy_ = new SolidMaterial(greenCheckerMat->color_, &checkersTex_);
	slizableMatCopy_->option_ = 2;
	bodyCopy->mat_ = slizableMatCopy_;

	//edit camera
	cam_->setFather(player_);
	cam_->setLocalPos(glm::vec3(0.f, 1.f, 0.f));

	//testing oblique projections
	//auto camBody_ = new ShapeNode(cam_, cubeMesh_, whiteCheckerMat);
	//camBody_->scale(0.25f);
	//camBody_->setLocalPos(glm::vec3(0.f, 0.f, -5.f));
	//camBody_->yaw(89);

	//auto fore = -camBody_->back();
	//auto clipPlane = glm::vec4(
	//	fore.x, fore.y, fore.z, glm::dot(-fore, camBody_->getLocalPos())
	//);

	//testPorj_->updateProjMatrix();
	//auto copy = testPorj_->computedProjMatrix_;
	//std::cout << "test:" << glm::to_string(testPorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy[2]) << std::endl << std::endl;

	//std::cout << "test:" << glm::to_string(testPorj_->computedProjMatrix_) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy) << std::endl << std::endl;

	//modifyProjectionMatrixOptPers(testPorj_->computedProjMatrix_, clipPlane);
	//modifyProjectionMatrix(copy, clipPlane);
	//std::cout << "test:" << glm::to_string(testPorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy[2]) << std::endl << std::endl;

	//std::cout << "test:" << glm::to_string(testPorj_->computedProjMatrix_) << std::endl;
	//std::cout << "copy:" << glm::to_string(copy) << std::endl << std::endl;

	//testPorj_->updateProjMatrix();
	//std::cout << "base:" << glm::to_string(testPorj_->computedProjMatrix_) << std::endl << std::endl;

	//testPorj_->near = 5.0;
	//testPorj_->updateProjMatrix();
	//std::cout << "5.0n:" << glm::to_string(testPorj_->computedProjMatrix_[2]) << std::endl;
	//std::cout << "5.0n:" << glm::to_string(testPorj_->computedProjMatrix_) << std::endl << std::endl;
	//modifyProjectionMatrixOptPers(testPorj_->computedProjMatrix_, clipPlane);

	//PORTAL EXTRA CAMERAS
	bPortalCam_ = new Camera(proj_);
	bPortalCam_->setFather(rPortalPanel_);
	bAxisRGB_ = new ShapeNode(bPortalCam_, axisMesh, pinkMat_);
	auto bAxisSon = new ShapeNode(bAxisRGB_, cubeMesh_, blueCheckerMat);
	bAxisSon->scale(0.20f);
	float f2 = 0.9f / bAxisSon->getLocalScaleX();
	auto bCubeRight = new ShapeNode(bAxisSon, cubeMesh_, redCheckerMat);
	bCubeRight->translate(Transformation::BASE_RIGHT * f2);
	auto bCubeUp = new ShapeNode(bAxisSon, cubeMesh_, greenCheckerMat);
	bCubeUp->translate(Transformation::BASE_UP * f2);
	auto bCubeBack = new ShapeNode(bAxisSon, cubeMesh_, blueCheckerMat);
	bCubeBack->translate(Transformation::BASE_BACK * f2);

	rPortalCam_ = new Camera(proj_);
	rPortalCam_->setFather(bPortalPanel_);
	rAxisRGB_ = new ShapeNode(rPortalCam_, axisMesh, pinkMat_);
	auto rAxisSon = new ShapeNode(rAxisRGB_, cubeMesh_, redCheckerMat);
	rAxisSon->scale(0.20f);
	auto rCubeRight = new ShapeNode(rAxisSon, cubeMesh_, redCheckerMat);
	rCubeRight->translate(Transformation::BASE_RIGHT * f2);
	auto rCubeUp = new ShapeNode(rAxisSon, cubeMesh_, greenCheckerMat);
	rCubeUp->translate(Transformation::BASE_UP * f2);
	auto rCubeBack = new ShapeNode(rAxisSon, cubeMesh_, blueCheckerMat);
	rCubeBack->translate(Transformation::BASE_BACK * f2);

	rAxisRGB_->setFather(nullptr);
	bAxisRGB_->setFather(nullptr);

	//INPUT
	movController_ = new InputFreeMovement(world_node_, player_, cam_, false);
	camController_ = new InputCameraRotation(world_node_, cam_);

	return true;
}

bool SampleScene::handleEvent(SDL_Event const & e) {
	if (e.type == SDL_QUIT) {
		app_->stop();
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
		app_->stop();
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o) {
		if (renderPanel_->mat_ == renderMat_) {
			renderPanel_->mat_ = pinkMat_;
			//bPortalPanel_->mat_ = pinkMat_;
			bPortalCube_->mat_ = pinkMat_;
			rPortalCube_->mat_ = pinkMat_;
		}
		else {
			renderPanel_->mat_ = renderMat_;
			//bPortalPanel_->mat_ = bPortalMat_;
			bPortalCube_->mat_ = bPortalMat_;
			rPortalCube_->mat_ = rPortalMat_;
			renderMat_->option_ == 0 ? renderMat_->option_ = 1 : renderMat_->option_ = 0;
			bPortalMat_->option_ == 0 ? bPortalMat_->option_ = 1 : bPortalMat_->option_ = 0;
			rPortalMat_->option_ == 0 ? rPortalMat_->option_ = 1 : rPortalMat_->option_ = 0;
		}
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_i) {
		//only works once (no deep edited references) used for some random test
		Camera *aux = cam_;
		cam_ = bPortalCam_;
		bPortalCam_ = aux;
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_k) {
		if (movController_->target_ != rPortalPanel_) {
			movController_->target_ = rPortalPanel_;
			movController_->rotationReference_ = rPortalPanel_;
		}
		else {
			movController_->target_ = player_;
			movController_->rotationReference_ = cam_;
		}
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m) {
		if (movController_->target_ != testTraveller_) {
			movController_->target_ = testTraveller_;
			movController_->rotationReference_ = testTraveller_;
		}
		else {
			movController_->target_ = player_;
			movController_->rotationReference_ = cam_;
		}
		return true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l) {
		if (rAxisRGB_->getFather() == nullptr) {
			rAxisRGB_->setFather(rPortalCam_);
			bAxisRGB_->setFather(bPortalCam_);
		}
		else {
			rAxisRGB_->setFather(nullptr);
			bAxisRGB_->setFather(nullptr);
		}
		return true;
	}

	//else printf("scene - ignored event type: %i\n", e.type);
	return false;
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
	glm::vec3 rCamOffset = player_->getLocalPos() + cam_->getLocalPos() - bPortalPanel_->getLocalPos();
	float rCamDot = glm::dot(rCamOffset, bPortalPanel_->back());

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
	rPortalCam_->setLocalTrans(Transformation::getDescomposed(rPortalPanel_->getModelMatrix_Inversed() * cam_->getModelMatrix()));

	//calculate recursion positions and rotations - for just 1 portal atm
	glm::mat4 camMat = cam_->getModelMatrix(), portalMat_inv = bPortalPanel_->getModelMatrix_Inversed(), portalMat_base = rPortalPanel_->getModelMatrix();

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
	auto bPortalPos = bPortalPanel_->getLocalPos();
	glm::vec3 bPortalOffset = playerPos - bPortalPos;
	//close enough
	if (glm::length2(bPortalOffset) < sqCloseDistance_) {
		int side = sgn(glm::dot(bPortalOffset, -bPortalPanel_->back()));
		//printf(" blue S: %i - So: %i - off: %f %f %f\n", side, bSideOld_, bPortalOffset.x, bPortalOffset.y, bPortalOffset.z);

		//set clone position accordingly
		playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalPanel_->getModelMatrix() * bPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));

		//diff sides so tp
		if (side * bSideOld_ == -1) {
			printf("%i - TP blue \n", ++tpc);
			//player_->setLocalPos(rPortalPanel_->getLocalPos() + bPortalOffset); //no correct rotation atm

			//set correct position and rotation (decomposed from matrices for now) - ignoring scale
			Transformation t = Transformation::getDescomposed(rPortalPanel_->getModelMatrix() * bPortalPanel_->getModelMatrix_Inversed() * cam_->getModelMatrix());
			//update player pos (although atm no tp chaining)
			playerPos = t.postion - cam_->getLocalPos();
			player_->setLocalPos(playerPos);
			camController_->setInputRot(t.rotation);

			//invalid previous sides
			bSideOld_ = 0;
			bPortalCube_->setLocalScaleZ(EPSILON);
			bPortalCube_->setLocalPosZ(0);

			//correct linked portal panel scale
			rSideOld_ = sgn(glm::dot(playerPos - rPortalPanel_->getLocalPos(), -rPortalPanel_->back()));
			rPortalCube_->setLocalScaleZ(initialNearCornerDistance_);
			rPortalCube_->setLocalPosZ(rSideOld_ * rPortalCube_->getLocalScaleZ() / 2);
			//make player copy
			printf("red clone + undo blue\n");
			playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalPanel_->getModelMatrix() * rPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(rSideOld_) * -rPortalPanel_->back(), normalCopy = float(rSideOld_) * bPortalPanel_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, rPortalPanel_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, bPortalPanel_->getLocalPos()));
		}
		else if (bSideOld_ == 0) { //store new valid side - just entered the zone
			bSideOld_ = side;
			//avoid clip strategy B - modify portal scale to fit clipping near plane
			bPortalCube_->setLocalScaleZ(initialNearCornerDistance_);
			bPortalCube_->setLocalPosZ(side * bPortalCube_->getLocalScaleZ() / 2);

			//make player copy
			printf("blue clone\n");
			playerCopy_->setFather(world_node_);
			slizableMat_->option_ = 2;
			playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalPanel_->getModelMatrix() * bPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(side) * -bPortalPanel_->back(), normalCopy = float(side) * rPortalPanel_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, bPortalPanel_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, rPortalPanel_->getLocalPos()));
		}
	}
	else if (bSideOld_ != 0) { //player is out of zone so invalid previous
		bSideOld_ = 0;
		//avoid clip strategy B - modify portal scale to fit clipping near plane
		bPortalCube_->setLocalScaleZ(EPSILON);
		bPortalCube_->setLocalPosZ(0);
		printf("blue UNclone\n");
		playerCopy_->setFather(nullptr);
		slizableMat_->option_ = 0;
	}

	//red portal
	auto rPortalPos = rPortalPanel_->getLocalPos();
	glm::vec3 rPortalOffset = playerPos - rPortalPos;
	//close enough
	if (glm::length2(rPortalOffset) < sqCloseDistance_) {
		int side = sgn(glm::dot(rPortalOffset, -rPortalPanel_->back()));
		//printf(" red S: %i - So: %i - off: %f %f %f\n", side, rSideOld_, rPortalOffset.x, rPortalOffset.y, rPortalOffset.z);

		//set clone position accordingly
		playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalPanel_->getModelMatrix() * rPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));

		//diff sides so tp
		if (side * rSideOld_ == -1) {
			printf("%i - TP red \n", ++tpc);
			//set correct position and rotation (decomposed from matrices for now) - ignoring scale
			Transformation t = Transformation::getDescomposed(bPortalPanel_->getModelMatrix() * rPortalPanel_->getModelMatrix_Inversed() * cam_->getModelMatrix());
			playerPos = t.postion - cam_->getLocalPos();
			player_->setLocalPos(playerPos);
			camController_->setInputRot(t.rotation);

			//invalid previous sides
			rSideOld_ = 0;
			rPortalCube_->setLocalScaleZ(EPSILON);
			rPortalCube_->setLocalPosZ(0);

			//correct linked portal panel scale
			bSideOld_ = sgn(glm::dot(playerPos - bPortalPanel_->getLocalPos(), -bPortalPanel_->back()));
			bPortalCube_->setLocalScaleZ(initialNearCornerDistance_);
			bPortalCube_->setLocalPosZ(bSideOld_ * bPortalCube_->getLocalScaleZ() / 2);
			//make player copy
			printf("blue clone + undo red\n");
			playerCopy_->setLocalTrans(Transformation::getDescomposed(rPortalPanel_->getModelMatrix() * bPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(bSideOld_) * -bPortalPanel_->back(), normalCopy = float(bSideOld_) * rPortalPanel_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, bPortalPanel_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, rPortalPanel_->getLocalPos()));
		}
		else if (rSideOld_ == 0) { //store new valid side - just entered the zone
			rSideOld_ = side;
			//avoid clip strategy B - modify portal scale to fit clipping near plane
			rPortalCube_->setLocalScaleZ(initialNearCornerDistance_);
			rPortalCube_->setLocalPosZ(side * rPortalCube_->getLocalScaleZ() / 2);

			//make player copy
			printf("red clone\n");
			playerCopy_->setFather(world_node_);
			slizableMat_->option_ = 2;
			playerCopy_->setLocalTrans(Transformation::getDescomposed(bPortalPanel_->getModelMatrix() * rPortalPanel_->getModelMatrix_Inversed() * player_->getModelMatrix()));
			//set both clipPlanes (world pos)
			auto normal = float(side) * -rPortalPanel_->back(), normalCopy = float(side) * bPortalPanel_->back();
			slizableMat_->clipPlane_ = glm::vec4(normal.x, normal.y, normal.z, glm::dot(-normal, rPortalPanel_->getLocalPos()));
			slizableMatCopy_->clipPlane_ = glm::vec4(normalCopy.x, normalCopy.y, normalCopy.z, glm::dot(-normalCopy, bPortalPanel_->getLocalPos()));
		}
	}
	else if (rSideOld_ != 0) { //player is out of zone so invalid previous
		rSideOld_ = 0;
		//avoid clip strategy B - modify portal scale to fit clipping near plane
		rPortalCube_->setLocalScaleZ(EPSILON);
		rPortalCube_->setLocalPosZ(0);
		printf("red UNclone\n");
		playerCopy_->setFather(nullptr);
		slizableMat_->option_ = 0;
	}
}

void SampleScene::update() {
	Scene::update();

	//atm done within portal checking (strategy B)
	//if (diffPos) avoidCameraClip();

	//check objects entering portal zone: handle tp
		//atm separated from player - handle portal scale to avoid camera near clip
	updatePortalTravellers();

	//update camera matrices
	updatePortalCamerasTrans();
}

glm::vec4 SampleScene::getClipPlane(Transformation const & panelT, Transformation const & camT) {
	//oblique near plane for each portal camera (camera is child of plane - so just inverse values atm)
	//auto planeN = -rPortalPanel_->back(); //camera is child of plane so acually no
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
	rPortalCube_->mesh_ = nullptr;
	bPortalCube_->mesh_ = cubeMesh_;
	bPortalCube_->mat_ = pinkMat_;

	//atm only 1 portal has recursion (and atm do all recursions event outside screen)
	for (size_t i = 0; i < recLimit_; i++) {
		//PORTAL PANEL pass - draw scene in the reused postfilter buffer
		SolidMaterial::SOLID_MAT_SHADER.bind(); //common shader
		rt_PF_->bind(true); //3d depth test enabled
		rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set the transformation in order
		bPortalCam_->setLocalTrans(recTrans_[i]);

		//calculate oblique plane
		modifyProjectionMatrixOptPers(testPorj_->computedProjMatrix_, getClipPlane(rPortalPanel_->getLocalTrans(), bPortalCam_->getLocalTrans()));
		//load the matrix and the restore it
		glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, testPorj_->getProjMatrixPtr());
		testPorj_->computedProjMatrix_ = proj_->computedProjMatrix_;

		glUniformMatrix4fv(uniformView_, 1, GL_FALSE, bPortalCam_->getViewMatrixPtr());
		Scene::render(); //edited virtual render_rec

		//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
		rt_bPortalPanel_->bind(false);
		screenPF_->render();

		//pink only for final iteration
		if (i == 0) bPortalCube_->mat_ = bPortalMat_;
	}

	//PORTAL PANEL pass - draw scene in the reused postfilter buffer
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)

	//oblique near plane for each portal camera (camera is child of plane - so just inverse values atm)
	modifyProjectionMatrixOptPers(testPorj_->computedProjMatrix_, getClipPlane(bPortalPanel_->getLocalTrans(), rPortalCam_->getLocalTrans()));
	glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, testPorj_->getProjMatrixPtr());
	testPorj_->computedProjMatrix_ = proj_->computedProjMatrix_;

	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, rPortalCam_->getViewMatrixPtr());
	rt_PF_->bind(true); //3d depth test enabled
	rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bPortalCube_->mesh_ = nullptr;
	rPortalCube_->mesh_ = cubeMesh_;
	rPortalCube_->mat_ = pinkMat_;
	Scene::render(); //edited virtual render_rec

	//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
	rt_rPortalPanel_->bind(false);
	screenPF_->render();

	//main camera active
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)
	glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, proj_->getProjMatrixPtr());
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, cam_->getViewMatrixPtr());

	bPortalCube_->mesh_ = cubeMesh_;
	rPortalCube_->mesh_ = cubeMesh_;
	bPortalCube_->mat_ = bPortalMat_;
	rPortalCube_->mat_ = rPortalMat_;

	//LAST PASS - all the portals have view textures
	rt_PF_->bind(true); //3d depth test enabled
	rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::render(); //edited virtual render_rec

	//EXTRA PASS - copy texture for the render panel (avoid writing and reading same buffer)
	//no need of model uniform in the shaders - nor camera matrices
	rt_renderPanel_->bind(false);
	screenPF_->render();

	//SCREEN PASS - with the postfilters
	rt_screen_->bind(false); //3d depth test disable (no need to clear the depth buffer)
	screenPF_->render();
}

void SampleScene::render_rec(Node * n) {
	//movable model
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, n->getModelMatrix_ptr());
	n->render();
	for (auto c : n->getChildren()) render_rec(c);
}

//http://terathon.com/code/oblique.html - edited for glm matrix layout and opengl version
void SampleScene::modifyProjectionMatrixOptPers(glm::mat4 & proj, glm::vec4 const & clipPlane) {
	// Calculate the clip-space corner point opposite the clipping plane as (fsgn(clipPlane.x), fsgn(clipPlane.y), 1, 1)
	// and transform it into camera space by multiplying it by the inverse of the projection matrix
	glm::vec4 q;
	q.x = (fsgn(clipPlane.x) + proj[2][0]) / proj[0][0]; //optimized multiplying by inverse
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