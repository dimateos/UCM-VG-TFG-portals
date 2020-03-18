#include "Node.h"

Node Node::ROOT = Node();

Node::Node() : father_(nullptr) {}
Node::Node(Node * father) : father_(nullptr) {
	father->addChild(this);
}
Node::~Node() {}

void Node::setFather(Node * const & father) {
	if (father == father_) return;						//check same father
	if (father_ != nullptr) father_->removeChild(this);	//check father not null before removing
	if (father != nullptr) father->addChild(this);		//check new father not null before adding
}
void Node::addChild(Node * const & child) {
	if (child == nullptr) return;
	if (child->father_ == this) return; //already child

	//first check if it has no father before adding it
	if (child->father_ != nullptr) child->father_->removeChild(child);
	children_.push_back(child);
	child->father_ = this;
}
void Node::removeChild(Node * const & child) {
	if (child == nullptr) return;
	if (child->father_ != this) return; //not its child

	//if found then erase from list and reset its father
	auto it = std::find(children_.begin(), children_.end(), child);
	if (it != children_.end()) {
		children_.erase(it);
		child->father_ = nullptr;
	}
}
void Node::clearChildren() {
	children_.clear();
}

void Node::updateTransform() {
	trans.updateModelMatrix(father_->trans.getModelMatrix());
}
void Node::updateInvTransform() {
	trans.updateInvModelMatrix(father_->trans.getInvModelMatrix());
}

void Node::update() {
}

void Node::render() {
}
