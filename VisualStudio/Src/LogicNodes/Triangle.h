#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"

class Triangle : public Node
{
public:
	Triangle();
	virtual ~Triangle();

	virtual void render();

protected:
	Shader _shaderBasic;

	unsigned int _VAO, _VBO;
	const float _l = 0.3f;
	float triangle_vertices[3*3] = {
		// positions
		-_l, -_l, 0.0f,
		_l, -_l, 0.0f,
		0.0f,  _l, 0.0f,
	};
};
