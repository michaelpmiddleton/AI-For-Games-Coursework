#pragma once

#include "GridPathfinder.h"
#include <vector>

/*
	FILE:		DjikstraPathfinder.h
	AUTHOR:		mmiddleton
	DATE:		6 November 2017

	NOTES:
	This header file was adapted from the DepthFirstPathfinder header file.
*/

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DjikstraPathfinder : public GridPathfinder {
	public:
		DjikstraPathfinder (Graph* pGraph);
		~DjikstraPathfinder ();

		const Path& findPath (Node* pFrom, Node* pTo);	//make sure to delete the path when you are done!
		std::string GetAlgorithmName ();


	private:
};