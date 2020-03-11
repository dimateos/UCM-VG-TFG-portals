#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"

class SquareTextured : public Node
{
public:
	SquareTextured();
	virtual ~SquareTextured();

	virtual void render();

protected:
	Shader _shaderTextured;
	Texture _tex1, _tex2;
	unsigned int _uniformTranform;

	unsigned int _VAO, _VBO, _EBO;
	float _l = 0.6f;
	unsigned int indices[6] = {  // note that we start from 0
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float square_tex_vertices[4*5] = {
		// positions          // texture coords
		 _l,  _l, 0.0f,   1.0f, 1.0f,   // top right
		 _l, -_l, 0.0f,   1.0f, 0.0f,   // bottom right
		-_l, -_l, 0.0f,   0.0f, 0.0f,   // bottom left
		-_l,  _l, 0.0f,   0.0f, 1.0f    // top left
	};
	float square_tex_color_vertices[4*8] = {
		// positions		// colors           // texture coords
		 _l,  _l, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 _l, -_l, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-_l, -_l, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-_l,  _l, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
};
