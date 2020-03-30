#pragma once

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void draw() = 0;
};

//for now here
class AxisMesh : public Mesh
{
public:
	AxisMesh();
	virtual ~AxisMesh();
	virtual void draw();

protected:
	unsigned int VAO_, VBO_;
	float l_ = 1.0f; //size of screen
	float axis_rgb_vertices_[6 * (3+3)] = {
		// positions          // color
		 0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 l_, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		 0.0f, l_, 0.0f,		0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		 0.0f, 0.0f, l_,		0.0f, 0.0f, 1.0f
	};
};


class PlaneMesh : public Mesh
{
public:
	PlaneMesh();
	virtual ~PlaneMesh();
	virtual void draw();

protected:
	unsigned int VAO_, VBO_, EBO_;
	float l_ = 1.0f; //size of screen
	unsigned int indices_[6] = {  // note that we start from 0
		//0, 1, 3,   // first triangle
		//1, 2, 3    // second triangle
		3, 1, 0,   // first triangle
		3, 2, 1    // second triangle
	};
	float square_tex_vertices_[4 * 5] = {
		// positions          // texture coords
		 l_,  l_, 0.0f,   1.0f, 1.0f,   // top right
		 l_, -l_, 0.0f,   1.0f, 0.0f,   // bottom right
		-l_, -l_, 0.0f,   0.0f, 0.0f,   // bottom left
		-l_,  l_, 0.0f,   0.0f, 1.0f    // top left
	};
};

class CubeMesh : public Mesh
{
public:
	CubeMesh();
	virtual ~CubeMesh();
	virtual void draw();

protected:
	unsigned int VAO_, VBO_;
	float l_ = 0.5f; //size of screen
	float cube_vertices[36 * 5] = {
		-l_, -l_, -l_,  0.0f, 0.0f,
		l_, -l_, -l_,  1.0f, 0.0f,
		l_,  l_, -l_,  1.0f, 1.0f,
		l_,  l_, -l_,  1.0f, 1.0f,
		-l_,  l_, -l_,  0.0f, 1.0f,
		-l_, -l_, -l_,  0.0f, 0.0f,

		-l_, -l_,  l_,  0.0f, 0.0f,
		l_, -l_,  l_,  1.0f, 0.0f,
		l_,  l_,  l_,  1.0f, 1.0f,
		l_,  l_,  l_,  1.0f, 1.0f,
		-l_,  l_,  l_,  0.0f, 1.0f,
		-l_, -l_,  l_,  0.0f, 0.0f,

		-l_,  l_,  l_,  1.0f, 0.0f,
		-l_,  l_, -l_,  1.0f, 1.0f,
		-l_, -l_, -l_,  0.0f, 1.0f,
		-l_, -l_, -l_,  0.0f, 1.0f,
		-l_, -l_,  l_,  0.0f, 0.0f,
		-l_,  l_,  l_,  1.0f, 0.0f,

		l_,  l_,  l_,  1.0f, 0.0f,
		l_,  l_, -l_,  1.0f, 1.0f,
		l_, -l_, -l_,  0.0f, 1.0f,
		l_, -l_, -l_,  0.0f, 1.0f,
		l_, -l_,  l_,  0.0f, 0.0f,
		l_,  l_,  l_,  1.0f, 0.0f,

		-l_, -l_, -l_,  0.0f, 1.0f,
		l_, -l_, -l_,  1.0f, 1.0f,
		l_, -l_,  l_,  1.0f, 0.0f,
		l_, -l_,  l_,  1.0f, 0.0f,
		-l_, -l_,  l_,  0.0f, 0.0f,
		-l_, -l_, -l_,  0.0f, 1.0f,

		-l_,  l_, -l_,  0.0f, 1.0f,
		l_,  l_, -l_,  1.0f, 1.0f,
		l_,  l_,  l_,  1.0f, 0.0f,
		l_,  l_,  l_,  1.0f, 0.0f,
		-l_,  l_,  l_,  0.0f, 0.0f,
		-l_,  l_, -l_,  0.0f, 1.0f
	};
};