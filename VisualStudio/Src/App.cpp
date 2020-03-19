#include "App.h"
#include <iostream>
using namespace std;

#include "Platform/Platform_SDL.h"
#include "Platform/Window_SDL_GL.h"

#include "LogicScenes/SampleScene.h"

App::App() {}

App::~App() {
	if (running_ == true) printf("app - WARNING destroyed while running\n");
}

bool App::init(int window_w, int window_h) {
	printf("app - init\n");
	bool success = false;

	//init all platform systems
	success = Platform_SDL::init();
	if (!success) return false;

	success = Window_SDL_GL::init("TFG_dimateos", window_w, window_h, 100, 100, 3, 3);
	if (!success) return false;

	scene_ = new SampleScene(this);
	success = scene_->init();
	if (!success) return false;

	return true;
}

void App::release() {
	printf("app - release\n");

	//relase scene etc
	scene_->release();
	delete scene_;
}

bool App::start() {
	if (running_) return false;
	printf("app - Start running\n");

	running_ = true;
	stopRequest_ = false;
	loop();
	return true;
}

bool App::stop() {
	if (running_ == false) return false; //not running
	printf("app - Stop running\n");

	running_ = false;
	stopRequest_ = true;
	return true;
}

void App::loop() {
	printf("app - Start loop\n");
	Platform_SDL::startTimings();

	while (!stopRequest_) {
		//printf("app - loop\n");

		Platform_SDL::updateTimings();
		//float fps = 1 / Platform_SDL::getDeltaTime();
		//if (fps < 135) printf("fps: %f\n", fps);
		//printf("time since start: %f\n", Platform_SDL::getDeltaTimeSinceStart());

		//events sent to registered listeners by the platform
		Platform_SDL::pollEvents();

		//update
		scene_->update();

		//render
		scene_->render();

		//swap
		Window_SDL_GL::swap();
	}

	release();
}
