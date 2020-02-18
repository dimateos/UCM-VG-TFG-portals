#include "Scene.h"
#include "Node.h"

Scene::Scene() {}
Scene::~Scene() {
	if (!_nodes.empty()) printf("Scene - WARNING destroyed while ents not empty\n");
}

bool Scene::init() {
	return true;
}
void Scene::release() {
	for each (Node* it in _nodes) delete it;
	_nodes.clear();
}

//bool Scene::handleEvent(const SDL_Event & event) {
//	for (auto e : _ents) if (e->handleEvent(event)) return true;
//	return false;
//}

void Scene::update(float delta) {
	for (auto e : _nodes) e->update(delta);
}

void Scene::render() {
	for (auto e : _nodes) e->render();
}