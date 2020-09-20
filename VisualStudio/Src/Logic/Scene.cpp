#include "Scene.h"
#include "Node.h"

Scene::Scene(App* app) : app_ (app), world_node_(&Node::ROOT) {
	world_node_->setLocalTrans(Transformation::BASE);
}
Scene::~Scene() {
	if (!world_node_->getChildren().empty()) printf("Scene - WARNING destroyed while scene not empty\n");
}

bool Scene::init() {
	return app_ != nullptr;
}
void Scene::release() {
	for (auto n : world_node_->getChildren()) release_rec(n);
	world_node_->clearChildren();
	//delete world_node_; //reference not new node
}
void Scene::release_rec(Node * n) {
	for (auto c : n->getChildren()) release_rec(c);
	n->clearChildren();
	delete n;
}

void Scene::update() {
	for (auto n : world_node_->getChildren()) update_rec(n);
}
void Scene::render() {
	for (auto n : world_node_->getChildren()) render_rec(n);
}

void Scene::update_rec(Node * n) {
	n->update();
	for (auto c : n->getChildren()) update_rec(c);
}
void Scene::render_rec(Node * n) {
	n->render();
	for (auto c : n->getChildren()) render_rec(c);
}

