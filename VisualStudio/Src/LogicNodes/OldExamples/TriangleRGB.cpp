#include "TriangleRGB.h"
#include <glad\glad.h>

TriangleRGB::TriangleRGB() : Node(&Node::ROOT) {
	glGenBuffers(1, &VBO_);
	glGenVertexArrays(1, &VAO_);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO_);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices_rgb_), triangle_vertices_rgb_, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shaderRGB_.build("../Shaders/_basic/V_color.glsl", "../Shaders/_basic/F_color.glsl");
}
TriangleRGB::~TriangleRGB() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}

void TriangleRGB::render() {
	shaderRGB_.bind();
	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
