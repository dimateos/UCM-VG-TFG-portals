#include "Window_SDL_GL.h"
#include "SDL.h"
#include <glad\glad.h>
#include <iostream>

#include <string>

int Window_SDL_GL::_width = 0;
int Window_SDL_GL::_height = 0;
float Window_SDL_GL::_resolution = 1.0f;
SDL_Window* Window_SDL_GL::_window = nullptr;
SDL_GLContext Window_SDL_GL::_context = nullptr;

bool Window_SDL_GL::init(int SDL_window_flags, const char* title, int w, int h,
	int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int GL_major = 3, int GL_minor = 3) {
	printf("window - init\n");

	//create window
	_window = SDL_CreateWindow(title, x, y, w, h, SDL_window_flags);
	if (_window == nullptr) {
		printf("window - Error creating window! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//if (Config::FULLSCREEN) SDL_SetWindowFullscreen(_window);

	//set GL attributes
	printf("window context - init\n");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //remove deprecated

	//create opengl context
	_context = SDL_GL_CreateContext(_window);
	if (_context == nullptr) {
		printf("window context - failed to create context\n");
		return false;
	}

	//use glad loader
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("window context - failed to initialize GLAD\n");
		return false;
	}

	_width = SDL_GetWindowSurface(_window)->w;
	_height = SDL_GetWindowSurface(_window)->h;
	_resolution = (float)_width / (float)_height;

	//logging info
	printf("window context - GL VERSION: %s - GL VENDOR: %s\n", glGetString(GL_VERSION), glGetString(GL_VENDOR));
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "window context - Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	std::cout << std::endl;

	return true;
}

void Window_SDL_GL::release() {
	printf("window - release\n");

	if (_window != nullptr) {
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}

	printf("window context - release\n");
	if (_context != nullptr) {
		SDL_GL_DeleteContext(_context);
		_context = nullptr;
	}

	_width = 0;
	_height = 0;
}

void Window_SDL_GL::swap() {
	//printf("window - swap\n");
	SDL_GL_SwapWindow(_window);
}
