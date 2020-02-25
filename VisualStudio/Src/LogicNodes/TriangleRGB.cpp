#include "TriangleRGB.h"
#include <glad\glad.h>

TriangleRGB::TriangleRGB() : Node() {
	glGenBuffers(1, &_VBO);
	glGenVertexArrays(1, &_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices_rgb), triangle_vertices_rgb, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	_shaderRGB.build("../Shaders/_basic/V_color.glsl", "../Shaders/_basic/F_color.glsl");
}
TriangleRGB::~TriangleRGB() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

void TriangleRGB::render() {
	_shaderRGB.bind();
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
