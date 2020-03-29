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

SampleScene::SampleScene(App* app) : Scene(app) {}

SampleScene::~SampleScene() {
	//delete all new
}

bool SampleScene::init() {
	Scene::init();
	glDepthFunc(GL_LESS);

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
	proj_ = new Projection(vp_screen_->getAspect(), 90.0f, 0.001f);
	cam_ = new Camera(proj_);
	Node::ROOT_CAM = cam_;

	//glDisable(GL_CULL_FACE); //cube not correct vertices
	//glEnable(GL_CULL_FACE);

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
	//fixed projection (ramains set to shader on binding / unbinding)
	glUniformMatrix4fv(uniformProj_, 1, GL_FALSE, Node::ROOT_CAM->getProj()->getProjMatrixPtr());

	//OBJECTS
	auto cubeMesh = new CubeMesh();
	auto redCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.2f, 0.2f), &checkersTex_);
	auto orangeCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.4f, 0.2f), &checkersTex_);
	auto blueCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.2f, 0.8f), &checkersTex_);
	auto cyanCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.8f), &checkersTex_);
	auto greenCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.2f), &checkersTex_);
	auto whiteCheckerMat = new SolidMaterial(glm::vec3(0.8f), &checkersTex_);

	auto redCube = new ShapeNode(world_node_, cubeMesh, redCheckerMat);
	auto redFloor = new ShapeNode(world_node_, cubeMesh, orangeCheckerMat);
	redFloor->setLocalScale(glm::vec3(6.0f, 0.1f, 10.0f));
	redFloor->setLocalPos(glm::vec3(0.0f, -0.5f, 4.0f));

	auto blueCube = new ShapeNode(world_node_, cubeMesh, blueCheckerMat);
	blueCube->translateX(10.0f);
	auto blueFloor = new ShapeNode(world_node_, cubeMesh, cyanCheckerMat);
	blueFloor->setLocalScale(glm::vec3(6.0f, 0.1f, 10.0f));
	blueFloor->setLocalPos(glm::vec3(0.0f, -0.5f, 4.0f));
	blueFloor->translateX(10.0f);

	auto whiteFloor = new ShapeNode(world_node_, cubeMesh, whiteCheckerMat);
	whiteFloor->setLocalScale(glm::vec3(15.0f, 0.1f, 15.0f));
	whiteFloor->setLocalPos(glm::vec3(5.0f, -0.5f, 18.0f));

	//RENDER PANEL
	rt_renderPanel_ = new RenderTarget();
	rt_renderPanel_->create(vp_screen_);
	renderTex_ = new Texture();
	renderTex_->createRenderTargetTexture(rt_renderPanel_);

	pinkMat_ = new SolidMaterial(glm::vec3(0.9f, 0.3f, 0.6f), &blankTex_);
	renderMat_ = new SolidMaterial(glm::vec3(0.9f), renderTex_);
	planeMesh_ = new PlaneMesh();

	renderPanel_ = new ShapeNode(world_node_, planeMesh_, renderMat_);
	renderPanel_->setLocalPos(whiteFloor->getLocalPos());
	renderPanel_->setLocalScale(glm::vec3(2, 2, 1));
	renderPanel_->translateY(2);
	//renderPanel->pitch(90);

	//BLUE PORTAL PANEL
	rt_bPortalPanel_ = new RenderTarget();
	rt_bPortalPanel_->create(vp_screen_);
	bPortalTex_ = new Texture();
	bPortalTex_->createRenderTargetTexture(rt_bPortalPanel_);
	bPortalMat_ = new SolidMaterial(glm::vec3(1.0f), bPortalTex_);
	bPortalMat_->option_ = 1;

	bPortalPanel_ = new ShapeNode(world_node_, planeMesh_, bPortalMat_);
	bPortalPanel_->setLocalScale(glm::vec3(1.5, 1.5, 1));
	bPortalPanel_->translateY(1);
	bPortalPanel_->translateZ(5);

	auto bPortalBorders = new Node(bPortalPanel_);
	bPortalBorders->scale(0.25f);
	float separation = 1.0f / bPortalBorders->getLocalScaleX();
	float rescale = 2 / bPortalBorders->getLocalScaleX();
	auto bPortalBorderL = new ShapeNode(bPortalBorders, cubeMesh, blueCheckerMat);
	bPortalBorderL->translate(-Transformation::BASE_RIGHT * separation);
	bPortalBorderL->setLocalScaleY(rescale);
	auto bPortalBorderR = new ShapeNode(bPortalBorders, cubeMesh, blueCheckerMat);
	bPortalBorderR->translate(Transformation::BASE_RIGHT * separation);
	bPortalBorderR->setLocalScaleY(rescale);
	auto bPortalBorderU = new ShapeNode(bPortalBorders, cubeMesh, blueCheckerMat);
	bPortalBorderU->translate(Transformation::BASE_UP * separation);
	bPortalBorderU->setLocalScaleX(rescale);

	//RED PORTAL PANEL
	rt_rPortalPanel_ = new RenderTarget();
	rt_rPortalPanel_->create(vp_screen_);
	rPortalTex_ = new Texture();
	rPortalTex_->createRenderTargetTexture(rt_rPortalPanel_);
	rPortalMat_ = new SolidMaterial(glm::vec3(1.0f), rPortalTex_);
	rPortalMat_->option_ = 1;

	rPortalPanel_ = new ShapeNode(world_node_, planeMesh_, rPortalMat_);
	//rPortalPanel_->mesh_ = nullptr;
	rPortalPanel_->setLocalTrans(bPortalPanel_->getLocalTrans());
	rPortalPanel_->translateX(10);

	auto rPortalBorders = new Node(rPortalPanel_);
	rPortalBorders->scale(0.25f);
	auto rPortalBorderL = new ShapeNode(rPortalBorders, cubeMesh, redCheckerMat);
	rPortalBorderL->translate(-Transformation::BASE_RIGHT * separation);
	rPortalBorderL->setLocalScaleY(rescale);
	auto rPortalBorderR = new ShapeNode(rPortalBorders, cubeMesh, redCheckerMat);
	rPortalBorderR->translate(Transformation::BASE_RIGHT * separation);
	rPortalBorderR->setLocalScaleY(rescale);
	auto rPortalBorderU = new ShapeNode(rPortalBorders, cubeMesh, redCheckerMat);
	rPortalBorderU->translate(Transformation::BASE_UP * separation);
	rPortalBorderU->setLocalScaleX(rescale);

	//REFERENCE AXIS
	auto axisMesh = new AxisMesh();
	auto axisRGB = new ShapeNode(world_node_, axisMesh, pinkMat_);
	auto axisSon = new Node(axisRGB);
	axisSon->scale(0.25f);
	float f = 1.0f / axisSon->getLocalScaleX();
	auto cubeRight = new ShapeNode(axisSon, cubeMesh, redCheckerMat);
	cubeRight->translate(Transformation::BASE_RIGHT * f);
	auto cubeUp = new ShapeNode(axisSon, cubeMesh, greenCheckerMat);
	cubeUp->translate(Transformation::BASE_UP * f);
	auto cubeBack = new ShapeNode(axisSon, cubeMesh, blueCheckerMat);
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

	//PLAYER
	player_ = new Node(world_node_);
	player_->setLocalPos(glm::vec3(0.f, 0.f, 10.f));
	//playerPrevTrans_ = player_->getLocalTrans();
	//player_->yaw(-90);
	//player->yaw(20);
	//player->scale(0.8f);

	auto playerBody = new ShapeNode(player_, cubeMesh, redCheckerMat);
	playerBody->scale(0.5);

	//edit camera
	cam_->setFather(player_);
	cam_->setLocalPos(glm::vec3(0.f, 1.f, 0.f));
	//auto camBody_ = new ShapeNode(cam_, cubeMesh, redCheckerMat);
	//camBody_->scale(0.5);

	playerPosOld_ = player_->getLocalPos();
	//camRotOld_ = cam_->getLocalRot(); //force first render

	//PORTAL EXTRA CAMERAS
	bPortalCam_ = new Camera(proj_);
	bPortalCam_->setFather(rPortalPanel_);
	auto bAxisRGB = new ShapeNode(bPortalCam_, axisMesh, pinkMat_);
	auto bAxisSon = new Node(bAxisRGB);
	bAxisSon->scale(0.20f);
	float f2 = 0.9f / bAxisSon->getLocalScaleX();
	auto bCubeRight = new ShapeNode(bAxisSon, cubeMesh, redCheckerMat);
	bCubeRight->translate(Transformation::BASE_RIGHT * f2);
	auto bCubeUp = new ShapeNode(bAxisSon, cubeMesh, greenCheckerMat);
	bCubeUp->translate(Transformation::BASE_UP * f2);
	auto bCubeBack = new ShapeNode(bAxisSon, cubeMesh, blueCheckerMat);
	bCubeBack->translate(Transformation::BASE_BACK * f2);

	rPortalCam_ = new Camera(proj_);
	rPortalCam_->setFather(bPortalPanel_);
	auto rAxisRGB = new ShapeNode(rPortalCam_, axisMesh, pinkMat_);
	auto rAxisSon = new Node(rAxisRGB);
	rAxisSon->scale(0.20f);
	auto rCubeRight = new ShapeNode(rAxisSon, cubeMesh, redCheckerMat);
	rCubeRight->translate(Transformation::BASE_RIGHT * f2);
	auto rCubeUp = new ShapeNode(rAxisSon, cubeMesh, greenCheckerMat);
	rCubeUp->translate(Transformation::BASE_UP * f2);
	auto rCubeBack = new ShapeNode(rAxisSon, cubeMesh, blueCheckerMat);
	rCubeBack->translate(Transformation::BASE_BACK * f2);

	//INPUT
	controller_ = new InputFreeMovement(world_node_, player_, cam_, false);
	auto inputCameraNode = new InputCameraRotation(world_node_, cam_);

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
			bPortalPanel_->mat_ = pinkMat_;
			rPortalPanel_->mat_ = pinkMat_;
		}
		else {
			renderPanel_->mat_ = renderMat_;
			bPortalPanel_->mat_ = bPortalMat_;
			rPortalPanel_->mat_ = rPortalMat_;
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
		controller_->target_ = controller_->target_ != player_ ? player_ : rPortalPanel_;
		return true;
	}

	//else printf("scene - ignored event type: %i\n", e.type);
	return false;
}

