#pragma once

#include <vector>
#include <Trackable.h>
#include "Node.h"


class Path : public Trackable {
	//	OLD CODE:
	/*
	public:
		Path();
		~Path();

		Node* PeekNode( int index ) const;
		Node* peekNextNode() const;
		Node* getAndRemoveNextNode();
		bool containsNode( Node* pNode ) const;
		int GetSize() const { return mNodes.size(); };

		void addNode( Node* pNode );
		void clear();//remove all nodes

	private:
		std::vector<Node*> mNodes;
	*/

	public:
		Path ();
		~Path ();

		Node* PeekNode (int index) const;
		Node* PeekNextNode () const;
		Node* GetAndRemoveNextNode ();
		bool Contains (Node* nodeToCheck) const;
		const int GetSize () const { return _nodes.size (); };

		void AddNode (Node* toBeAdded);
		Path* GetPathToTargetNode (Node* target, Node* source);
		void Clear ();//remove all nodes

	private:
		std::vector<Node*> _nodes;


};