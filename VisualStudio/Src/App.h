#pragma once

class Scene;

class App
{
public:
	App();
	~App();
	bool init();
	void release();

	bool start();
	bool stop();

private:
	void loop();
	bool _stopRequest, _running; //loop control

	Scene* _scene;
};