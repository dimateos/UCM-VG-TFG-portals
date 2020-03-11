#include "Scene.h"
#include "Node.h"

Scene::Scene(App* app) : _app (app) {}
Scene::~Scene() {
	if (!_nodes.empty()) printf("Scene - WARNING destroyed while ents not empty\n");
}

bool Scene::init() {
	return _app != nullptr;
}
void Scene::release() {
	for each (Node* it in _nodes) delete it;
	_nodes.clear();
}

//bool Scene::handleEvent(const SDL_Event & event) {
//	for (auto e : _ents) if (e->handleEvent(event)) return true;
//	return false;
//}

void Scene::update() {
	for (auto e : _nodes) e->update();
}

void Scene::render() {
	for (auto e : _nodes) e->render();
}