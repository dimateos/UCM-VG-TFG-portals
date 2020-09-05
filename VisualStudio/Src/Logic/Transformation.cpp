#include "Transformation.h"

#include <gtc/epsilon.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

#include <gtx/matrix_decompose.hpp> //for now

const glm::vec3 Transformation::BASE_UP = Y;
const glm::vec3 Transformation::BASE_RIGHT = X;
const glm::vec3 Transformation::BASE_BACK = Z;
const glm::vec3 Transformation::BASE_POS = ZEROS;
const glm::vec3 Transformation::BASE_SCALE = ONES;
const glm::quat Transformation::BASE_ROT = IDENTITY_QUAT;
//const glm::quat Transformation::BASE_ROT = glm::angleAxis(glm::radians(0.f), BASE_UP);

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
	//for our purposes conjugate can do (cheaper than inverse)
	glm::mat4 r = glm::mat4_cast(glm::conjugate(rotation));
	glm::mat4 s = glm::scale(IDENTITY_MAT, 1.0f / scale);

	return s * r * t;
}

Transformation Transformation::getDescomposed(glm::mat4 const & trans) {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(trans, scale, rotation, translation, skew, perspective);

	return { translation, rotation, scale };
}

bool Transformation::operator==(const Transformation & other) const {
	return glm::all(glm::epsilonEqual(postion, other.postion, EPSILON))
		&& glm::all(glm::epsilonEqual(rotation, other.rotation, EPSILON))
		&& glm::all(glm::epsilonEqual(scale, other.scale, EPSILON));
}
bool Transformation::operator!=(const Transformation & other) const {
	return !(*this == other);
}

#include <iostream>
void Transformation::toBuffer(char * buffer) const {
	sprintf(buffer,
		"T: { %f, %f, %f } R: { %f, %f, %f %f } S: { %f, %f, %f }",
		postion.x, postion.y, postion.z, rotation.x, rotation.y, rotation.z, rotation.w, scale.x, scale.y, scale.z);
}