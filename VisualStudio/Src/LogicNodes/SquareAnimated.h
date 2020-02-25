#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"

class SquareAnimated : public Node
{
public:
	SquareAnimated();
	virtual ~SquareAnimated();

	virtual void update(float delta);
	virtual void render();

protected:
	Shader _shaderBasic;
	unsigned int _uniformLocation;

	float _timish;

	unsigned int _VAO, _VBO, _EBO;
	float _l = 0.9f;
	float square_vertices[4*3] = {
		 _l,  _l, 0.0f,  // top right
		 _l, -_l, 0.0f,  // bottom right
		-_l, -_l, 0.0f,  // bottom left
		-_l,  _l, 0.0f   // top left
	};
	unsigned int indices[6] = {  // note that we start from 0
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
};
