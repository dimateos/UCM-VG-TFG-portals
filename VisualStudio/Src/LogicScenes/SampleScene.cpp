#include "SampleScene.h"
#include "../LogicNodes/TriangleRGB.h"
#include "../LogicNodes/Triangle.h"
#include "../LogicNodes/SquareAnimated.h"
#include "../LogicNodes/SquareTextured.h"

#include <glad\glad.h>
#define UNBIND 0

SampleScene::SampleScene() : Scene() {}

SampleScene::~SampleScene() {}

bool SampleScene::init() {
	_nodes.push_back(new SquareAnimated());
	_nodes.push_back(new SquareTextured());
	_nodes.push_back(new Triangle());
	_nodes.push_back(new TriangleRGB());

	//glEnable(GL_DEPTH_TEST);
	return true;
}

void SampleScene::update(float delta) {
	Scene::update(delta);
}

void SampleScene::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene::render();

	//glBindVertexArray(UNBIND); //no need to unbind every time
}
