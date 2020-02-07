#include "Shader.h"
#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {}
Shader::~Shader() {
	destroy();
}
void Shader::destroy() {
	if (ID != -1) {
		glDeleteProgram(ID);
		ID = -1;
	}
}

bool Shader::build(const std::string & vertexPath, const std::string & fragmentPath) {
	return build(vertexPath.c_str(), vertexPath.c_str());
}
bool Shader::build(const char * vertexPath, const char * fragmentPath) {
	if (ID != -1) {
		std::cout << "ERROR::SHADER::PROGRAM::ALREADYBUILT\n" << std::endl;
		return false;
	}

	// 1. retrieve the vertex/fragment source code from filePath
	std::string vShaderCode = loadFileContent(vertexPath);
	if (vShaderCode == "") return false;
	std::string fShaderCode = loadFileContent(fragmentPath);
	if (fShaderCode == "") return false;

	// 2. compile shaders
	unsigned int vertex = compileShader(vShaderCode.c_str(), GL_VERTEX_SHADER);
	if (vertex == -1) return false;
	unsigned int fragment = compileShader(fShaderCode.c_str(), GL_FRAGMENT_SHADER);
	if (fragment == -1) return false;

	// 3. link shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	// print linking errors if any
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		ID = -1;
		return false;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return true;
}

void Shader::bind() {
	glUseProgram(ID);
}

int Shader::getUniformLocation(const std::string & name) const {
	return glGetUniformLocation(ID, name.c_str());
}
bool Shader::setBool(const std::string & name, bool value) const {
	int pos = glGetUniformLocation(ID, name.c_str());
	if (pos == -1) return false;
	glUniform1i(pos, (int)value);
	return true;
}
bool Shader::setInt(const std::string & name, int value) const {
	int pos = glGetUniformLocation(ID, name.c_str());
	if (pos == -1) return false;
	glUniform1i(pos, value);
	return true;
}
bool Shader::setFloat(const std::string & name, float value) const {
	int pos = glGetUniformLocation(ID, name.c_str());
	if (pos == -1) return false;
	glUniform1f(pos, value);
	return true;
}

std::string Shader::loadFileContent(const char * path) {
	std::string s = "";
	std::ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open files
		file.open(path);
		// read file's buffer contents into streams
		std::stringstream stream;
		stream << file.rdbuf();
		// close file handlers
		file.close();

		// convert stream into string
		s = stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		s = "";
	}

	return s;
}

unsigned int Shader::compileShader(const char* code, int shaderType) {
	unsigned int shId = -1;
	int success;
	char infoLog[512];

	// vertex Shader
	shId = glCreateShader(shaderType);
	glShaderSource(shId, 1, &code, NULL);
	glCompileShader(shId);

	// print compile errors if any
	glGetShaderiv(shId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		shId = -1;
	};

	return shId;
}
