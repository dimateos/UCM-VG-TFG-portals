#include "Cubes3D.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>

Cubes3D::Cubes3D() : Node() {
	glGenBuffers(1, &_VBO);
	glGenVertexArrays(1, &_VAO);

	// 1. bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//build the shader
	_shader3D.build("../Shaders/_basic/V_3D.glsl", "../Shaders/_basic/F_texture.glsl");
	_shader3D.bind(); // don't forget to activate the shader before setting uniforms

	//positioning
	_uniformModel = _shader3D.getUniformLocation("model");
	trans.localScale = glm::vec3(0.8f);

	_initialPos = trans.localPostion;
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	projection = glm::perspective(glm::radians(45.0f),
		(float) Window_SDL_GL::getWidth() / (float)Window_SDL_GL::getHeight(), 0.1f, 100.0f);
	glUniformMatrix4fv(_shader3D.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(_shader3D.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//textures
	_tex1.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	_tex2.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);

	_shader3D.setInt("texture1", 1);
	_shader3D.setInt("texture2", 2);
}
Cubes3D::~Cubes3D() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

void Cubes3D::render() {
	_shader3D.bind();

	_tex1.bind(1);
	_tex2.bind(2);

	//rotate
	trans.localRotation = glm::angleAxis(glm::radians(Platform_SDL::getDeltaTimeSinceStartf() * 25), glm::vec3(0.f, 0.f, 1.f));
	trans.updateModelMatrix();

	glBindVertexArray(_VAO);

	//draw one
	glUniformMatrix4fv(_uniformModel, 1, GL_FALSE, trans.getModelMatrixPtr());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//draw the rest
	for (unsigned int i = 0; i < 9; i++) {
		//m = glm::rotate(m, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
		trans.localPostion = cubePositions[i];
		trans.updateModelMatrix();

		//draw one
		glUniformMatrix4fv(_uniformModel, 1, GL_FALSE, trans.getModelMatrixPtr());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//restore initial transform
		trans.localPostion = _initialPos;
	}
}
