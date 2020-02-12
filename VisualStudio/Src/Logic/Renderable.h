#pragma once
#include <glm.hpp>

class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void draw(float delta, glm::mat4 modelMatrix) = 0;

protected:

};
