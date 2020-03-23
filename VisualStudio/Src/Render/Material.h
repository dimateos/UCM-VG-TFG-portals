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

	Shader* shader_;
};

//for now here
class SolidMaterial : public Material
{
public:
	SolidMaterial(glm::vec3 const& color, Texture* tex);
	virtual ~SolidMaterial();
	virtual void bind();

	static Shader SOLID_MAT_SHADER; //for now
	static unsigned int UNIFORM_COLOR;

	glm::vec3 color_;
	Texture* tex_;
};