#pragma once
#include "Transform.h"

class Node
{
public:
	Node();
	virtual ~Node();

	Transform trans;

	virtual void update(float delta);
	virtual void render();
};