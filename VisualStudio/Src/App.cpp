#include "App.h"
#include <iostream>
using namespace std;

#include "Platform/Platform_SDL.h"
#include "Platform/Window_SDL_GL.h"

#include "LogicScenes/SampleScene.h"

App::App() {}

App::~App() {
	if (_running == true) printf("app - WARNING destroyed while running\n");
}

bool App::init(int window_w, int window_h) {
	printf("app - init\n");
	bool success = false;

	//init all platform systems
	success = Platform_SDL::init();
	if (!success) return false;

	success = Window_SDL_GL::init("TFG_dimateos", window_w, window_h, 100, 100, 3, 3);
	if (!success) return false;

	_scene = new SampleScene(this);
	success = _scene->init();
	if (!success) return false;

	return true;
}

void App::release() {
	printf("app - release\n");

	//relase scene etc
	_scene->release();
	delete _scene;
}

bool App::start() {
	if (_running) return false;
	printf("app - Start running\n");

	_running = true;
	_stopRequest = false;
	loop();
	return true;
}

bool App::stop() {
	if (_running == false) return false; //not running
	printf("app - Stop running\n");

	_running = false;
	_stopRequest = true;
	return true;
}

void App::loop() {
	printf("app - Start loop\n");
	Platform_SDL::startTimings();

	while (!_stopRequest) {
		//printf("app - loop\n");

		Platform_SDL::updateTimings();
		//printf("fps: %f\n", 1 / Platform_SDL::getDeltaTime());
		//printf("time since start: %f\n", Platform_SDL::getDeltaTimeSinceStart());

		//events sent to registered listeners by the platform
		Platform_SDL::pollEvents();

		//update
		_scene->update();

		//render
		_scene->render();

		//swap
		Window_SDL_GL::swap();
	}

	release();
}
