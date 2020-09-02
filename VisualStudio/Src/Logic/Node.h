#pragma once
#include "Transformable.h"
#include <list>

class Camera; //forwarded for now

class Node : public Transformable
{
public:
	Node();
	Node(Node* father);
	virtual ~Node();
	virtual Node* getCopy() const;

	static Camera* ROOT_CAM; //root camera for now
	static Node* ROOT_AXIS; //common axis for debug
	static Node ROOT; //root node for now

	inline Node* const& getFather() const { return father_; }
	void setFather(Node* const& father, bool ignoreTrans = false);

	inline std::list<Node*> const& getChildren() const { return children_; }
	void addChild(Node* const& child, bool ignoreTrans = false);
	void removeChild(Node* const& child, bool ignoreTrans = false);
	void clearChildren();

	virtual void update();
	virtual void render();

	//drawing node axis
	void setDrawingAxis(bool set = true);
	void toggleDrawingAxis();
	bool isDrawingAxis() const;

protected:
	Node* father_;
	std::list<Node*> children_;

	bool drawingAxis_ = false;
	Node* axis_ = nullptr;
};