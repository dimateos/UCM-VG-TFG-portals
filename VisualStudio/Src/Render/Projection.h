#pragma once
#include <glm.hpp>

class Projection
{
public:
	Projection(float aspect, float fovY = 60.0f, float near = 0.1f, float far = 100.0f);
	~Projection();

	float aspect, fov, near, far;

	void updateProjMatrix();
	glm::mat4 getProjMatrix() const;
	const glm::f32* getProjMatrixPtr() const;

	glm::mat4 computedProjMatrix_;
private:
};