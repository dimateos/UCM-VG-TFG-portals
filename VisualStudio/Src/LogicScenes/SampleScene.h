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
class InputFreeRotation;

#include "../Render/Material.h"
class ScreenPostFiltering;

#include <vector>

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

	Viewport *screenVP_, *postFilterVP_;
	RenderTarget *screenRT_, *postFilterRT_;
	ScreenPostFiltering* screenPF_;

	//render panel with real time screenshot (non-activated)
	Mesh* planeMesh_, *cubeMesh_;
	ShapeNode* renderPanel_;
	SolidMaterial *pinkMat_, *renderMat_;
	RenderTarget *renderPanelRT_;
	Texture *renderTex_;

	//blue render portal
	Camera* bPortalCam_;
	Node* bPortalRoot_;
	ShapeNode* bPortalSurface_;
	SolidMaterial *bPortalMat_;
	RenderTarget *bPortalRT_;
	Texture *bPortalTex_;

	//red render portal
	Camera* rPortalCam_;
	Node* rPortalRoot_;
	ShapeNode* rPortalSurface_;
	SolidMaterial *rPortalMat_;
	RenderTarget *rPortalPanelRT_;
	Texture *rPortalTex_;

	//camera mimic
	Node *player_;
	ShapeNode *playerBody_;
	InputFreeMovement* movController_;
	InputFreeRotation* rotController_;

	//portal teleporting
	float sqCloseDistance_;
	int rSideOld_ = 0, bSideOld_ = 0;

	//avoid portal clipping strategies
	float initialNear_, initialNearCornerDistance_;

	//portal recursion testing
	int recLimit_ = 1, startIndex_ = 0;
	const int REC_HARD_LIMIT = 16;
	std::vector<Transformation> recTrans_;

	//portal travellers slicing and duping test
	ShapeNode* testTraveller_;
	Node *playerCopy_;
	SolidMaterial *slizableMat_, *slizableMatCopy_;

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

	void avoidCameraClip();
	void updatePortalCamerasTrans();
	void updatePortalTravellers();

	glm::vec4 getClipPlane(Transformation const & panelT, Transformation const & camT);

	void modifyProjectionMatrixOptPers(glm::mat4 & proj, glm::vec4 const & clipPlane);
	void modifyProjectionMatrix(glm::mat4 & proj, glm::vec4 const & clipPlane);
};