#pragma once
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	void destroy();

	//reads and builds the shader
	bool build(const std::string &vertexPath, const std::string &fragmentPath);
	bool build(const char* vertexPath, const char* fragmentPath);
	unsigned int getID();

	// use/activate the shader
	void bind();

	// utility uniform functions
	int getUniformLocation(const std::string &name) const;
	bool setBool(const std::string &name, bool value) const;
	bool setInt(const std::string &name, int value) const;
	bool setFloat(const std::string &name, float value) const;

protected:
	// the program ID
	unsigned int _ID = -1;

	//could go to some utils
	static std::string loadFileContent(const char* path);
	static unsigned int compileShader(const char* code, int shaderType);

	//informative errors
	bool buildError(const std::string & path) const;
	bool setError(const std::string & name) const;
};
