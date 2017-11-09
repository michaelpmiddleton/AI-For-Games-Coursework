#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder )
	:mpPathfinder(pPathfinder)
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;

#ifdef VISUALIZE_PATH
	theStream << "Pathlength:"<< mpPathfinder->mPath.GetSize();
	
	theStream << "  Num Nodes Processed:" << mpPathfinder->mVisitedNodes.size();
#endif
	theStream << "  Elapsed Time:" << mpPathfinder->mTimeElapsed;
	theStream << "  Pathfinding Method: " << mpPathfinder -> GetAlgorithmName ();
	return theStream.str();
}

