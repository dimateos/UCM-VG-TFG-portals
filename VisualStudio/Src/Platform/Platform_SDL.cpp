#include "Platform_SDL.h"
#include <SDL.h>
#include <iostream>

bool Platform_SDL::init(int SDL_flags = SDL_INIT_EVERYTHING) {
	printf("plat - init\n");

	//init sdl
	if (SDL_Init(SDL_flags) < 0) {
		printf("plat - SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void Platform_SDL::release() {
	printf("plat - release\n");
	SDL_Quit();
}