void SampleScene::update() {
	Scene::update();

	//atm we ignore scale
	auto playerPos = player_->getLocalPos();
	bool diffPos = glm::any(glm::epsilonNotEqual(playerPosOld_, playerPos, EPSILON));
	bool diffRot = glm::any(glm::epsilonNotEqual(camRotOld_, cam_->getLocalRot(), EPSILON));

	//update camera matrices
	if (diffPos || diffRot) {
		//printf("scene - updating cameras \n");

		//get position (P) in bPortal local coordinates of player
		//we also get the inversed for the camera
			//atm setting the matrix doesnt update the transformation so we cannot calculate the inversed
		glm::mat4 localMat = bPortalPanel_->getModelMatrix_Inversed() * cam_->getModelMatrix();
		glm::mat4 localMat_inversed = cam_->getModelMatrix_Inversed() * bPortalPanel_->getModelMatrix();

		//set player2 position in rPortal local coordinates equal to (P)
		//player2 is already child of portal
		bPortalCam_->setLocalModelMatrix(localMat);
		bPortalCam_->setLocalModelMatrix_Inversed(localMat_inversed);

		//same for the other portal
		rPortalCam_->setLocalModelMatrix(rPortalPanel_->getModelMatrix_Inversed() * cam_->getModelMatrix());
		rPortalCam_->setLocalModelMatrix_Inversed(cam_->getModelMatrix_Inversed() * rPortalPanel_->getModelMatrix());

		//player2_->setLocalPos(player_->getLocalPos());
		//player2_->translateX(10.0f);
		//player2_->setLocalRot(player_->getLocalRot());
		//printf("scene - cam roll: %f\n", glm::roll(cam_->getLocalRot()));
	}

	//check tp for each close portal
	if (diffPos) {
		//printf("scene - checking tp \n");

		//blue portal
		auto bPortalPos = bPortalPanel_->getLocalPos();
		glm::vec3 bPortalOffset = playerPos - bPortalPos;
		//close enough
		if (glm::length2(bPortalOffset) < sqCloseDistance_) {
			glm::vec3 bPortalOffsetOld = playerPosOld_ - bPortalPos; //could store between frames
			bool side = glm::dot(bPortalOffset, bPortalPanel_->back()) < 0;
			bool sideOld = glm::dot(bPortalOffsetOld, bPortalPanel_->back()) < 0;

			//diff sides so tp
			if (side != sideOld) {
				//printf("scene - TP \n");
				player_->setLocalPos(rPortalPanel_->getLocalPos() + bPortalOffset); //no correct rotation atm
			}
		}

		//red portal
		auto rPortalPos = rPortalPanel_->getLocalPos();
		glm::vec3 rPortalOffset = playerPos - rPortalPos;
		//close enough
		if (glm::length2(rPortalOffset) < sqCloseDistance_) {
			glm::vec3 rPortalOffsetOld = playerPosOld_ - rPortalPos; //could store between frames
			bool side = glm::dot(rPortalOffset, rPortalPanel_->back()) < 0;
			bool sideOld = glm::dot(rPortalOffsetOld, rPortalPanel_->back()) < 0;

			//diff sides so tp
			if (side != sideOld) {
				//printf("scene - TP \n");
				player_->setLocalPos(bPortalPanel_->getLocalPos() + rPortalOffset); //no correct rotation atm
			}
		}

		//printf(" bPortalPos x z: %f %f | playerPos x z: %f %f | playerPosOld_ x z: %f %f \n",
		//	bPortalPos.x, bPortalPos.z, playerPos.x, playerPos.z, playerPosOld_.x, playerPosOld_.z);

		//printf(" bPortalPanel_->back() x y z: %f %f %f\n",
		//	bPortalPanel_->back().x, bPortalPanel_->back().y, bPortalPanel_->back().z);

		//printf(" bPortalOffset x z: %f %f %i | bPortalOffsetOld x z: %f %f %i\n",
		//	bPortalOffset.x, bPortalOffset.z, side, bPortalOffsetOld.x, bPortalOffsetOld.z, sideOld);
	}

	//update previous
	playerPosOld_ = playerPos;
	camRotOld_ = cam_->getLocalRot();
}

