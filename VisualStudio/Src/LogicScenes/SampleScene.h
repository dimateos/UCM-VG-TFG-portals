#pragma once

#include "../Logic/Scene.h"
#include "../Logic/Transformation.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class Viewport;
class Projection;
class Camera;
class RenderTarget;
class ShapeNode;
class Texture;
class Mesh;
class InputFreeMovement;
class InputCameraRotation;

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
	Mesh* planeMesh_;
	ShapeNode* renderPanel_;
	SolidMaterial *pinkMat_, *renderMat_;
	RenderTarget *rt_renderPanel_;
	Texture *renderTex_;

	//blue render portal
	Camera* bPortalCam_;
	ShapeNode* bPortalPanel_;
	SolidMaterial *bPortalMat_;
	RenderTarget *rt_bPortalPanel_;
	Texture *bPortalTex_;

	//red render portal
	Camera* rPortalCam_;
	ShapeNode* rPortalPanel_;
	SolidMaterial *rPortalMat_;
	RenderTarget *rt_rPortalPanel_;
	Texture *rPortalTex_;

	//camera mimic
	Node *player_;
	InputFreeMovement* movController_;
	InputCameraRotation* camController_;

	//portal teleporting
	float sqCloseDistance_ = 2*2;
	glm::vec3 playerPosOld_;
	glm::quat camRotOld_;

	//common here now
	Texture checkersTex_, blankTex_;
	unsigned int uniformModel_, uniformView_, uniformProj_;
	virtual void render_rec(Node* n);
};