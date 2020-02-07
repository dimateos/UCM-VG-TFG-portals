/// TFG_dimateos
// Diego Mateos Arlanzon

// WINDOWS
#include <SDL.h>
#include <glad\glad.h>

#include <stdio.h>
#include <iostream>
//#include <string>
using namespace std;

#define UNBIND 0

//const float RES = 16.0f / 9.0f;
const float RES = 1.0f;
const int RES_H = 720;
const int RES_W = RES_H * RES;

///////////////////////////////////////////////////////////////////////////////
//shaders

#include "Shader.h"
Shader squareShader, triangleShader, triangleRGBShader;

///////////////////////////////////////////////////////////////////////////////
//objects

float t_rgb_l = 0.2f, t_l = 0.4f;
float triangle_vertices_rgb[] = {
	// positions				// colors
	-t_rgb_l, -t_rgb_l, 0.0f,	1.0f, 0.0f, 0.0f,   // bottom right
	t_rgb_l, -t_rgb_l, 0.0f,	0.0f, 1.0f, 0.0f,   // bottom left
	0.0f,  t_rgb_l, 0.0f,		0.0f, 0.0f, 1.0f    // top
};
float triangle_vertices[] = {
	// positions
	-t_l, -t_l, 0.0f,
	t_l, -t_l, 0.0f,
	0.0f,  t_l, 0.0f,
};

float s_l = 0.8f;
float square_vertices[] = {
	 s_l,  s_l, 0.0f,  // top right
	 s_l, -s_l, 0.0f,  // bottom right
	-s_l, -s_l, 0.0f,  // bottom left
	-s_l,  s_l, 0.0f   // top left
};
unsigned int indices[] = {  // note that we start from 0
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

unsigned int s_VAO, s_VBO, s_EBO;
unsigned int t_VAO, t_VBO;
unsigned int trgb_VAO, trgb_VBO;

void setupVAOsquare() {
	// 1. bind Vertex Array Object
	glBindVertexArray(s_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(UNBIND);
}
void setupVAOtriangle() {
	// 1. bind Vertex Array Object
	glBindVertexArray(t_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, t_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
void setupVAOtriangleRGB() {
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
}

void setup() {
	//logging info
	printf("GL VERSION: %s\n", glGetString(GL_VERSION));
	printf("GL VENDOR: %s\n", glGetString(GL_VENDOR));
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	std::cout << std::endl;

	//creating the objects
	glGenBuffers(1, &s_VBO);
	glGenBuffers(1, &s_EBO);
	glGenBuffers(1, &t_VBO);
	glGenBuffers(1, &trgb_VBO);

	glGenVertexArrays(1, &s_VAO);
	glGenVertexArrays(1, &t_VAO);
	glGenVertexArrays(1, &trgb_VAO);

	//creating the shaders
	squareShader.build("Shaders/_basic/V_base.glsl", "Shaders/_basic/F_uniform.glsl");
	triangleShader.build("Shaders/_basic/V_base.glsl", "Shaders/_basic/F_base.glsl");
	triangleRGBShader.build("Shaders/_basic/V_color.glsl", "Shaders/_basic/F_color.glsl");

	//creating the VAOs
	setupVAOsquare();
	setupVAOtriangle();
	setupVAOtriangleRGB();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
}

void render(float timish) {
	//clear
	glClearColor(0.1f, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//square
	squareShader.bind();
	float light = (sin(timish) / 2.0f) + 0.5f;
	glUniform4f(squareShader.getUniformLocation("ourColor"), light, light, light, 1.0f);
	glBindVertexArray(s_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//triangle
	triangleShader.bind();
	glBindVertexArray(t_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//triangleRGB
	triangleRGBShader.bind();
	glBindVertexArray(trgb_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBindVertexArray(UNBIND); //no need to unbind every time
}

int run () {
	printf("TFG - init app\n");

	//init sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow(
		"SDL + OpenGL",
		//SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_CENTERED,
		100, 100,
		RES_W, RES_H,
		SDL_WINDOW_OPENGL);

	if (window == NULL) {
		std::cout << "Failed to create SDL window" << std::endl;
		SDL_Quit();
		return -1;
	}

	//init opengl context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext mainContext = SDL_GL_CreateContext(window);
	//use glad loader
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//do the scene setup
	setup();

	// Main loop
	printf("TFG - start loop\n");
	bool exit = false;
	SDL_Event event;

	float timish = 0, stepsih = 0.01;

	//_deltaTimer.start();
	while (!exit) {
		timish += stepsih;

		//events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				exit = true;
			}
			//else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			//	glViewport(0, 0, event.window.data1, event.window.data2);
			//}
		}

		//render
		render(timish);

		//swap
		SDL_GL_SwapWindow(window);
	}
	printf("TFG - end loop\n");

	// Release
	glDeleteVertexArrays(1, &s_VAO);
	glDeleteVertexArrays(1, &t_VAO);
	glDeleteVertexArrays(1, &trgb_VAO);

	glDeleteBuffers(1, &s_VBO);
	glDeleteBuffers(1, &s_EBO);
	glDeleteBuffers(1, &t_VBO);
	glDeleteBuffers(1, &trgb_VBO);

	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("TFG - exit app\n");
	return 0;
}

int main(int argc, char* argv[]) {
	return run();
}