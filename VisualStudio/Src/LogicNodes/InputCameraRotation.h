#pragma once
#include "../Logic/Node.h"
#include "../Logic/Camera.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class InputCameraRotation : public Node, Listener<SDL_Event>
{
public:
	InputCameraRotation(Node* father, Camera* cam);
	virtual ~InputCameraRotation();

	virtual bool handleEvent(SDL_Event const & e);
	virtual void update();

	void setInputRot(glm::quat const & q);

protected:
	Camera * cam_;
	bool focus_ = true;

	float sens_ = 0.10;
	int frame_yaw_ = 0, frame_pitch_ = 0;
	float total_yaw_ = 0, total_pitch_ = 0;

	bool cappedPitch_ = true;
	float maxPitch_ = 90;
	void capPitch();
};
