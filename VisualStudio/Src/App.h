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

	//tmp here
	const float RES = 1.0f; //16.0f / 9.0f;
	const int RES_H = 720;
	const int RES_W = RES_H * RES;

	Scene* _scene;
};