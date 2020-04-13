#pragma once
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include <glm.hpp>

class Material
{
public:
	Material(Shader* shader);
	virtual ~Material();
	virtual void bind() = 0;
	virtual void unbind() = 0;

	Shader* shader_;
};

//for now here
class SolidMaterial : public Material
{
public:
	SolidMaterial(glm::vec3 const& color, Texture* tex);
	virtual ~SolidMaterial();
	virtual void bind();
	virtual void unbind();

	static Shader SOLID_MAT_SHADER; //for now
	static unsigned int UNIFORM_COLOR, UNIFORM_OPTION;

	glm::vec3 color_;
	Texture* tex_;
	int option_ = 0; //quick hack to test shader options for portals
};