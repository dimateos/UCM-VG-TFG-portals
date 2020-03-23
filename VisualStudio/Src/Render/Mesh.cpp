#include "Mesh.h"
#include <glad\glad.h>

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

//for now here

CubeMesh::CubeMesh() {
	glGenBuffers(1, &VBO_);
	glGenVertexArrays(1, &VAO_);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO_);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
CubeMesh::~CubeMesh() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}
void CubeMesh::draw() {
	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

PlaneMesh::PlaneMesh() {
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glGenVertexArrays(1, &VAO_);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO_);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_tex_vertices_), square_tex_vertices_, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
PlaneMesh::~PlaneMesh() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteBuffers(1, &VBO_);
}
void PlaneMesh::draw() {
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
