#pragma once

#include "../Logic/Scene.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class Viewport;
class Projection;
class Camera;
class RenderTarget;
class ShapeNode;
class Texture;

#include "../Render/Material.h"
class ScreenPostFiltering;

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
	Projection* proj_;
	Camera* cam_;

	Viewport *vp_screen_, *vp_PF_;
	RenderTarget *rt_screen_, *rt_PF_;

	ScreenPostFiltering* screenPF_;

	//render panelling
	ShapeNode* renderPanel_;
	SolidMaterial *pinkMat_, *renderMat_;
	RenderTarget *rt_renderPanel_;
	Texture *renderTex_;

	//common here now
	Texture checkersTex_, blankTex_;
	unsigned int uniformModel_, uniformView_;
	virtual void render_rec(Node* n);
};