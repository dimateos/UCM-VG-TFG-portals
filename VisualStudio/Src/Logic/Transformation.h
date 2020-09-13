#pragma once
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

//common directions
enum Direction { RIGHT, LEFT, DOWN, UP, BACK, FORE }; //ordered as SDL enums

//epsilon used for comparisons
const float EPSILON = 1E-6; //same precision as vector
//sign using custom EPSILON
inline float fsgn(float f) {
	if (f > EPSILON) return (1.0F);
	if (f < -EPSILON) return (-1.0F);
	return (0.0F);
}
inline int sgn(float f) {
	if (f > EPSILON) return 1;
	if (f < -EPSILON) return -1;
	return 0;
}

//common vectors
const glm::vec3 X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Z = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 ZEROS = glm::vec3(0.0f);
const glm::vec3 ONES = glm::vec3(1.0f);
const glm::mat4 IDENTITY_MAT = glm::mat4(1.0);
const glm::quat IDENTITY_QUAT = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

//transformation struct
struct Transformation
{
public:
	glm::vec3 postion;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 matrix() const;
	glm::mat4 matrix_Inversed() const;

	//static common reference
	static const glm::vec3 BASE_RIGHT, BASE_UP, BASE_BACK;
	static const glm::vec3 BASE_POS, BASE_SCALE;
	static const glm::quat BASE_ROT;
	static const Transformation BASE;

	static Transformation getDecomposed(glm::mat4 const & trans);

	//operations
	bool operator== (const Transformation &other) const;
	bool operator!= (const Transformation &other) const;

	void toBuffer(char * buffer) const;
};