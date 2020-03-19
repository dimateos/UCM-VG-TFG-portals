#include "Cube.h"
#include <glad\glad.h>

#include "../Logic/Camera.h" //tmp
#include "../Platform/Platform_SDL.h"

Cube::Cube(Node * father) : Node(father) {
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

	//textures
	tex1_.load("../Assets/_basic/container.jpg", GL_TEXTURE_2D);
	tex2_.load("../Assets/_basic/awesomeface.png", GL_TEXTURE_2D);
	shader3D_.setInt("texture1", 1);
	shader3D_.setInt("texture2", 2);

	//positioning
	uniformModel_ = shader3D_.getUniformLocation("model");

	//camera
	glUniformMatrix4fv(shader3D_.getUniformLocation("projection"), 1, GL_FALSE, Node::ROOT_CAM->getProj()->getProjMatrixPtr());
	uniformView_ = shader3D_.getUniformLocation("view");
}
Cube::~Cube() {
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}

void Cube::render() {
	shader3D_.bind();

	tex1_.bind(1);
	tex2_.bind(2);

	//movable camera
	glUniformMatrix4fv(uniformView_, 1, GL_FALSE, Node::ROOT_CAM->getViewMatrixPtr());

	//draw
	glBindVertexArray(VAO_);
	glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, getModelMatrix_ptr());
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
