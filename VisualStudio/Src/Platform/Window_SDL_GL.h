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
	inline static SDL_Window* getWindow() { return _window; };
	inline static int getWidth() { return _width; };
	inline static int getHeight() { return _height; };
	inline static float getResolution() { return _resolution; };

	//Context data
	inline static SDL_GLContext getContext() { return _context; };

private:
	Window_SDL_GL() {};

	//Window data
	static SDL_Window* _window;
	static int _width, _height;
	static float _resolution;

	//Context data
	static SDL_GLContext _context;
};