#pragma once
#include "../Logic/Node.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

//moves the father - quizas target en vez de father?
class InputFreeMovement : public Node, Listener<SDL_Event>
{
public:
	InputFreeMovement(Node* father, Node* target);
	virtual ~InputFreeMovement();

	virtual void update();
	virtual bool handleEvent(SDL_Event const & e);

protected:
	Node* target_;
	Transformation initialTrans_;

	float speed_ = 1, rotation_speed_ = 50, sprint_scaler_ = 3;
	bool sprint_toggleMode_ = false, rotate_toggleMode_ = true;

	bool sprinting_ = false, rotating_ = false;
	glm::vec3 frame_velocity_, frame_rotation_;
	std::list<Direction> xAxis_, zAxis_, yAxis_;
	std::list<Direction> rot_xAxis_, rot_zAxis_, rot_yAxis_;
};
