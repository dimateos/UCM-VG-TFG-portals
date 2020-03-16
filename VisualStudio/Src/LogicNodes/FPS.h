#pragma once
#include "../Logic/Node.h"
#include "../Logic/Camera.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class FPS : public Node, Listener<SDL_Event>
{
public:
	FPS(Camera* cam);
	virtual ~FPS();

	virtual void update();
	virtual bool handleEvent(SDL_Event const & e);

protected:
	Camera * cam_;

	float speed_ = 1;
	glm::vec3 velocity_;
	std::list<Direction> xAxis_, zAxis_;
};
