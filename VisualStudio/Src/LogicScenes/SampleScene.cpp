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

	//SCENE INPUT
	Platform_SDL::platformEventEmitter_.registerListener(this);
	Platform_SDL::keyEventEmitter_.registerListener(this);

	//CAMERA
	vp_ = new Viewport(Window_SDL_GL::getWidth(), (float)Window_SDL_GL::getHeight());
	proj_ = new Projection(vp_->getAspect(), 90.0f);
	cam_ = new Camera(vp_, proj_);
	Node::ROOT_CAM = cam_;

	rt_ = new RenderTarget();

	//COMMON TEXTURES AND MATERIALS
	//really badly placed here but for now

	Texture::setFlipVerticallyOnLoad(); //texture loading
	checkersTex_.load("../Assets/checker_gray.bmp", GL_TEXTURE_2D);
	blankTex_.load("../Assets/blank_white.bmp", GL_TEXTURE_2D);

	SolidMaterial::SOLID_MAT_SHADER.build("../Shaders/_basic/V_3D.glsl", "../Shaders/_basic/F_solid.glsl");
	SolidMaterial::SOLID_MAT_SHADER.bind();
	SolidMaterial::UNIFORM_COLOR = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("color");
	SolidMaterial::SOLID_MAT_SHADER.setInt("texture0", 0);

	uniformModel_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("model");
	uniformView_ = SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("view");
	//fixed projection
	glUniformMatrix4fv(SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("projection"), 1, GL_FALSE, Node::ROOT_CAM->getProj()->getProjMatrixPtr());

	//OBJECTS
	//glEnable(GL_DEPTH_TEST); //3d depth test
	auto cubeMesh = new CubeMesh();
	auto whiteCheckerMat = new SolidMaterial(glm::vec3(0.8f), &checkersTex_);
	auto redCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.2f, 0.2f), &checkersTex_);
	auto orangeCheckerMat = new SolidMaterial(glm::vec3(0.8f, 0.4f, 0.2f), &checkersTex_);
	auto blueCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.2f, 0.8f), &checkersTex_);
	auto cyanCheckerMat = new SolidMaterial(glm::vec3(0.2f, 0.8f, 0.8f), &checkersTex_);

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

	//simple cube
	//auto cube = new ShapeNode(world_node_);
	//cube->setLocalPos(glm::vec3(2.f, 0.f, 0.f));
	//cube->setLocalScaleY(2.0f);
	//cube->pitch(180.0f);
	//cube->yaw(90.0f);

	//directions of space
	//auto cubeSon = new Node(cube);
	//cubeSon->scale(0.25f);
	//float f = 1.5f / cubeSon->getLocalScaleX();
	//auto cubeRight = new ShapeNode(cubeSon);
	//cubeRight->translate(Transformation::BASE_RIGHT * f);
	//auto cubeUp = new ShapeNode(cubeSon);
	//cubeUp->translate(Transformation::BASE_UP * f);
	//auto cubeBack = new ShapeNode(cubeSon);
	//cubeBack->translate(Transformation::BASE_BACK * f);

	//transforming a father to see how transforms chain
	//auto cubeFather = new Node(world_node_);
	//cubeFather->setLocalPos(glm::vec3(1.f, 1.f, 1.f));
	//cubeFather->yaw(45.0f);
	//cubeFather->setLocalScaleY(0.5f);
	//actualy set the father in order to see results
	//cube->setFather(cubeFather);

	//PLAYER
	auto player = new Node(world_node_);
	player->setLocalPos(glm::vec3(0.f, 0.f, 5.f));
	//player->yaw(20);
	//player->scale(0.8f);

	//edit camera
	cam_->setFather(player);
	//cam_->yaw(20);
	//cam_->setLocalPos(glm::vec3(0.f, 0.f, 5.f));

	//INPUT
	auto inputMovementNode = new InputFreeMovement(world_node_, player, cam_, false);
	auto inputCameraNode = new InputCameraRotation(world_node_, cam_);

	//FRAME BUFFERING
	screenPF_ = new ScreenPostFiltering(nullptr, rt_); //out of the tree

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

	//else printf("scene - ignored event type: %i\n", e.type);
	return false;
}

void SampleScene::update() {
	Scene::update();

	//printf("scene - cam roll: %f\n", glm::roll(cam_->getLocalRot()));
}

void SampleScene::render() {
	//CONFIG COMMON SHADER here for now
	SolidMaterial::SOLID_MAT_SHADER.bind();

	//movable camera
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, Node::ROOT_CAM->getViewMatrixPtr());

	//FIRST PASS
	rt_->bind();
	glEnable(GL_DEPTH_TEST); //3d depth test enabled

	float res_ = 2.0f;
	glViewport(0, 0, Window_SDL_GL::getWidth() * res_, Window_SDL_GL::getWidth() * res_);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//edited virtual render_rec
	Scene::render();

	//LAST PASS
	rt_->unbind();
	glDisable(GL_DEPTH_TEST); //3d depth test disable (no need to clear the depth buffer)
	//glClearColor(0.2f, 0.2f, 0.2f, 1.0); //no need because we draw the whole screen
	//glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, Window_SDL_GL::getWidth(), Window_SDL_GL::getWidth());
	screenPF_->render();
}

void SampleScene::render_rec(Node * n) {
	//movable model
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, n->getModelMatrix_ptr());
	n->render();
	for (auto c : n->getChildren()) render_rec(c);
}
