#pragma once
#include <vector>

#include "Transform.h"
class Renderable;
#include <SDL_events.h>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	Transform trans;

	virtual bool handleEvent(const SDL_Event &event);
	virtual void update(float delta);
	virtual void render(float delta);

protected:
	std::vector<Renderable*> _renderables;
};