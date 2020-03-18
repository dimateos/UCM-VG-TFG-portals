#pragma once
#include "../Logic/Node.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

//moves the father_
class InputFreeMovement : public Node, Listener<SDL_Event>
{
public:
	InputFreeMovement(Node* fatherToMove);
	virtual ~InputFreeMovement();

	virtual void update();
	virtual bool handleEvent(SDL_Event const & e);

protected:
	glm::vec3 iniPostion;
	glm::quat iniRotation;

	float speed_ = 1, rotation_speed_ = 50, sprint_scaler_ = 3;
	bool sprint_toggleMode_ = false, rotate_toggleMode_ = true;

	bool sprinting_ = false, rotating_ = false;
	glm::vec3 frame_velocity_, frame_rotation_;
	std::list<Direction> xAxis_, zAxis_, yAxis_;
	std::list<Direction> rot_xAxis_, rot_zAxis_, rot_yAxis_;
};
