#include "Path.h"

Path::Path () {}
Path::~Path () {}


// Returns reference to the Node at 'index.'
Node* Path::PeekNode (int index) const {
	if ((unsigned int)index < _nodes.size ()) {
		return _nodes[index];
	}
	else {
		return NULL;
	}
}


// Returns reference to the Node at the end of the vector _nodes.
Node* Path::PeekNextNode () const {
	if (_nodes.size () > 0) {
		return _nodes.back ();
	}
	else {
		return NULL;
	}
}


// Returns reference to the Node at the end of the vector _nodes and removes it from the vector.
Node* Path::GetAndRemoveNextNode () {
	if (_nodes.size () > 0) {
		Node* toBeReturned = _nodes.back ();
		_nodes.pop_back ();
		return toBeReturned;
	}
	else {
		return NULL;
	}
}


// Adds Node to the pack of the vector _nodes.
void Path::AddNode (Node* toBeAdded) {
	_nodes.push_back (toBeAdded);
}


// Returns true if 'toBeChecked' is in _nodes.
bool Path::Contains (Node* toBeChecked) const {
	bool retVal = false;

	for (unsigned int i = 0; i<_nodes.size (); i++) {
		if (_nodes[i] == toBeChecked) {
			retVal = true;
			break;
		}
	}
	return retVal;
}


// Clears the vector _nodes.
void Path::Clear () {
	_nodes.clear ();
}



Path* Path::GetPathToTargetNode (Node* target, Node* source) {
	Path* toBeUsed = new Path ();
	Node* currentNode = target;
	
	//while (currentNode -> GetId () != source -> GetId ()) {
	while (currentNode != NULL) {
		toBeUsed -> AddNode (currentNode);
		currentNode = currentNode -> GetParentNode ();
	}

	toBeUsed -> AddNode (source);
	return toBeUsed;
}