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
	Shader shaderBasic_;

	unsigned int VAO_, VBO_;
	const float l_ = 0.3f;
	float triangle_vertices_[3*3] = {
		// positions
		-l_, -l_, 0.0f,
		l_, -l_, 0.0f,
		0.0f,  l_, 0.0f,
	};
};
