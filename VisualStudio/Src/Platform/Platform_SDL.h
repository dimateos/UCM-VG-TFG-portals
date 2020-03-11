#pragma once

#include "Listening.h"
typedef union SDL_Event; //forwarded

//maybe later decouple service using middle interface?
class Platform_SDL
{
public:
	static bool init();
	static void release();

	//atm here?
	static void pollEvents();
	static Emitter<SDL_Event> _keyEventEmitter, _mouseMotionEventEmitter, _mouseButtonEventEmitter,
		_windowEventEmitter, _platformEventEmitter;

	static void startTimings();
	static void updateTimings();

	//timings in seconds
	inline static double getDeltaTime() { return _deltaTime; }
	inline static float getDeltaTimef() { return (float) _deltaTime; }
	inline static double getDeltaTimeSinceStart() { return _detaTimeSinceStart; };
	inline static float getDeltaTimeSinceStartf() { return (float) _detaTimeSinceStart; };

private:
	Platform_SDL() {};

	//atm here
	static double _SDL_PERFORMANCE_FREQUENCY;
	static long long unsigned int _lastFrame, _thisFrame;
	static double _deltaTime, _detaTimeSinceStart;
};