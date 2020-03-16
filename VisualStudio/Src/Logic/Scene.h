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
	Node* world_node_;
	App* app_;

	//change for iterative over a vector
	void release_rec(Node* n);
	void update_rec(Node* n);
	void render_rec(Node* n);
};