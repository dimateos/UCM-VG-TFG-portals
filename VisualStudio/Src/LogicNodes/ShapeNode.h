#pragma once

#include "../Logic/Node.h"
#include "../Render/Mesh.h"
#include "../Render/Material.h"

class ShapeNode : public Node
{
public:
	ShapeNode(Node* father, Mesh* mesh, Material* mat);
	virtual ~ShapeNode();

	virtual void render();

	Mesh* mesh_;
	Material* mat_;
};
