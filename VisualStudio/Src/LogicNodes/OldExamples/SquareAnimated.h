#pragma once

#include "../../Logic/Node.h"
#include "../../Render/Shader.h"

class SquareAnimated : public Node
{
public:
	SquareAnimated();
	virtual ~SquareAnimated();

	virtual void render();

protected:
	Shader shaderBasic_;
	unsigned int uniformLocation_;

	unsigned int VAO_, VBO_, EBO_;
	float l_ = 0.9f;
	float square_vertices_[4*3] = {
		 l_,  l_, 0.0f,  // top right
		 l_, -l_, 0.0f,  // bottom right
		-l_, -l_, 0.0f,  // bottom left
		-l_,  l_, 0.0f   // top left
	};
	unsigned int indices_[6] = {  // note that we start from 0
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
};
