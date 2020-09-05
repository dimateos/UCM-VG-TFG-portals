#pragma once
#include "../Logic/Node.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

//moves the father - quizas target en vez de father?
class InputFreeMovement : public Node, Listener<SDL_Event>
{
public:
	InputFreeMovement(Node* father, Node* target, Node * rotationReference, bool disable_rotation);
	virtual ~InputFreeMovement();

	virtual bool handleEvent(SDL_Event const & e);
	virtual void update();

	void setTarget(Node *target, Node *rotationReference);
	inline const Node * getTarget() const { return target_; };

	void setRotating(bool rotating);


protected:
	Node *target_, *rotationReference_;
	Transformation initialTrans_, hardInitialTrans_;

	bool disable_rotation_; //maybe separated node?
	void applyFrameRotation();
	void calculateFrameTranslation();
	void applyFrameGLOBALTranslation();

	float baseSpeed_ = 5, baseRotSpeed_ = 50;
	float fastSpeedMuliplier_ = 3.0f, slowSpeedMuliplier_ = 0.3, currentSpeedMultiplier_ = 1.0f;

	bool CFG_toggleSpeed_ = false, CFG_toggleRotation_ = true, CFG_independetAxisY_ = true;

	bool fast_ = false, slow_ = false, rotating_ = false;
	glm::vec3 frame_velocity_, frame_Gvelocity_, frame_rotation_;
	std::list<Direction> xAxis_, zAxis_, yAxis_;
	std::list<Direction> xGAxis_, zGAxis_, yGAxis_;
	std::list<Direction> rot_xAxis_, rot_zAxis_, rot_yAxis_;
};
