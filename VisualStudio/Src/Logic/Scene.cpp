#include "Scene.h"
#include "Node.h"

Scene::Scene(App* app) : app_ (app) {}
Scene::~Scene() {
	if (!nodes_.empty()) printf("Scene - WARNING destroyed while ents not empty\n");
}

bool Scene::init() {
	return app_ != nullptr;
}
void Scene::release() {
	for each (Node* it in nodes_) delete it;
	nodes_.clear();
}

//bool Scene::handleEvent(const SDL_Event & event) {
//	for (auto e : _ents) if (e->handleEvent(event)) return true;
//	return false;
//}

void Scene::update() {
	for (auto e : nodes_) e->update();
}

void Scene::render() {
	for (auto e : nodes_) e->render();
}