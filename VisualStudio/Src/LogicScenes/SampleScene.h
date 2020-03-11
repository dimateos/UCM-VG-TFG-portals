#pragma once

#include "../Logic/Scene.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class SampleScene : public Scene, Listener<SDL_Event>
{
public:
	SampleScene(App* app);
	virtual ~SampleScene();

	virtual bool init();

	virtual bool handleEvent(SDL_Event const & e);
	virtual void update(float delta);
	virtual void render();
};