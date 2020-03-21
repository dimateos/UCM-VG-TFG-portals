#pragma once

#include "../Logic/Scene.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class Viewport;
class Projection;
class Camera;

class FrameBuffering;

class SampleScene : public Scene, Listener<SDL_Event>
{
public:
	SampleScene(App* app);
	virtual ~SampleScene();

	virtual bool init();

	virtual bool handleEvent(SDL_Event const & e);
	virtual void update();
	virtual void render();

protected:
	Viewport* vp_;
	Projection* proj_;
	Camera* cam_;

	FrameBuffering* frameBuffering_;
};