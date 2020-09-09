#pragma once
#include "../Logic/Node.h"
#include "../Logic/Camera.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class InputFreeRotation : public Node, Listener<SDL_Event>
{
public:
	InputFreeRotation(Node* father, Node* target);
	virtual ~InputFreeRotation();

	virtual bool handleEvent(SDL_Event const & e);
	virtual void update();

	void setInputRot(glm::quat const & q);

	void setBlocked(bool b);
	void toggleBlocked();

protected:
	Node * target_;
	bool focus_ = true, blocked_ = false;

	float sens_ = 0.10;
	int frame_yaw_ = 0, frame_pitch_ = 0;
	float total_yaw_ = 0, total_pitch_ = 0;

	bool cappedPitch_ = true;
	float maxPitch_ = 90;
	void capPitch();
};
