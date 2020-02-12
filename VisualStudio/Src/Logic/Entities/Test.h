#pragma once

#include "../Entity.h"

class Test : public Entity
{
public:
	Test();
	virtual ~Test();

	virtual bool handleEvent(const SDL_Event &event);
	virtual void update(float delta);
};