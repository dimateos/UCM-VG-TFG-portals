#include "App.h"
#include <iostream>
using namespace std;

#include "Platform/Platform_SDL.h"
#include "Platform/Window_SDL_GL.h"

#include <SDL.h>
#include <glad\glad.h>

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

	return true;
}

void App::release() {
	printf("app - release\n");
	pause(); //in case not paused
}

bool App::resume() {
	if (_running) return false;
	printf("app - Start thread\n");

	//spawn thread
	_running = true;
	_quitRequest = false;
	//_t = new thread(&App::loop, this);
	loop();

	return true;
}

bool App::pause() {
	if (_running == false) return false; //not running
	printf("app - Stop thread\n");

	//join thread
	_running = false;
	_quitRequest = true;
	//_t->join();
	//_t = nullptr;

	return true;
}

void App::loop() {
	printf("app - Start loop\n");

	SDL_Event event;
	float timish = 0, stepsih = 0.01;
	while (!_quitRequest) {
		//printf("app - loop\n");
		timish += stepsih;

		//events
		while (SDL_PollEvent(&event) && !_quitRequest) {
			if (event.type == SDL_QUIT) {
				pause();
			}
			//exit also on ESC
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				pause();
			}
			//emit the events to the listeners (INPUT)
			//else Emit(e);
			//else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			//	glViewport(0, 0, event.window.data1, event.window.data2);
			//}
		}

		//clear
		glClearColor(0.9f, 0.1f, 0.1f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//swap
		Window_SDL_GL::swap();
	}
}
