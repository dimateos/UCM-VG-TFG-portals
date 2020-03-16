#pragma once
#include "Transform.h"
#include <list>

class Node
{
public:
	Node();
	Node(Node* _father);
	virtual ~Node();

	static Node ROOT; //root node
	Node* father;
	std::list<Node*> children;

	Transform trans;
	void updateTransform();
	void updateInvTransform();

	virtual void update();
	virtual void render();
};