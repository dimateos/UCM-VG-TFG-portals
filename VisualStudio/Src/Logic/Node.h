#pragma once
#include "Transform.h"

class Node
{
public:
	Node();
	virtual ~Node();

	Transform trans;

	virtual void update();
	virtual void render();
};