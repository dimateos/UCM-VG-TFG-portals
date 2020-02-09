/// TFG_dimateos
// Diego Mateos Arlanzon

// WINDOWS
#include <SDL.h>
#include <glad\glad.h>
#include <stb.h>

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
Shader squareShader, squareTexShader, triangleShader, triangleRGBShader;

///////////////////////////////////////////////////////////////////////////////
//objects

unsigned int trgb_VAO, trgb_VBO;
float t_rgb_l = 0.2f, t_l = 0.3f;
float triangle_vertices_rgb[] = {
	// positions				// colors
	-t_rgb_l, -t_rgb_l, 0.0f,	1.0f, 0.0f, 0.0f,   // bottom right
	t_rgb_l, -t_rgb_l, 0.0f,	0.0f, 1.0f, 0.0f,   // bottom left
	0.0f,  t_rgb_l, 0.0f,		0.0f, 0.0f, 1.0f    // top
};

unsigned int t_VAO, t_VBO;
float triangle_vertices[] = {
	// positions
	-t_l, -t_l, 0.0f,
	t_l, -t_l, 0.0f,
	0.0f,  t_l, 0.0f,
};

unsigned int s_VAO, s_VBO, s_EBO;
float s_l = 0.9f;
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

///////////////////////////////////////////////////////////////////////////////
//texturing

unsigned int texture1, texture2;

unsigned int st_VAO, st_VBO, st_EBO;
float st_l = 0.6f;
float square_tex_vertices[] = {
	// positions          // texture coords
	 st_l,  st_l, 0.0f,   1.0f, 1.0f,   // top right
	 st_l, -st_l, 0.0f,   1.0f, 0.0f,   // bottom right
	-st_l, -st_l, 0.0f,   0.0f, 0.0f,   // bottom left
	-st_l,  st_l, 0.0f,   0.0f, 1.0f    // top left
};
float square_tex_color_vertices[] = {
	// positions          // colors           // texture coords
	 st_l,  st_l, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 st_l, -st_l, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-st_l, -st_l, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-st_l,  st_l, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

///////////////////////////////////////////////////////////////////////////////
//transformations

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

unsigned int transformLoc;
glm::mat4 trans = glm::mat4(1.0f);

void doSomeTransformations() {
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(0.75f));

	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	std::cout << "x:" << vec.x << " y:" << vec.y << " z:" << vec.z << std::endl;
	vec = trans * vec;
	std::cout << "x:" << vec.x << " y:" << vec.y << " z:" << vec.z << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//setups

bool loadTexture(const std::string &path, unsigned int &texture, int colorMode = GL_RGB, int textureType = GL_TEXTURE_2D) {
	glGenTextures(1, &texture);
	glBindTexture(textureType, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//unused border color
	float borderColor[] = { 0.9f, 0.6f, 0.3f, 1.0f };
	glTexParameterfv(textureType, GL_TEXTURE_BORDER_COLOR, borderColor);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(textureType, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(textureType);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		return false;
	}
	stbi_image_free(data);
	return true;
}

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
void setupVAOsquareTex() {
	// 1. bind Vertex Array Object
	glBindVertexArray(st_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, st_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_tex_color_vertices), square_tex_color_vertices, GL_STATIC_DRAW);
	// 2.5. set index orders
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, st_EBO);
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

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(UNBIND);
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
	glGenBuffers(1, &st_VBO);
	glGenBuffers(1, &s_EBO);
	glGenBuffers(1, &st_EBO);
	glGenBuffers(1, &t_VBO);
	glGenBuffers(1, &trgb_VBO);

	glGenVertexArrays(1, &s_VAO);
	glGenVertexArrays(1, &st_VAO);
	glGenVertexArrays(1, &t_VAO);
	glGenVertexArrays(1, &trgb_VAO);

	//creating the shaders
	squareShader.build("Shaders/_basic/V_base.glsl", "Shaders/_basic/F_uniform.glsl");
	triangleShader.build("Shaders/_basic/V_base.glsl", "Shaders/_basic/F_base.glsl");
	triangleRGBShader.build("Shaders/_basic/V_color.glsl", "Shaders/_basic/F_color.glsl");
	squareTexShader.build("Shaders/_basic/V_transform_c.glsl", "Shaders/_basic/F_texture_c.glsl");

	//some transforms
	doSomeTransformations();

	//loading textured
	stbi_set_flip_vertically_on_load(true);
	loadTexture("Assets/_basic/container.jpg", texture1);
	loadTexture("Assets/_basic/awesomeface.png", texture2, GL_RGBA);
	squareTexShader.bind(); // don't forget to activate the shader before setting uniforms
	squareTexShader.setInt("texture1", 0);
	squareTexShader.setInt("texture2", 1);
	transformLoc = squareTexShader.getUniformLocation("transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//creating the VAOs
	setupVAOsquare();
	setupVAOtriangle();
	setupVAOtriangleRGB();
	setupVAOsquareTex();
}

void render(float timish) {
	//clear
	glClearColor(0.1f, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//animated square
	squareShader.bind();
	float light = (sin(timish) / 2.0f) + 0.5f;
	glUniform4f(squareShader.getUniformLocation("ourColor"), light, light, light, 1.0f);
	glBindVertexArray(s_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//textured square
	squareTexShader.bind();
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
		glm::value_ptr(glm::rotate(trans, glm::radians(timish*25), glm::vec3(0.0, 0.0, 1.0))));
	glActiveTexture(GL_TEXTURE0); // activate the texture unit (0 is default so no need if only 1 unit)
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindVertexArray(st_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//triangle
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	triangleShader.bind();
	glBindVertexArray(t_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	glDeleteVertexArrays(1, &st_VAO);
	glDeleteVertexArrays(1, &t_VAO);
	glDeleteVertexArrays(1, &trgb_VAO);

	glDeleteBuffers(1, &s_VBO);
	glDeleteBuffers(1, &st_VBO);
	glDeleteBuffers(1, &s_EBO);
	glDeleteBuffers(1, &st_EBO);
	glDeleteBuffers(1, &t_VBO);
	glDeleteBuffers(1, &trgb_VBO);

	//glDeleteTextures

	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("TFG - exit app\n");
	return 0;
}

int main(int argc, char* argv[]) {
	return run();
}