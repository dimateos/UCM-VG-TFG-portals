#include "SquareAnimated.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"

SquareAnimated::SquareAnimated() : Node(&Node::ROOT) {
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glGenVertexArrays(1, &VAO_);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO_);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices_), square_vertices_, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shaderBasic_.build("../Shaders/_basic/V_base.glsl", "../Shaders/_basic/F_uniform.glsl");
	uniformLocation_ = shaderBasic_.getUniformLocation("ourColor");
}
SquareAnimated::~SquareAnimated() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteBuffers(1, &VBO_);
}

void SquareAnimated::render() {
	shaderBasic_.bind();

	float light = (sin(Platform_SDL::getDeltaTimeSinceStartf()) / 2.0f) + 0.5f;
	glUniform4f(uniformLocation_, light, light, light, 1.0f);

	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
