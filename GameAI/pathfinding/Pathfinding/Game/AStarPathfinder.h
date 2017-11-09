#pragma once

#include "GridPathfinder.h"
#include <vector>

/*
	FILE:		AStarPathfinder.h
	AUTHOR:		mmiddleton
	DATE:		6 November 2017

	NOTES:
	This header file was adapted from the DepthFirstPathfinder header file.
*/

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStarPathfinder : public GridPathfinder {
	public:
		AStarPathfinder (Graph* pGraph, Grid* appGrid);
		~AStarPathfinder ();

		const Path& findPath (Node* sourceNode, Node* targetNode);
		float _AStarHeuristic (Node* source, Node* target);
		std::string GetAlgorithmName ();

	private:
		Grid* _appGrid;
};

