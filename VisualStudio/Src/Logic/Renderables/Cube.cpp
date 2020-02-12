#include "Cube.h"
#include <glad\glad.h>

Cube::Cube() {
	glGenBuffers(1, &trgb_VBO);
	glGenVertexArrays(1, &trgb_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(trgb_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, trgb_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices_rgb), triangle_vertices_rgb, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	triangleRGBShader.build("../Shaders/_basic/V_color.glsl", "../Shaders/_basic/F_color.glsl");
}
Cube::~Cube() {
	glDeleteVertexArrays(1, &trgb_VAO);
	glDeleteBuffers(1, &trgb_VBO);
}

void Cube::draw(float delta, glm::mat4 modelMatrix) {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	triangleRGBShader.bind();
	glBindVertexArray(trgb_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
