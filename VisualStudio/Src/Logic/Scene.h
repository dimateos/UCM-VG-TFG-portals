#pragma once
#include <vector>

//forwarded
class Entity;
#include <SDL_events.h>
//class Camera;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool init();
	virtual void release();

	bool handleEvent(const SDL_Event &event);
	void update(float delta);
	void render(float delta);

protected:
	//Camera* _camera = nullptr;
	std::vector<Entity*> _ents;
};