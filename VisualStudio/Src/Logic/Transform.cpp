#include "Transform.h"

//#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Transform::Transform() {
	fatherPostion = glm::vec3(0.0f);
	localPostion = glm::vec3(0.0f);
	localScale = glm::vec3(1.0f);
	localRotation = glm::angleAxis(glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
}

Transform::~Transform() {}

glm::mat4 Transform::getModelMatrix() const {
	glm::mat4 translate = glm::translate(glm::mat4(1.0), localPostion);
	glm::mat4 rotate = glm::mat4_cast(localRotation);
	glm::mat4 scale = glm::scale(glm::mat4(1.0), localScale);

	return translate * rotate * scale;
}


