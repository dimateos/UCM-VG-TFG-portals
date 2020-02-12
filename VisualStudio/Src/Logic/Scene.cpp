#include "Scene.h"

#include "Entity.h"

Scene::Scene() {}
Scene::~Scene() {
	release();
}

bool Scene::init() {
	return false;
}

void Scene::release() {
	for each (Entity* it in _ents) delete it;
	_ents.clear();
}

bool Scene::handleEvent(const SDL_Event & event) {
	for (auto e : _ents) if (e->handleEvent(event)) return true;
	return false;
}

void Scene::update(float delta) {
	for (auto e : _ents) e->update(delta);
}

void Scene::render(float delta) {
	for (auto e : _ents) e->render(delta);
}