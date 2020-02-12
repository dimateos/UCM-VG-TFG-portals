#pragma once

#include <atomic>
#include <thread>

class App
{
public:
	App();
	~App();
	bool init();
	void release();
	inline void join() const { _t->join(); };

	bool resume();
	bool pause();

private:
	void loop();

	std::thread *_t = nullptr;
	std::atomic<bool> _quitRequest, _running; //frenar el loop
};