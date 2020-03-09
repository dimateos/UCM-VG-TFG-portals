#include "SquareTextured.h"
#include <glad\glad.h>

SquareTextured::SquareTextured() : Node() {
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glGenVertexArrays(1, &_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_tex_color_vertices), square_tex_color_vertices, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	_shaderTextured.build("../Shaders/_basic/V_transform_c.glsl", "../Shaders/_basic/F_texture_c.glsl");

	//transforming
	_uniformTranform = _shaderTextured.getUniformLocation("transform");
	trans.localScale = glm::vec3(0.8f);

	//textures
	_tex1.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	_tex2.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);

	_shaderTextured.bind(); // don't forget to activate the shader before setting uniforms
	_shaderTextured.setInt("texture1", 1);
	_shaderTextured.setInt("texture2", 2);
}
SquareTextured::~SquareTextured() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_EBO);
	glDeleteBuffers(1, &_VBO);
}

void SquareTextured::update(float delta) {
	_timish += delta;
}

void SquareTextured::render() {
	_shaderTextured.bind();

	_tex1.bind(1);
	_tex2.bind(2);

	trans.localRotation = glm::angleAxis(glm::radians(_timish * 25), glm::vec3(0.f, 0.f, 1.f));
	trans.updateModelMatrix();
	glUniformMatrix4fv(_uniformTranform, 1, GL_FALSE, trans.getModelMatrixPtr());

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
