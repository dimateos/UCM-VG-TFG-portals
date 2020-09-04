#pragma once
#include <glm.hpp>

class Projection
{
public:
	Projection(float near = 0.1f, float far = 100.0f);
	~Projection();

	float near, far;
	virtual void updateProjMatrix() = 0;

	glm::mat4 getProjMatrix() const;
	const glm::f32* getProjMatrixPtr() const;
	glm::mat4 computedProjMatrix_;
};

class PerspectiveProjection : public Projection
{
public:
	PerspectiveProjection(float aspect, float fovY = 60.0f, float near = 0.1f, float far = 100.0f);
	~PerspectiveProjection();

	float aspect, fov;
	virtual void updateProjMatrix();
};

class OrthoProjection : public Projection
{
public:
	OrthoProjection(float w, float h, float zoom, float near = 0.1f, float far = 100.0f);
	~OrthoProjection();

	float w, h, zoom;
	virtual void updateProjMatrix();
};
