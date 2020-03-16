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
	_vp = new Viewport(Window_SDL_GL::getWidth(), (float)Window_SDL_GL::getHeight());
	_proj = new Projection(_vp->getAspect());
	_cam = new Camera(_vp, _proj);

	//OBJECTS
	//_nodes.push_back(new SquareAnimated());

	Texture::setFlipVerticallyOnLoad();
	//_nodes.push_back(new SquareTextured());

	_nodes.push_back(new Triangle());
	//_nodes.push_back(new TriangleRGB());

	glEnable(GL_DEPTH_TEST);
	_nodes.push_back(new Cubes3D(_cam));
	_nodes.push_back(new FPS(_cam));

	return true;
}

bool SampleScene::handleEvent(SDL_Event const & e) {
	if (e.type == SDL_QUIT) {
		_app->stop();
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
