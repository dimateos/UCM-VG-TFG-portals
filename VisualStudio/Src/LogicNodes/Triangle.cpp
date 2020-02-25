#include "Triangle.h"
#include <glad\glad.h>

Triangle::Triangle() : Node() {
	glGenBuffers(1, &_VBO);
	glGenVertexArrays(1, &_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); //0 unbinds
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	_shaderBasic.build("../Shaders/_basic/V_base.glsl", "../Shaders/_basic/F_base.glsl");
}
Triangle::~Triangle() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

void Triangle::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_shaderBasic.bind();
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
