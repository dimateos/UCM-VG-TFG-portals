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
	Shader shaderRGB_;

	unsigned int VAO_, VBO_;
	const float l_ = 0.2f;
	float triangle_vertices_rgb_[6*3] = {
		// positions				// colors
		-l_, -l_, 0.0f,		1.0f, 0.0f, 0.0f,   // bottom right
		l_, -l_, 0.0f,		0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  l_, 0.0f,	0.0f, 0.0f, 1.0f    // top
	};
};
