#include "Node.h"

Node Node::ROOT = Node();
Camera* Node::ROOT_CAM = nullptr;

Node::Node() : Transformable(nullptr), father_(nullptr) {}
Node::Node(Node * father) : Transformable(nullptr), father_(nullptr) {
	father->addChild(this);
}
Node::~Node() {}

Node * Node::getCopy() const {
	Node * n = new Node(father_);
	n->setLocalTrans(getLocalTrans());
	n->axis_ = axis_;
	for (auto child : getChildren()) n->addChild(child->getCopy());
	return n;
}

void Node::setFather(Node * const & father, bool ignoreTrans) {
	if (father == father_) return;										//check same father
	if (father_ != nullptr) father_->removeChild(this, ignoreTrans);	//check father not null before removing
	if (father != nullptr) father->addChild(this, ignoreTrans);			//check new father not null before adding
}
void Node::addChild(Node * const & child, bool ignoreTrans) {
	if (child == nullptr) return;
	if (child->father_ == this) return; //already child

	//first check if it has no father before adding it
	if (child->father_ != nullptr) child->father_->removeChild(child);
	children_.push_back(child);
	child->father_ = this;
	if (!ignoreTrans) child->setFatherTransformable(this);
}
void Node::removeChild(Node * const & child, bool ignoreTrans) {
	if (child == nullptr) return;
	if (child->father_ != this) return; //not its child

	//if found then erase from list and reset its father
	auto it = std::find(children_.begin(), children_.end(), child);
	if (it != children_.end()) {
		children_.erase(it);
		child->father_ = nullptr;
		if (!ignoreTrans) child->setFatherTransformable(nullptr);
	}
}
void Node::clearChildren() {
	children_.clear();
}

void Node::update() {
}

void Node::render() {
}

void Node::setDrawAxis(bool set) {
	if (axis_ == nullptr) axis_ = Node::ROOT_AXIS->getCopy();

	if (set) addChild(axis_);
	else removeChild(axis_);
}
