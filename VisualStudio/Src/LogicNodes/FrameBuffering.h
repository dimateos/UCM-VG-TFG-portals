#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Render/Mesh.h"

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

	Mesh * mesh_;
};
