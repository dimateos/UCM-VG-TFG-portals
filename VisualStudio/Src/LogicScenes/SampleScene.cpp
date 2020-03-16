#include "SampleScene.h"
#include "../LogicNodes/TriangleRGB.h"
#include "../LogicNodes/Triangle.h"
#include "../LogicNodes/SquareAnimated.h"
#include "../LogicNodes/SquareTextured.h"
#include "../LogicNodes/Cubes3D.h"
#include "../LogicNodes/FPS.h"

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
	//SCENE INPUT
	Platform_SDL::_platformEventEmitter.registerListener(this);

	//CAMERA
	vp_ = new Viewport(Window_SDL_GL::getWidth(), (float)Window_SDL_GL::getHeight());
	proj_ = new Projection(vp_->getAspect());
	cam_ = new Camera(vp_, proj_);

	//OBJECTS
	//nodes_.push_back(new SquareAnimated());

	Texture::setFlipVerticallyOnLoad();
	//nodes_.push_back(new SquareTextured());

	nodes_.push_back(new Triangle());
	//nodes_.push_back(new TriangleRGB());

	glEnable(GL_DEPTH_TEST);
	nodes_.push_back(new Cubes3D(cam_));
	nodes_.push_back(new FPS(cam_));

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

void SampleScene::update(float delta) {
	Scene::update();
}

void SampleScene::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene::render();

	//glBindVertexArray(UNBIND); //no need to unbind every time
}
