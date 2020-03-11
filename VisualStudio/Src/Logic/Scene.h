#pragma once
#include <vector>

//forwarded
class Node;
//class Camera;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool init();
	virtual void release();

	virtual void update();
	virtual void render();

protected:
	//Camera* _camera = nullptr;
	std::vector<Node*> _nodes;
};