void SampleScene::render() {
	//PORTAL PANEL pass - draw scene in the reused postfilter buffer
	SolidMaterial::SOLID_MAT_SHADER.bind(); //common shader
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, bPortalCam_->getViewMatrixPtr());
	rt_PF_->bind(true); //3d depth test enabled
	rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rPortalPanel_->mesh_ = nullptr;
	Scene::render(); //edited virtual render_rec
	rPortalPanel_->mesh_ = planeMesh_;

	//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
	rt_bPortalPanel_->bind(false);
	screenPF_->render();

	//PORTAL PANEL pass - draw scene in the reused postfilter buffer
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, rPortalCam_->getViewMatrixPtr());
	rt_PF_->bind(true); //3d depth test enabled
	rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bPortalPanel_->mesh_ = nullptr;
	Scene::render(); //edited virtual render_rec
	bPortalPanel_->mesh_ = planeMesh_;

	//EXTRA PASS - copy texture (draw to specific portal buffer + avoid writing and reading same buffer)
	rt_rPortalPanel_->bind(false);
	screenPF_->render();

	//main camera active
	SolidMaterial::SOLID_MAT_SHADER.bind(); //need to rebind (post filter render binded its shader)
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, cam_->getViewMatrixPtr());

	//LAST PASS - all the portals have view textures
	rt_PF_->bind(true); //3d depth test enabled
	rt_PF_->clear(0.2f, 0.2f, 0.2f, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::render(); //edited virtual render_rec

	//EXTRA PASS - copy texture for the render panel (avoid writing and reading same buffer)
	//no need of model uniform in the shaders
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
