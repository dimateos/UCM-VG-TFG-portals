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
	Projection* proj_, *testPorj_;
	Camera* cam_;

	Viewport *vp_screen_, *vp_PF_;
	RenderTarget *rt_screen_, *rt_PF_;

	ScreenPostFiltering* screenPF_;

	//render panelling
	Mesh* planeMesh_, *cubeMesh_;
	ShapeNode* renderPanel_;
	SolidMaterial *pinkMat_, *renderMat_;
	RenderTarget *rt_renderPanel_;
	Texture *renderTex_;

	//blue render portal
	Camera* bPortalCam_;
	Node* bPortalPanel_;
	ShapeNode* bPortalCube_;
	SolidMaterial *bPortalMat_;
	RenderTarget *rt_bPortalPanel_;
	Texture *bPortalTex_;

	//red render portal
	Camera* rPortalCam_;
	Node* rPortalPanel_;
	ShapeNode* rPortalCube_;
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

	//some oblique here for now
	inline float fsgn(float f) {
		if (f > EPSILON) return (1.0F);
		if (f < -EPSILON) return (-1.0F);
		return (0.0F);
	}
	inline int sgn(float f) {
		if (f > EPSILON) return 1;
		if (f < -EPSILON) return -1;
		return 0;
	}

	void modifyProjectionMatrixOptPers(glm::mat4 & proj, glm::vec4 const & clipPlane);
	void modifyProjectionMatrix(glm::mat4 & proj, glm::vec4 const & clipPlane);
};