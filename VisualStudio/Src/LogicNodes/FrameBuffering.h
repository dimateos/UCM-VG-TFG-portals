#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"

class FrameBuffering : public Node
{
public:
	FrameBuffering(Node* father);
	virtual ~FrameBuffering();

	void bindFrameBuffer();

	virtual void render();

protected:
	Shader shaderScreen_, postFilterShader_;
	Texture tex1_; //testing
	unsigned int framebuffer_, texColorBuffer_;
	float res_, preview_res_; //resolution for the texture (multi/down sampling)

	unsigned int VAO_, VBO_, EBO_;
	float l_ = 1.0f; //size of screen
	unsigned int indices_[6] = {  // note that we start from 0
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float square_tex_vertices_[4 * 5] = {
		// positions          // texture coords
		 l_,  l_, 0.0f,   1.0f, 1.0f,   // top right
		 l_, -l_, 0.0f,   1.0f, 0.0f,   // bottom right
		-l_, -l_, 0.0f,   0.0f, 0.0f,   // bottom left
		-l_,  l_, 0.0f,   0.0f, 1.0f    // top left
	};
};
