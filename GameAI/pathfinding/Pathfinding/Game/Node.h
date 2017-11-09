#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
const float NODE_INFINITY = 9999;
const float NODE_INTERDISTANCE = 1;
#define NODE_ID int

class Node : public Trackable {
	//	FORMER CODE:
	/*
	public:
		Node( const NODE_ID& id );
		Node();
		~Node();
	
		const NODE_ID& GetId() const {return mId;};
	
	private:
		const NODE_ID mId;
	*/
	public:
		Node (const NODE_ID& id, Node* parentNode);
		Node ();
		~Node ();

		
		const NODE_ID& GetId () const { return _nodeID; };
		//const Path* GetPathToThisNode () const { return _pathFromOrigin; };
		const float GetDistanceFromOrigin () const { return _distanceFromOrigin; };


		void AdjustParentNode (Node* newParentNode);
		void AdjustDistanceFromOrigin (float newDistance);
		void SetAsRootNode ();
		void ResetNode ();


		Node* GetParentNode ();

	private:
		const NODE_ID _nodeID;
		float _distanceFromOrigin;		// Distance currently traveled from current source.
		Node* _parentNode;
};