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
	Shader triangleRGBShader;
	unsigned int trgb_VAO, trgb_VBO;
	float t_rgb_l = 0.2f;
	float triangle_vertices_rgb[6*3] = {
		// positions				// colors
		-t_rgb_l, -t_rgb_l, 0.0f,	1.0f, 0.0f, 0.0f,   // bottom right
		t_rgb_l, -t_rgb_l, 0.0f,	0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  t_rgb_l, 0.0f,		0.0f, 0.0f, 1.0f    // top
	};
};
