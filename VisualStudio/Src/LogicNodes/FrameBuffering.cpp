#include "FrameBuffering.h"
#include <glad\glad.h>
#include <iostream>

#include "../Logic/Camera.h" //tmp
#include "../Platform/Platform_SDL.h"
#include "../Platform/Window_SDL_GL.h"

FrameBuffering::FrameBuffering(Node * father) : Node(father) {
	//MESH
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

	//SHADER
	shaderScreen_.build("../Shaders/V_screenTexture.glsl", "../Shaders/F_screenTexture.glsl"); //unused
	postFilterShader_.build("../Shaders/V_screenTexture.glsl", "../Shaders/F_screenTexture_postFiltering.glsl");
	tex1_.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D); //for testnf unused

	//TEXTURE
	res_ = 2.0f;
	preview_res_ = 0.25;
	glGenTextures(1, &texColorBuffer_);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window_SDL_GL::getWidth() * res_, Window_SDL_GL::getHeight() * res_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST
	glBindTexture(GL_TEXTURE_2D, 0); //unbind just in case

	//FRAME BUFFER
	glGenFramebuffers(1, &framebuffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer_, 0);

	//available depth test
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window_SDL_GL::getWidth() * res_, Window_SDL_GL::getHeight() * res_);
	glBindRenderbuffer(GL_RENDERBUFFER, 0); //unbind
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	//..delete render buffer

	//check errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind
}
FrameBuffering::~FrameBuffering() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteBuffers(1, &VBO_);

	glDeleteTextures(1, &texColorBuffer_);
	glDeleteFramebuffers(1, &framebuffer_);
}

void FrameBuffering::bindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
	glViewport(0, 0, Window_SDL_GL::getWidth() * res_, Window_SDL_GL::getWidth() * res_);
}

void FrameBuffering::render() {
	postFilterShader_.bind();
	postFilterShader_.setFloat("time", Platform_SDL::getDeltaTimeSinceStartf() * 2.0f);
	postFilterShader_.setInt("option", 3);
	glViewport(0, 0, Window_SDL_GL::getWidth(), Window_SDL_GL::getWidth());

	glBindVertexArray(VAO_);
	//glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0); //other shaders may have changed this
	glBindTexture(GL_TEXTURE_2D, texColorBuffer_);
	//glBindTexture(GL_TEXTURE_2D, tex1_.getID());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //to check the quad on top
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	postFilterShader_.setInt("option", 0);
	glViewport(0, 0, Window_SDL_GL::getWidth() *preview_res_, Window_SDL_GL::getWidth() *preview_res_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glViewport(0, 0, Window_SDL_GL::getWidth(), Window_SDL_GL::getWidth());
}