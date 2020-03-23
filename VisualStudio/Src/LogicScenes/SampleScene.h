#pragma once

#include "../Logic/Scene.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class Viewport;
class Projection;
class Camera;

#include "../Render/Material.h"
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
	//for now here
	Viewport* vp_;
	Projection* proj_;
	Camera* cam_;

	//common here now
	Texture checkersTex_, blankTex_;
	unsigned int uniformModel_, uniformView_;
	virtual void render_rec(Node* n);

	FrameBuffering* frameBuffering_;
};