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
//for now here

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.1f, 0.1f, 1.0f);\n"
"}\0";

int  success;
char infoLog[512];

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

unsigned int VBO, VAO, shaderProgram;

void setup() {
	printf("GL VERSION %s\n", glGetString(GL_VERSION));
	printf("GL VENDOR %s\n", glGetString(GL_VENDOR));

	//loading vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//loading vertex shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//activate and delete already linked
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//creating the vao to reuse
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(UNBIND);
}

int main(int argc, char* argv[]) {
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Main loop
	printf("TFG - start loop\n");
	bool exit = false;
	SDL_Event event;

	//_deltaTimer.start();
	while (!exit) {
		//events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				exit = true;
			}
			//else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			//	glViewport(0, 0, event.window.data1, event.window.data2);
			//}

		}

		//update


		//render
		glClearColor(0.1f, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //no need to unbind every time

		//swap
		SDL_GL_SwapWindow(window);
	}
	printf("TFG - end loop\n");

	// Release
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("TFG - exit app\n");
	return 0;
}