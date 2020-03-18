#pragma once

#include "../../Logic/Node.h"
#include "../../Render/Shader.h"
#include "../../Render/Texture.h"

class SquareTextured : public Node
{
public:
	SquareTextured();
	virtual ~SquareTextured();

	virtual void render();

protected:
	Shader shaderTextured_;
	Texture tex1_, tex2_;
	unsigned int uniformTranform_;

	unsigned int VAO_, VBO_, EBO_;
	float l_ = 0.6f;
	unsigned int indices_[6] = {  // note that we start from 0
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float square_tex_vertices_[4*5] = {
		// positions          // texture coords
		 l_,  l_, 0.0f,   1.0f, 1.0f,   // top right
		 l_, -l_, 0.0f,   1.0f, 0.0f,   // bottom right
		-l_, -l_, 0.0f,   0.0f, 0.0f,   // bottom left
		-l_,  l_, 0.0f,   0.0f, 1.0f    // top left
	};
	float square_tex_color_vertices_[4*8] = {
		// positions		// colors           // texture coords
		 l_,  l_, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 l_, -l_, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-l_, -l_, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-l_,  l_, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
};
