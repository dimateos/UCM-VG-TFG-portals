#include "SampleScene.h"
#include "../LogicNodes/OldExamples/TriangleRGB.h"
#include "../LogicNodes/OldExamples/Triangle.h"
#include "../LogicNodes/OldExamples/SquareAnimated.h"
#include "../LogicNodes/OldExamples/SquareTextured.h"
#include "../LogicNodes/OldExamples/Cubes3D.h"

#include "../LogicNodes/Cube.h"
#include "../LogicNodes/FPS.h"
#include "../LogicNodes/InputFreeMovement.h"

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

	//CAMERA
	vp_ = new Viewport(Window_SDL_GL::getWidth(), (float)Window_SDL_GL::getHeight());
	proj_ = new Projection(vp_->getAspect());
	cam_ = new Camera(vp_, proj_);

	glEnable(GL_DEPTH_TEST); //3d depth
	Texture::setFlipVerticallyOnLoad(); //texture loading

	//OBJECTS
	//world_node_->addChild(new SquareAnimated());
	//world_node_->addChild(new SquareTextured());
	//world_node_->addChild(new Triangle());
	//world_node_->addChild(new TriangleRGB());
	//world_node_->addChild(new Cubes3D(cam_));

	auto cube = new Cube(cam_);
	world_node_->addChild(cube);

	auto node = new InputFreeMovement(cube);
	node->setFather(world_node_);

	//auto rotated = new Node();
	//world_node_->addChild(new FPS(cam_));

	return true;
}

bool SampleScene::handleEvent(SDL_Event const & e) {
	if (e.type == SDL_QUIT) {
		app_->stop();
		return true;
	}

	else printf("scene - ignored event type: %i\n", e.type);
	return false;
}

void SampleScene::update() {
	cam_->update();
	Scene::update();
}

void SampleScene::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene::render();

	//glBindVertexArray(UNBIND); //no need to unbind every time
}
