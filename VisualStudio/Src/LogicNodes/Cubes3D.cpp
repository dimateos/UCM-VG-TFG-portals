#include "Cubes3D.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>


Cubes3D::Cubes3D(Camera * cam) : Node(&Node::ROOT), cam_(cam) {
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

	//build the shader
	shader3D_.build("../Shaders/_basic/V_3D.glsl", "../Shaders/_basic/F_texture.glsl");
	shader3D_.bind(); // don't forget to activate the shader before setting uniforms

	//positioning
	uniformModel_ = shader3D_.getUniformLocation("model");
	trans.localScale = glm::vec3(0.8f);

	initialPos_ = trans.localPostion;
	glUniformMatrix4fv(shader3D_.getUniformLocation("projection"), 1, GL_FALSE, cam_->getProj()->getProjMatrixPtr());

	cam_->trans.localPostion.z = 5;
	cam_->trans.localScale.x = 0.5;
	cam_->trans.localRotation = glm::angleAxis(glm::radians(30.0f), glm::vec3(1.f, 0.f, 0.f));
	cam_->trans.updateInvModelMatrix();
	glUniformMatrix4fv(shader3D_.getUniformLocation("view"), 1, GL_FALSE, cam_->getViewMatrixPtr());

	//textures
	tex1_.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	tex2_.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);

	shader3D_.setInt("texture1", 1);
	shader3D_.setInt("texture2", 2);

	Platform_SDL::_keyEventEmitter.registerListener(this);
	rotationAngle_ = glm::vec3(0.f, 0.f, 1.f);
}
Cubes3D::~Cubes3D() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}

bool Cubes3D::handleEvent(SDL_Event const & e) {
	bool handled = false;

	if (e.type == SDL_KEYDOWN) {
		handled = true;

		switch (e.key.keysym.sym) {
			case SDLK_1: rotationAngle_ = glm::vec3(1.f, 0.f, 0.f); break;
			case SDLK_2: rotationAngle_ = glm::vec3(0.f, 1.f, 0.f); break;
			case SDLK_3: rotationAngle_ = glm::vec3(0.f, 0.f, 1.f); break;

			case SDLK_RIGHT: xAxis_.push_front(RIGHT); break;
			case SDLK_LEFT: xAxis_.push_front(LEFT); break;
			case SDLK_DOWN: yAxis_.push_front(DOWN); break;
			case SDLK_UP: yAxis_.push_front(UP); break;

			default: handled = false;
		}
	}
	else if (e.type == SDL_KEYUP) {
		handled = true;

		switch (e.key.keysym.sym) {
		case SDLK_RIGHT: xAxis_.remove(RIGHT); break;
		case SDLK_LEFT: xAxis_.remove(LEFT); break;
		case SDLK_DOWN: yAxis_.remove(DOWN); break;
		case SDLK_UP: yAxis_.remove(UP); break;

		default: handled = false;
		}
	}

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void Cubes3D::update() {
	velocity_ = glm::vec3(0);

	if (!yAxis_.empty()) {
		if (yAxis_.front() == UP) velocity_.y = 1;
		else velocity_.y = -1;
	}
	if (!xAxis_.empty()) {
		if (xAxis_.front() == RIGHT) velocity_.x = 1;
		else velocity_.x = -1;
	}

	if (velocity_.y != 0 || velocity_.x != 0) {
		velocity_ = glm::normalize(velocity_) * speed_;
		trans.localPostion += velocity_ * Platform_SDL::getDeltaTimef();
	}
}

void Cubes3D::render() {
	shader3D_.bind();

	tex1_.bind(1);
	tex2_.bind(2);

	//rotate
	trans.localRotation = glm::angleAxis(glm::radians(Platform_SDL::getDeltaTimeSinceStartf() * 25.0f), rotationAngle_);
	trans.updateModelMatrix();

	glBindVertexArray(VAO_);

	//draw one
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, trans.getModelMatrixPtr());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//draw the rest
	initialPos_ = trans.localPostion;
	for (unsigned int i = 0; i < 9; i++) {
		//m = glm::rotate(m, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
		trans.localPostion = cubePositions_[i];
		trans.updateModelMatrix();

		//draw one
		glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, trans.getModelMatrixPtr());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//restore initial transform
	trans.localPostion = initialPos_;
}
