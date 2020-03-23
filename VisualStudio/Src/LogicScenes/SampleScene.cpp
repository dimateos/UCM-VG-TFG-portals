#include "SampleScene.h"

#include "../LogicNodes/ShapeNode.h"
#include "../LogicNodes/InputCameraRotation.h"
#include "../LogicNodes/InputFreeMovement.h"

#include "../LogicNodes/FrameBuffering.h"

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

SampleScene::~SampleScene() {}

bool SampleScene::init() {
	Scene::init();

	//SCENE INPUT
	Platform_SDL::platformEventEmitter_.registerListener(this);
	Platform_SDL::keyEventEmitter_.registerListener(this);

	//CAMERA
	vp_ = new Viewport(Window_SDL_GL::getWidth(), (float)Window_SDL_GL::getHeight());
	proj_ = new Projection(vp_->getAspect());
	cam_ = new Camera(vp_, proj_);
	Node::ROOT_CAM = cam_;

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
	glUniformMatrix4fv(SolidMaterial::SOLID_MAT_SHADER.getUniformLocation("projection"), 1, GL_FALSE, Node::ROOT_CAM->getProj()->getProjMatrixPtr());

	//OBJECTS
	//glEnable(GL_DEPTH_TEST); //3d depth test
	auto mesh = new CubeMesh();
	auto mat = new SolidMaterial(glm::vec3(0.8f, 0.2f, 0.2f), &checkersTex_);
	auto cube = new ShapeNode(world_node_, mesh, mat);

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
	frameBuffering_ = new FrameBuffering(nullptr); //out of the tree

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

//void SampleScene::render() {
//	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	Scene::render();
//	frameBuffering_->render();
//}

void SampleScene::render() {
	//CONFIG COMMON SHADER
	SolidMaterial::SOLID_MAT_SHADER.bind();
	//movable camera
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, Node::ROOT_CAM->getViewMatrixPtr());

	//FIRST PASS
	frameBuffering_->bindFrameBuffer();
	glEnable(GL_DEPTH_TEST); //3d depth test enabled
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//edited virtual render_rec
	Scene::render();

	//SECOND PASS
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); //3d depth test disable (no need to clear the depth buffer)
	//glClearColor(0.2f, 0.2f, 0.2f, 1.0); //no need because we draw the whole screen
	//glClear(GL_COLOR_BUFFER_BIT);

	frameBuffering_->render();
}

void SampleScene::render_rec(Node * n) {
	//movable model
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, n->getModelMatrix_ptr());
	n->render();
	for (auto c : n->getChildren()) render_rec(c);
}
