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
	inline static double getDeltaTime() { return deltaTime_; }
	inline static float getDeltaTimef() { return (float) deltaTime_; }
	inline static double getDeltaTimeSinceStart() { return detaTimeSinceStart_; };
	inline static float getDeltaTimeSinceStartf() { return (float) detaTimeSinceStart_; };

private:
	Platform_SDL() {};

	//atm here
	static double SDL_PERFORMANCE_FREQUENCY_;
	static long long unsigned int lastFrame_, thisFrame_;
	static double deltaTime_, detaTimeSinceStart_;
};