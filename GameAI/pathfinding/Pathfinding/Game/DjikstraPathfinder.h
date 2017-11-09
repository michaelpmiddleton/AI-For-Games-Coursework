#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DjikstraPathfinder : public GridPathfinder {
	public:
		DjikstraPathfinder (Graph* pGraph);
		~DjikstraPathfinder ();

		const Path& findPath (Node* pFrom, Node* pTo);	//make sure to delete the path when you are done!

	private:
};