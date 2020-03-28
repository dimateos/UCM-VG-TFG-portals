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

protected:
	Node *target_, *rotationReference_;
	Transformation initialTrans_;

	bool disable_rotation_; //maybe separated node?
	void applyFrameRotation();
	void applyFrameTranslation();

	float speed_ = 2, rotation_speed_ = 50, sprint_scaler_ = 4;
	bool sprint_toggleMode_ = false, rotate_toggleMode_ = true;

	bool sprinting_ = false, rotating_ = false;
	glm::vec3 frame_velocity_, frame_rotation_;
	std::list<Direction> xAxis_, zAxis_, yAxis_;
	std::list<Direction> rot_xAxis_, rot_zAxis_, rot_yAxis_;
};
