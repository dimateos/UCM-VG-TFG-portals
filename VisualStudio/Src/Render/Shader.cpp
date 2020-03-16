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
	if (ID_ != -1) {
		glDeleteProgram(ID_);
		ID_ = -1;
	}
}

bool Shader::build(const std::string & vertexPath, const std::string & fragmentPath) {
	return build(vertexPath.c_str(), vertexPath.c_str());
}
bool Shader::build(const char * vertexPath, const char * fragmentPath) {
	if (ID_ != -1) {
		std::cout << "ERROR::SHADER::PROGRAM::ALREADYBUILT\n" << std::endl;
		std::cout << vertexPath << fragmentPath << std::endl;
		return false;
	}

	// 1. retrieve the vertex/fragment source code from filePath
	std::string vShaderCode = loadFileContent(vertexPath);
	if (vShaderCode == "") return buildError(vertexPath);
	std::string fShaderCode = loadFileContent(fragmentPath);
	if (fShaderCode == "") return buildError(fragmentPath);

	// 2. compile shaders
	unsigned int vertex = compileShader(vShaderCode.c_str(), GL_VERTEX_SHADER);
	if (vertex == -1) return buildError(vertexPath);;
	unsigned int fragment = compileShader(fShaderCode.c_str(), GL_FRAGMENT_SHADER);
	if (fragment == -1) return buildError(fragmentPath);;

	// 3. link shader program
	ID_ = glCreateProgram();
	glAttachShader(ID_, vertex);
	glAttachShader(ID_, fragment);
	glLinkProgram(ID_);

	// print linking errors if any
	int success;
	char infoLog[512];
	glGetProgramiv(ID_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		std::cout << vertexPath << fragmentPath << std::endl;
		ID_ = -1;
		return false;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return true;
}
bool Shader::buildError(const std::string & path) const {
	std::cout << path << std::endl;
	std::cout << "/////////////////////////////////////////////////////////////" << std::endl << std::endl;
	return false;
}

void Shader::bind() {
	glUseProgram(ID_);
}
void Shader::unbind() {
	glUseProgram(0);
}

int Shader::getUniformLocation(const std::string & name) const {
	int pos = glGetUniformLocation(ID_, name.c_str());
	if (pos == -1) setError(name);
	return pos;
}
bool Shader::setBool(const std::string & name, bool value) const {
	int pos = glGetUniformLocation(ID_, name.c_str());
	if (pos == -1) return setError(name);
	glUniform1i(pos, (int)value);
	return true;
}
bool Shader::setInt(const std::string & name, int value) const {
	int pos = glGetUniformLocation(ID_, name.c_str());
	if (pos == -1) return setError(name);
	glUniform1i(pos, value);
	return true;
}
bool Shader::setFloat(const std::string & name, float value) const {
	int pos = glGetUniformLocation(ID_, name.c_str());
	if (pos == -1) return setError(name);
	glUniform1f(pos, value);
	return true;
}
bool Shader::setError(const std::string & name) const {
	std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND" << std::endl;
	std::cout << name << std::endl;
	std::cout << "/////////////////////////////////////////////////////////////" << std::endl << std::endl;
	return false;
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
		std::cout << path << std::endl;
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
		std::cout << code << std::endl;
		shId = -1;
	};

	return shId;
}
