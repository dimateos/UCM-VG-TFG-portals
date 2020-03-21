#include "Window_SDL_GL.h"
#include "SDL.h"
#include <glad\glad.h>
#include <iostream>

#include <string>

int Window_SDL_GL::width_ = 0;
int Window_SDL_GL::height_ = 0;
float Window_SDL_GL::resolution_ = 1.0f;
SDL_Window* Window_SDL_GL::window_ = nullptr;
SDL_GLContext Window_SDL_GL::context_ = nullptr;

bool Window_SDL_GL::init(const char* title, int w, int h, int x = 0, int y = 0, int GL_major = 3, int GL_minor = 3) {
	printf("window - init\n");
	int flags = SDL_WINDOW_OPENGL; //SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE

	//create window
	window_ = SDL_CreateWindow(title, x, y, w, h, flags);
	if (window_ == nullptr) {
		printf("window - Error creating window! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//if (Config::FULLSCREEN) SDL_SetWindowFullscreen(_window);

	//set GL attributes
	printf("window context - init\n");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //remove deprecated

	// Turn on double buffering with a 24bit Z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4); //MSAA
	//glEnable(GL_MULTISAMPLE);

	//create opengl context
	context_ = SDL_GL_CreateContext(window_);
	if (context_ == nullptr) {
		printf("window context - failed to create context\n");
		return false;
	}

	//use glad loader
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("window context - failed to initialize GLAD\n");
		return false;
	}

	width_ = SDL_GetWindowSurface(window_)->w;
	height_ = SDL_GetWindowSurface(window_)->h;
	resolution_ = (float)width_ / (float)height_;

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

	if (window_ != nullptr) {
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}

	printf("window context - release\n");
	if (context_ != nullptr) {
		SDL_GL_DeleteContext(context_);
		context_ = nullptr;
	}

	width_ = 0;
	height_ = 0;
}

void Window_SDL_GL::swap() {
	//printf("window - swap\n");
	SDL_GL_SwapWindow(window_);
}
