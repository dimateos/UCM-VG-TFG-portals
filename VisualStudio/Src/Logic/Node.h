#pragma once
#include "Transform.h"
#include <list>

class Node
{
public:
	Node();
	Node(Node* father);
	virtual ~Node();

	static Node ROOT; //root node

	inline std::list<Node*> const& getChildren() const { return children_; }
	inline Node* const& getFather() const { return father_; }
	void setFather(Node* const& father);
	void addChild(Node* const& child);
	void removeChild(Node* const& child);
	void clearChildren();

	Transform trans;
	void updateTransform();
	void updateInvTransform();

	virtual void update();
	virtual void render();

protected:
	Node* father_;
	std::list<Node*> children_;
};