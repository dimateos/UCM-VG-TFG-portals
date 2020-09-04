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
class ScreenPostProcessing;

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
	//GENERAL RENDER
	Projection *proj_, *topDownProj_;
	Camera *cam_, *topDownCam_;
	float projFov_ = 75.0f, projNear_ = 0.1, projFar_ = 75.0, topDownW_ = 22.0, topDownZoom_ = 1.0;
	glm::vec3 topDownPos_ = glm::vec3(5,20,4);
	glm::vec3 clearColor = glm::vec3(0.2f, 0.2f, 0.2f);
	bool renderMainTopDown_ = false;

	unsigned int uniformModel_, uniformView_, uniformProj_;
	virtual void render_FPS();
	virtual void render_TOPDOWN();
	virtual void render_rec(Node* n);

	//viewports and postfiltering
	Viewport *screenVP_, *postProcessVP_;
	RenderTarget *screenRT_, *postProcessRT_;
	ScreenPostProcessing *screenPP_;
	int scenePPoption_ = 0, scenePPoption_pre_ = -1;

	//PLAYER AND CONTROL
	Node *player_;
	ShapeNode *playerBody_;
	InputFreeMovement *movController_;
	InputFreeRotation *rotController_;

	//OTHER DYNAMIC SCENE OBJETCTS
	ShapeNode *redCube_, *wall_;

	//common meshes and materials edited by key events
	Mesh *planeMesh_, *cubeMesh_;
	Texture checkersTex_, blankTex_;
	SolidMaterial *pinkMat_, *redCheckerMat_;

	//render panel with real time screenshot (non-activated)
	//RenderTarget *renderPanelRT_;
	//Texture *renderTex_;
	//SolidMaterial *renderMat_;
	//ShapeNode* renderPanel_;

	// PORTALS /////////////////////////////////////////////////////////////

	//blue portal
	Camera *bPortalCam_;
	RenderTarget *bPortalRT_;
	Texture *bPortalTex_;
	SolidMaterial *bPortalMat_;
	Node *bPortalRoot_, *bPortalFrames_;
	ShapeNode *bPortalSurface_;

	//red portal
	Camera *rPortalCam_;
	RenderTarget *rPortalPanelRT_;
	Texture *rPortalTex_;
	SolidMaterial *rPortalMat_;
	Node *rPortalRoot_, *rPortalFrames_;
	ShapeNode *rPortalSurface_;

	//portal teleporting
	float sqCloseDistance_;
	int rSideOld_ = 0, bSideOld_ = 0;

	//strategies to avoid portal clipping
	float minPortalWidth_ = EPSILON, minPortalIncrement = 0.05;
	const float WIDTH_HARD_LIMIT = EPSILON;
	float initialNear_, initialNearCornerDistance_;

	Projection *obliquePorj_;
	void avoidCameraClip();
	glm::vec4 getClipPlane(Transformation const & panelT, Transformation const & camT);
	void modifyProjectionMatrixOptPers(glm::mat4 & proj, glm::vec4 const & clipPlane);
	void modifyProjectionMatrix(glm::mat4 & proj, glm::vec4 const & clipPlane);

	//portal recursion
	int recLimit_ = 1, startIndex_ = 0;
	const int REC_HARD_LIMIT = 16;
	std::vector<Transformation> recTrans_;

	//portal travellers slicing and duping
	Node *playerCopy_;
	SolidMaterial *slizableMat_, *slizableMatCopy_;

	void updatePortalTravellers();
	void updatePortalCamerasTrans();
	void onPortalTravel();
};