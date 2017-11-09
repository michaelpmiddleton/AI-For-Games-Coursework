#include "Node.h"



Node::Node () :
	_nodeID (BAD_NODE_ID),
	_distanceFromOrigin (NODE_INFINITY) {}



Node::Node (const NODE_ID& nodeID, Node* parentNode) : _nodeID (nodeID), _distanceFromOrigin (NODE_INFINITY) {
	AdjustParentNode (parentNode);
}



Node::~Node () {}



void Node::AdjustParentNode (Node* newParentNode) {
	_parentNode = newParentNode;
	//_pathFromOrigin = newParentNode -> GetPathToThisNode ();
	//_pathFromOrigin -> AddNode (this);
}



void Node::AdjustDistanceFromOrigin (float newDistance) {
	_distanceFromOrigin  = newDistance;
}



void Node::SetAsRootNode () {
	_parentNode = NULL;
	_distanceFromOrigin = 0;
	//_pathFromOrigin = new Path ();
	//_pathFromOrigin -> AddNode (this);
}



void Node::ResetNode () {
	_distanceFromOrigin = NODE_INFINITY;
	_parentNode = NULL;
	//_pathFromOrigin = NULL;
}



Node* Node::GetParentNode () {
	return _parentNode;
}