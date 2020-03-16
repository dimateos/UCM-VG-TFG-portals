#include "Node.h"

Node Node::ROOT = Node();

Node::Node() : father(nullptr) {}
Node::Node(Node * _father) : father(_father) {}
Node::~Node() {}

void Node::updateTransform() {
	trans.updateModelMatrix(father->trans.getModelMatrix());
}
void Node::updateInvTransform() {
	trans.updateInvModelMatrix(father->trans.getInvModelMatrix());
}

void Node::update() {
}

void Node::render() {
}
