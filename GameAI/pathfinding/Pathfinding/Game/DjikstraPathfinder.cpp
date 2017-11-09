#include "DjikstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

/*
	FILE:		DjikstraPathfinder.cpp
	AUTHOR:		mmiddleton
	DATE:		6 November 2017

	NOTES:
	This CPP file was adapted from the DepthFirstPathfinder CPP file.
*/

// Constructor & Destructor:
DjikstraPathfinder::DjikstraPathfinder (Graph* graph) : GridPathfinder (dynamic_cast<GridGraph*> (graph)) {}
DjikstraPathfinder::~DjikstraPathfinder () {}

// Other functions:
const Path& DjikstraPathfinder::findPath (Node* sourceNode, Node* targetNode) {
	ClearGraph ();
	
	// [PRE-EXISTING CODE]	Performance tracking start.
	gpPerformanceTracker -> clearTracker ("path");
	gpPerformanceTracker -> startTracking ("path");


	// [OVERHAUL]	Load-in the graph as list of Nodes / Initialize local variables
	std::priority_queue<Node*, std::vector<Node*>, CompareNodeByDistanceFromOrigin> nodesToVisit;
	sourceNode -> SetAsRootNode ();
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
	

	//		DJISKTRA-SPECIFIC CODE:		////////////////////////////////////////////////////////
	while (!nodesToVisit.empty ()) {
		currentNode = nodesToVisit.top ();		// Peak closest node.
		nodesToVisit.pop ();					// Pop said node.
		
		if (currentNode -> GetId () == targetNode -> GetId ())
			break;

		connections = mpGraph -> getConnections (currentNode -> GetId ()); // Get all nodes connected to the current node.
		
		for each (Connection* connection in connections) {
			Node* potentialAddition = connection -> getToNode ();

			// If the path from the current node to the connection is shorter than the current path in the connection node, overwrite the path to the connection node 
			if ((currentNode -> GetDistanceFromOrigin () + NODE_INTERDISTANCE) < (potentialAddition -> GetDistanceFromOrigin ())) {
				mVisitedNodes.push_back (potentialAddition);
				potentialAddition -> AdjustParentNode (currentNode);
				potentialAddition -> AdjustDistanceFromOrigin (currentNode -> GetDistanceFromOrigin () + NODE_INTERDISTANCE);
				nodesToVisit.push (potentialAddition);
			}
		}
	}

	mPath = *(mPath.GetPathToTargetNode (targetNode, sourceNode));

	// /////////////////////////////////////////////////////////////////////////////////////////
	

	// [PRE-EXISTING CODE]	Performance tracking end.
	gpPerformanceTracker -> stopTracking ("path");
	mTimeElapsed = gpPerformanceTracker -> getElapsedTime ("path");


	return mPath;
}



std::string DjikstraPathfinder::GetAlgorithmName () {return "Dijkstra";}
