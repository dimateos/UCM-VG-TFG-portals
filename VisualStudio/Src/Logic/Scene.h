#pragma once
#include <vector>

//forwarded
class Node;
class App; //tmp?
//class Camera;

class Scene
{
public:
	Scene(App* app);
	virtual ~Scene();

	virtual bool init();
	virtual void release();

	virtual void update();
	virtual void render();

protected:
	//Camera* _camera = nullptr;
	std::vector<Node*> nodes_;
	App* app_;
};