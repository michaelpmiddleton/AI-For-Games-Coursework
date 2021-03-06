#include <allegro5/allegro.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest )
{
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}


	std::string temp = GetAlgorithmName ();
	static ALLEGRO_COLOR pathColor;
	if (temp == "A*")
		pathColor = al_map_rgb (0, 0, 255);

	else
		pathColor = al_map_rgb (255, 0, 0);

	static ALLEGRO_COLOR startColor = al_map_rgb(255, 255, 255);
	static ALLEGRO_COLOR stopColor = al_map_rgb(0, 0, 0);

	unsigned int numNodes = mPath.GetSize();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
			mpVisualizer->addColor(mPath.PeekNode(i)->GetId(), currentPathColor);
		

		//add beginning and ending color
		mpVisualizer->addColor(mPath.PeekNode(0)->GetId(), startColor);
		mpVisualizer->addColor(mPath.PeekNode(numNodes - 1)->GetId(), stopColor);
	}

	mpVisualizer->draw(*pDest);
}
#endif

std::string GridPathfinder::GetAlgorithmName () { return "UNOVERIDDEN";}