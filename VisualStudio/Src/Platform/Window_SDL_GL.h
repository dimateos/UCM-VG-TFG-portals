#pragma once

class SDL_Window; //forwarded
typedef void *SDL_GLContext;

//maybe later decouple service using middle interface?
class Window_SDL_GL
{
public:
	static bool init(const char* title, int w, int h, int x, int y, int GL_minor, int GL_major);
	static void release();

	//swap window buffers and present
	static void swap();

	//Window data
	inline static SDL_Window* getWindow() { return window_; };
	inline static int getWidth() { return width_; };
	inline static int getHeight() { return height_; };
	inline static float getResolution() { return resolution_; };

	//Context data
	inline static SDL_GLContext getContext() { return context_; };

private:
	Window_SDL_GL() {};

	//Window data
	static SDL_Window* window_;
	static int width_, height_;
	static float resolution_;

	//Context data
	static SDL_GLContext context_;
};