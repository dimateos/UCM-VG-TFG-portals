#pragma once
#include <glm.hpp>

#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

//more constructors later
//https://gamedev.stackexchange.com/questions/94061/rotating-an-object-with-quaternion

class Transform
{
public:
	Transform();
	~Transform();

	glm::vec3 fatherPostion, localPostion, localScale;
	glm::quat localRotation;

	glm::mat4 getModelMatrix() const;
};