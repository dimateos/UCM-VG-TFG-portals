#include "Transformation.h"

#include <gtc/matrix_transform.hpp>
using namespace glm;

const glm::vec3 Transformation::BASE_UP = Y;
const glm::vec3 Transformation::BASE_RIGHT = X;
const glm::vec3 Transformation::BASE_BACK = Z;
const glm::vec3 Transformation::BASE_POS = ZEROS;
const glm::vec3 Transformation::BASE_SCALE = ONES;
const glm::quat Transformation::BASE_ROT = glm::angleAxis(glm::radians(0.f), BASE_UP); //IDENTITY_QUAT

const Transformation Transformation::BASE = {
	Transformation::BASE_POS, Transformation::BASE_ROT, Transformation::BASE_SCALE
};

glm::mat4 Transformation::matrix() const {
	//multiply ordered matrices
	glm::mat4 t = glm::translate(IDENTITY_MAT, postion);
	glm::mat4 r = glm::mat4_cast(rotation);
	glm::mat4 s = glm::scale(IDENTITY_MAT, scale);
	return t * r * s;
}

glm::mat4 Transformation::matrix_Inversed() const {
	//multiply ordered matrices with the inverse operations
	glm::mat4 t = glm::translate(IDENTITY_MAT, -postion);
	glm::mat4 r = glm::mat4_cast(glm::inverse(rotation));
	glm::mat4 s = glm::scale(IDENTITY_MAT, 1.0f / scale);

	//return t * r * s;
	return s * r * t;
}
