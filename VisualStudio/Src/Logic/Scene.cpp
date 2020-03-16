#include "Scene.h"
#include "Node.h"

Scene::Scene(App* app) : app_ (app), world_node_(&Node::ROOT) {}
Scene::~Scene() {
	if (!world_node_->children.empty()) printf("Scene - WARNING destroyed while scene not empty\n");
}

bool Scene::init() {
	return app_ != nullptr;
}
void Scene::release() {
	for (auto n : world_node_->children) release_rec(n);
	world_node_->children.clear();
}
void Scene::release_rec(Node * n) {
	for (auto c : n->children) release_rec(c);
	n->children.clear();
	delete n;
}

void Scene::update() {
	for (auto n : world_node_->children) update_rec(n);
}
void Scene::render() {
	for (auto n : world_node_->children) render_rec(n);
}

void Scene::update_rec(Node * n) {
	n->update();
	for (auto c : n->children) update_rec(c);
}
void Scene::render_rec(Node * n) {
	n->render();
	for (auto c : n->children) render_rec(c);
}

