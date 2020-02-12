#include "App.h"
#include <iostream>
using namespace std;

#include "Platform/Platform_SDL.h"
#include "Platform/Window_SDL_GL.h"

#include <SDL.h>
#include <glad\glad.h>

#include "Logic/Scenes/SampleScene.h"

App::App() {}

App::~App() {
	if (_running == true) printf("app - WARNING destroyed while running\n");
}

bool App::init() {
	printf("app - init\n");
	bool success = false;

	//init all platform systems
	success = Platform_SDL::init(SDL_INIT_VIDEO);
	if (!success) return false;

	int flags = SDL_WINDOW_OPENGL; //SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	success = Window_SDL_GL::init(flags, "TFG_dimateos", 800, 800, 100, 100, 3, 3);
	if (!success) return false;

	_scene = new SampleScene();
	_scene->init();
	return true;
}

void App::release() {
	printf("app - release\n");
	stop(); //in case not
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

	SDL_Event event;
	float timish = 0.015;
	while (!_stopRequest) {
		//printf("app - loop\n");

		//events
		while (SDL_PollEvent(&event) && !_stopRequest) {
			if (event.type == SDL_QUIT) {
				stop();
			}
			//exit also on ESC
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				stop();
			}
			//emit the events to the listeners (INPUT)
			//else Emit(e);
			//else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			//	glViewport(0, 0, event.window.data1, event.window.data2);
			//}

			else _scene->handleEvent(event);
		}

		//update
		_scene->update(timish);

		//clear in scene?
		glClearColor(0.9f, 0.1f, 0.1f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render
		_scene->render(timish);

		//swap
		Window_SDL_GL::swap();
	}
}
