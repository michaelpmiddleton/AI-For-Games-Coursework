#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Game.h"
#include "Vector2D.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

/*
FILE:		AStarPathfinder.cpp
AUTHOR:		mmiddleton
DATE:		8 November 2017

NOTES:
This CPP file was adapted from the DepthFirstPathfinder CPP file.
*/

// Constructor & Destructor:
AStarPathfinder::AStarPathfinder (Graph* graph, Grid* appGrid) : GridPathfinder (dynamic_cast<GridGraph*> (graph)), _appGrid (appGrid) {}
AStarPathfinder::~AStarPathfinder () {}

// Other functions:
const Path& AStarPathfinder::findPath (Node* sourceNode, Node* targetNode) {
	ClearGraph ();

	// [PRE-EXISTING CODE]	Performance tracking start.
	gpPerformanceTracker->clearTracker ("path");
	gpPerformanceTracker->startTracking ("path");


	// [OVERHAUL]	Load-in the graph as list of Nodes / Initialize local variables
	std::priority_queue<Node*, std::vector<Node*>, CompareNodeByDistanceFromOrigin> nodesToVisit;
	sourceNode->SetAsRootNode ();
	nodesToVisit.push (sourceNode);
	Node* currentNode = NULL;
	std::vector<Connection*> connections;


	// [PRE-EXISTING CODE]	Graphics
	#ifdef VISUALIZE_PATH
	mVisitedNodes.clear ();
	mVisitedNodes.push_back (sourceNode);
	#endif


	// Clear path. (Removes previous one if applicable)
	mPath.Clear ();


	//		A*-SPECIFIC CODE:		////////////////////////////////////////////////////////
	while (!nodesToVisit.empty ()) {
		currentNode = nodesToVisit.top ();		// Peak closest node.
		nodesToVisit.pop ();					// Pop said node.

		if (currentNode -> GetId () == targetNode -> GetId ())
			break;

		connections = mpGraph->getConnections (currentNode->GetId ()); // Get all nodes connected to the current node.

		for each (Connection* connection in connections) {
			Node* potentialAddition = connection->getToNode ();

			// If the path from the current node to the connection is shorter than the current path in the connection node, overwrite the path to the connection node 
			if ((currentNode->GetDistanceFromOrigin () + _AStarHeuristic (currentNode, targetNode)) < (potentialAddition->GetDistanceFromOrigin ())) {
				mVisitedNodes.push_back (potentialAddition);
				potentialAddition->AdjustParentNode (currentNode);
				potentialAddition->AdjustDistanceFromOrigin (currentNode->GetDistanceFromOrigin () + NODE_INTERDISTANCE);
				nodesToVisit.push (potentialAddition);
			}
		}
	}

	// Copy pointer from mPath:
	Path* temp = mPath.GetPathToTargetNode (targetNode, sourceNode);

	// Transfer path pointer:
	mPath = *temp;

	// Delete temporary pointer:
	delete temp;
	temp = NULL;

	// /////////////////////////////////////////////////////////////////////////////////////////


	// [PRE-EXISTING CODE]	Performance tracking end.
	gpPerformanceTracker->stopTracking ("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime ("path");


	return mPath;
}



float AStarPathfinder::_AStarHeuristic (Node* source, Node* target) {
	float length = (_appGrid -> getULCornerOfSquare (source -> GetId ()) - _appGrid -> getULCornerOfSquare (target -> GetId ())).getLength ();
	return abs (length);
}



std::string AStarPathfinder::GetAlgorithmName () { return "A*"; }