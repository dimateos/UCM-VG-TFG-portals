#include "Cubes3D.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>


Cubes3D::Cubes3D(Camera * cam) : Node(), _cam(cam) {
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
	glUniformMatrix4fv(_shader3D.getUniformLocation("projection"), 1, GL_FALSE, _cam->getProj()->getProjMatrixPtr());

	_cam->trans.localPostion.z = 5;
	_cam->trans.localScale.x = 0.5;
	_cam->trans.localRotation = glm::angleAxis(glm::radians(30.0f), glm::vec3(1.f, 0.f, 0.f));
	_cam->trans.updateInvModelMatrix();
	glUniformMatrix4fv(_shader3D.getUniformLocation("view"), 1, GL_FALSE, _cam->getViewMatrixPtr());

	//textures
	_tex1.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	_tex2.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);

	_shader3D.setInt("texture1", 1);
	_shader3D.setInt("texture2", 2);

	Platform_SDL::_keyEventEmitter.registerListener(this);
	_rotationAngle = glm::vec3(0.f, 0.f, 1.f);
}
Cubes3D::~Cubes3D() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

bool Cubes3D::handleEvent(SDL_Event const & e) {
	bool handled = false;

	if (e.type == SDL_KEYDOWN) {
		handled = true;

		switch (e.key.keysym.sym) {
			case SDLK_1: _rotationAngle = glm::vec3(1.f, 0.f, 0.f); break;
			case SDLK_2: _rotationAngle = glm::vec3(0.f, 1.f, 0.f); break;
			case SDLK_3: _rotationAngle = glm::vec3(0.f, 0.f, 1.f); break;

			case SDLK_RIGHT: _xAxis.push_front(RIGHT); break;
			case SDLK_LEFT: _xAxis.push_front(LEFT); break;
			case SDLK_DOWN: _yAxis.push_front(DOWN); break;
			case SDLK_UP: _yAxis.push_front(UP); break;

			default: handled = false;
		}
	}
	else if (e.type == SDL_KEYUP) {
		handled = true;

		switch (e.key.keysym.sym) {
		case SDLK_RIGHT: _xAxis.remove(RIGHT); break;
		case SDLK_LEFT: _xAxis.remove(LEFT); break;
		case SDLK_DOWN: _yAxis.remove(DOWN); break;
		case SDLK_UP: _yAxis.remove(UP); break;

		default: handled = false;
		}
	}

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void Cubes3D::update() {
	_velocity = glm::vec3(0);

	if (!_yAxis.empty()) {
		if (_yAxis.front() == UP) _velocity.y = 1;
		else _velocity.y = -1;
	}
	if (!_xAxis.empty()) {
		if (_xAxis.front() == RIGHT) _velocity.x = 1;
		else _velocity.x = -1;
	}

	if (_velocity.y != 0 || _velocity.x != 0) {
		_velocity = glm::normalize(_velocity) * _speed;
		trans.localPostion += _velocity * Platform_SDL::getDeltaTimef();
	}
}

void Cubes3D::render() {
	_shader3D.bind();

	_tex1.bind(1);
	_tex2.bind(2);

	//rotate
	trans.localRotation = glm::angleAxis(glm::radians(Platform_SDL::getDeltaTimeSinceStartf() * 25.0f), _rotationAngle);
	trans.updateModelMatrix();

	glBindVertexArray(_VAO);

	//draw one
	glUniformMatrix4fv(_uniformModel, 1, GL_FALSE, trans.getModelMatrixPtr());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//draw the rest
	_initialPos = trans.localPostion;
	for (unsigned int i = 0; i < 9; i++) {
		//m = glm::rotate(m, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
		trans.localPostion = cubePositions[i];
		trans.updateModelMatrix();

		//draw one
		glUniformMatrix4fv(_uniformModel, 1, GL_FALSE, trans.getModelMatrixPtr());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//restore initial transform
	trans.localPostion = _initialPos;
}
