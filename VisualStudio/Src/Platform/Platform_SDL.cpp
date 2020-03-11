#include "Platform_SDL.h"
#include <SDL.h>
#include <iostream>

double Platform_SDL::_SDL_PERFORMANCE_FREQUENCY = 0.0f;
long long unsigned int Platform_SDL::_lastFrame = 0;
long long unsigned int Platform_SDL::_thisFrame = 0;
double Platform_SDL::_deltaTime = 0.0f;
double Platform_SDL::_detaTimeSinceStart = 0.0f;

bool Platform_SDL::init(int SDL_flags = SDL_INIT_EVERYTHING) {
	printf("plat - init\n");

	//init sdl
	if (SDL_Init(SDL_flags) < 0) {
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

void Platform_SDL::startTimings() {
	_thisFrame = SDL_GetPerformanceCounter();
}

void Platform_SDL::updateTimings() {
	_lastFrame = _thisFrame;
	_thisFrame = SDL_GetPerformanceCounter();

	_deltaTime = (_thisFrame - _lastFrame) / _SDL_PERFORMANCE_FREQUENCY;
	_detaTimeSinceStart += _deltaTime;
}
