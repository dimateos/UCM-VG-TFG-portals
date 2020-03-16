#include "SquareTextured.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"

SquareTextured::SquareTextured() : Node() {
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glGenVertexArrays(1, &VAO_);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO_);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_tex_color_vertices_), square_tex_color_vertices_, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//build the shader
	shaderTextured_.build("../Shaders/_basic/V_transform_c.glsl", "../Shaders/_basic/F_texture_c.glsl");

	//transforming
	uniformTranform_ = shaderTextured_.getUniformLocation("transform");
	trans.localScale = glm::vec3(0.8f);

	//textures
	tex1_.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	tex2_.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);

	shaderTextured_.bind(); // don't forget to activate the shader before setting uniforms
	shaderTextured_.setInt("texture1", 1);
	shaderTextured_.setInt("texture2", 2);
}
SquareTextured::~SquareTextured() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteBuffers(1, &VBO_);
}

void SquareTextured::render() {
	shaderTextured_.bind();

	tex1_.bind(1);
	tex2_.bind(2);

	trans.localRotation = glm::angleAxis(glm::radians(Platform_SDL::getDeltaTimeSinceStartf() * 25), glm::vec3(0.f, 0.f, 1.f));
	trans.updateModelMatrix();
	glUniformMatrix4fv(uniformTranform_, 1, GL_FALSE, trans.getModelMatrixPtr());

	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
