#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"

class TriangleRGB : public Node
{
public:
	TriangleRGB();
	virtual ~TriangleRGB();

	virtual void render();

protected:
	Shader _shaderRGB;

	unsigned int _VAO, _VBO;
	const float _l = 0.2f;
	float triangle_vertices_rgb[6*3] = {
		// positions				// colors
		-_l, -_l, 0.0f,		1.0f, 0.0f, 0.0f,   // bottom right
		_l, -_l, 0.0f,		0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  _l, 0.0f,	0.0f, 0.0f, 1.0f    // top
	};
};
