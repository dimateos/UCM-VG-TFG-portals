#include "SampleScene.h"
#include "../LogicNodes/TriangleRGB.h"

#include <glad\glad.h>

SampleScene::SampleScene() : Scene() {}

SampleScene::~SampleScene() {}

bool SampleScene::init() {
	_nodes.push_back(new TriangleRGB());
	return true;
}

void SampleScene::update(float delta) {}

void SampleScene::render() {
	glClearColor(0.9f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene::render();
}
