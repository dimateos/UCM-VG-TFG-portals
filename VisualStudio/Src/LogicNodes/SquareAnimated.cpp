#include "SquareAnimated.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"

SquareAnimated::SquareAnimated() : Node() {
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glGenVertexArrays(1, &_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	_shaderBasic.build("../Shaders/_basic/V_base.glsl", "../Shaders/_basic/F_uniform.glsl");
	_uniformLocation = _shaderBasic.getUniformLocation("ourColor");
}
SquareAnimated::~SquareAnimated() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_EBO);
	glDeleteBuffers(1, &_VBO);
}

void SquareAnimated::render() {
	_shaderBasic.bind();

	float light = (sin(Platform_SDL::getDeltaTimeSinceStartf()) / 2.0f) + 0.5f;
	glUniform4f(_uniformLocation, light, light, light, 1.0f);

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
