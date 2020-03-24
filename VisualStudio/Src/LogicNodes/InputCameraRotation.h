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

protected:
	Camera * cam_;
	bool focus_ = true;

	float sens_ = 1;
	int rotY_ = 0, rotX_ = 0;
	float total_rotY_ = 0, total_rotX_ = 0, maxRotX_ = 90;
};
