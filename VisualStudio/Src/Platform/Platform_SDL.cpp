#include "Platform_SDL.h"
#include <SDL.h>
#include <iostream>

double Platform_SDL::_SDL_PERFORMANCE_FREQUENCY = 0.0f;
long long unsigned int Platform_SDL::_lastFrame = 0;
long long unsigned int Platform_SDL::_thisFrame = 0;
double Platform_SDL::_deltaTime = 0.0f;
double Platform_SDL::_detaTimeSinceStart = 0.0f;

Emitter<SDL_Event> Platform_SDL::_keyEventEmitter, Platform_SDL::_mouseMotionEventEmitter, Platform_SDL::_mouseButtonEventEmitter,
	Platform_SDL::_windowEventEmitter, Platform_SDL::_platformEventEmitter;

bool Platform_SDL::init() {
	printf("plat - init\n");
	int flags = SDL_INIT_VIDEO; //SDL_INIT_EVERYTHING

	//init sdl
	if (SDL_Init(flags) < 0) {
		printf("plat - SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	_SDL_PERFORMANCE_FREQUENCY = SDL_GetPerformanceFrequency();
	return true;
}

void Platform_SDL::release() {
	printf("plat - release\n");
	SDL_Quit();
}

void Platform_SDL::pollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		//distrubuted listening
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) _keyEventEmitter.Emit(event);
		else if (event.type == SDL_MOUSEMOTION) _mouseMotionEventEmitter.Emit(event);
		else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL)
			_mouseButtonEventEmitter.Emit(event);
		else if (event.type == SDL_WINDOWEVENT || event.type == SDL_DISPLAYEVENT) _windowEventEmitter.Emit(event);

		//others
		else if (event.type == SDL_QUIT || event.type == SDL_SYSWMEVENT) _platformEventEmitter.Emit(event);
		else printf("plat - ignored event type: %i\n", event.type);
	}
}

void Platform_SDL::startTimings() {
	_thisFrame = SDL_GetPerformanceCounter();
}

void Platform_SDL::updateTimings() {
	_lastFrame = _thisFrame;
	_thisFrame = SDL_GetPerformanceCounter();

	_deltaTime = (_thisFrame - _lastFrame) / _SDL_PERFORMANCE_FREQUENCY;
	_detaTimeSinceStart += _deltaTime;
}
