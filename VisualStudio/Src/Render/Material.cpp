#include "Material.h"
#include <glad\glad.h>

Material::Material(Shader* shader) : shader_(shader) {}
Material::~Material() {}

Shader SolidMaterial::SOLID_MAT_SHADER = Shader();
unsigned int SolidMaterial::UNIFORM_COLOR = 0;
unsigned int SolidMaterial::UNIFORM_OPTION = 0;

SolidMaterial::SolidMaterial(glm::vec3 const & color, Texture* tex)
	: Material(&SOLID_MAT_SHADER), color_(color), tex_(tex) {
}
SolidMaterial::~SolidMaterial() {
}

void SolidMaterial::bind() {
	glUniform3f(UNIFORM_COLOR, color_.x, color_.y, color_.z);
	glUniform1i(UNIFORM_OPTION, option_);
	tex_->bind();
}