#include "ShapeNode.h"
#include <glad\glad.h>

#include "../Logic/Camera.h" //tmp
#include "../Platform/Platform_SDL.h"

ShapeNode::ShapeNode(Node * father, Mesh* mesh, Material* mat) : Node(father), mesh_(mesh), mat_(mat) {
}
ShapeNode::ShapeNode(ShapeNode const & other) : Node(other.getFather()), mesh_(other.mesh_), mat_(other.mat_) {
	setLocalTrans(other.getLocalTrans());
}

ShapeNode::~ShapeNode() {
}

void ShapeNode::render() {
	//from scene now
	//shader3D_.bind();
	//movable camera
	//glUniformMatrix4fv(uniformView_, 1, GL_FALSE, Node::ROOT_CAM->getViewMatrixPtr());
	//movable model
	//glUniformMatrix4fv(uniformModel_, 1, GL_FALSE, getModelMatrix_ptr());

	//draw
	if (mat_ != nullptr && mesh_ != nullptr) {
		mat_->bind();
		mesh_->draw();
		mat_->unbind();
	}
	else if (mesh_ != nullptr) mesh_->draw();
}
