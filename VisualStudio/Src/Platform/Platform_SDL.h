#pragma once

class Platform_SDL
{
public:
	static bool init(int SDL_flags);
	static void release();

private:
	Platform_SDL() {};
};