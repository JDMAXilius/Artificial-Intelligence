#include "PathSearch.h"

namespace fullsail_ai { namespace algorithms {

	PathSearch::PathSearch()
	{
		//start default and Weigh
		//The constructor should take no arguments
		//time
		//myTimer.start();
		goalTile = nullptr;
		firstTile = nullptr;
		hWeight = 1.2f;
		tileMap = nullptr;
		//rows = NULL;
		//columns = NULL;
	}

	PathSearch::~PathSearch()
	{
		//delete and null
		//The destructor should perform any final cleanup required before deletion of the object.
		//stop time
		if (goalTile != nullptr)
			delete goalTile;
		goalTile = nullptr;

		if (firstTile != nullptr)
			delete firstTile;
		firstTile = nullptr;
	}
	float PathSearch::Estimate(SearchNode* start, SearchNode* goal)
	{
		float x = 0, y = 0;
		x = start->tile->getXCoordinate() - goal->tile->getXCoordinate();
		y = start->tile->getYCoordinate() - goal->tile->getYCoordinate();
		//x = start->tile->getRow() - goal->tile->getRow();
		//y = start->tile->getColumn() - goal->tile->getColumn();
		return (sqrt(x * x + y * y));
	}
	//Breadth-First Search//costly one
	/*breadthFirstSearch(SearchNode* start, SearchNode* goal)
	{
		queue open;
		map visited;

		open.enqueue(new PlannerNode(start));
		visited[start] = open.front();

		while (!open.empty())
		{
			PlannerNode* current = open.dequeue();
			if current.vertex is the goal, we’re done;

			for each edge of current.vertex:
			{
				SearchNode* successor = edge.endpoint;

				if (visited[successor] == NULL)
				{
					successorNode = new PlannerNode(successor);
					successorNode.parent = current;
					visited[successor] = successorNode;
					open.enqueue(successorNode);
				}
			}
		}
	}*/

	//Greedy Best-First Search//quicker one
	/*greedyBestFirstSearch(SearchNode* start, SearchNode* goal)
	{
		PriorityQueue open(isGreater);
		map visited;
		open.enqueue(new PlannerNode(start));
		visited[start] = open.front();
		visited[start].heuristicCost = estimate(start, goal);

		while (!open.empty())
		{
			PlannerNode* current = open.dequeue();
			if current.vertex is the goal, we’re done;

			for each edge of current.vertex:
			{
				SearchNode* successor = edge.endpoint;

				if (visited[successor] == NULL)
				{
					successorNode = new PlannerNode(successor);
					successorNode.parent = current;
					successorNode.heuristicCost = estimate(successor, goal);
					visited[successor] = successorNode;
					open.enqueue(successorNode);
				}
			}
		}
	}*/

	//Uniform Cost Search//slower one
	/*uniformCostSearch(SearchNode* start, SearchNode* goal)
	{
		PriorityQueue open(isGreater);
		map visited;
		open.enqueue(new PlannerNode(start));
		visited[start] = open.front();
		open.front().givenCost = 0;

		while (!open.empty())
		{
			PlannerNode* current = open.dequeue();
			if current.vertex is the goal, we’re done;

			for each edge of current.vertex:
			{
				SearchNode* successor = edge.endpoint;
				float tempGivenCost = current.givenCost + edge.cost;

				if (visited[successor] != NULL)
				{
					if (tempGivenCost < visited[successor].givenCost)
					{
						PlannerNode* successorNode = visited[successor];
						open.remove(successorNode);
						successorNode.givenCost = tempGivenCost;
						successorNode.parent = current;
						open.enqueue(successorNode);
					}
				}
				else
				{
					successorNode = new PlannerNode(successor);
					successorNode.givenCost = tempGivenCost;
					successorNode.parent = current;
					visited[successor] = successorNode;
					open.enqueue(successorNode);
				}
			}
		}
	}*/

	//A* Search Planning//best one
	/*aStarSearch(SearchNode* start, SearchNode* goal)
	{
		PriorityQueue open(isGreater);
		map visited;
		open.enqueue(new PlannerNode(start));
		visited[start] = open.front();

		open.front().givenCost = 0;
		open.front().heuristicCost = estimate(start, goal);
		open.front().finalCost = givenCost + heuristicCost * hWeight;

		while (!open.empty())
		{
			PlannerNode* current = open.dequeue();
			if current.vertex is the goal, we’re done;

			for each edge of current.vertex:
			{
				SearchNode* successor = edge.endpoint;
				float tempGivenCost = current.givenCost + edge.cost;

				if (visited[successor] != NULL)
				{
					PlannerNode* node = visted[successor];
					if (tempGivenCost < node.givenCost)
					{
						open.remove(node);
						node.givenCost = tempGivenCost;
						node.finalCost = node.givenCost + node.heuristicCost * hWeight;
						node.parent = current;
						open.enqueue(node);
					}
				}
				else
				{
					node = new PlannerNode(successor);
					node.givenCost = tempGivenCost;
					node.heuristicCost = estimate(successor, goal);
					node.finalCost = node.givenCost + node.heuristicCost * hWeight;
					node.parent = current;
					visited[successor] = node;
					open.enqueue(node);
				}
			}
		}
	}*/


	void PathSearch::initialize(TileMap* _tileMap)
	{
		tileMap = _tileMap;
		//Create a SearchNode for each valid tile in the tile map.
		//• Create edges to connect each pair of adjacent tiles.
		//• Add all created node to an index(such as a map) that be easily accessed to find
		//the nodes by tileand allows for easy clean up later 
		
		//getColumnCount and row
		int rows = _tileMap->getRowCount();
		int columns = _tileMap->getColumnCount();
		//for each c & r check raw data
		for (int y = 0; y < _tileMap->getRowCount(); y++)
		{
			for (int x = 0; x < _tileMap->getColumnCount(); x++)
			{
				//getTile
				Tile* tile = _tileMap->getTile(y,x);
				//create search node
				if (_tileMap->getTile(y, x)->getWeight() == 0)
					continue;
				SearchNode* myPlannerNode = new SearchNode;
				myPlannerNode->tile = _tileMap->getTile(y, x);
				nodes[tile] = myPlannerNode;
				//nodes.insert(std::make_pair(myPlannerNode->tile, myPlannerNode));
			}
		}

		//set neighbors

		//for (int y = 0; y < rows; y++)
		//{
		//	for (int x = 0; x < columns; x++) // check raw data
		//	{
		//		//always matches
		//		Tile* findTile = _tileMap->getTile(y, x);;
		//		/*if (findTile == nullptr && findTile->getWeight() == 0)
		//			continue;*/
		//		SearchNode* filter = nodes[findTile];
		//		//LEFT
		//		findTile = _tileMap->getTile(y, filter->tile->getColumn() - 1);
		//		if (findTile != nullptr && findTile->getWeight() != 0)
		//		{
		//			if (nodes[findTile] != nullptr)
		//				filter->neighbors.push_back(nodes[findTile]);
		//			/*else
		//				delete findTile;*/
		//		}

		//		//RIGHT
		//		findTile = _tileMap->getTile(y, filter->tile->getColumn() + 1);
		//		if (findTile != nullptr && findTile->getWeight() != 0)
		//		{
		//			if (nodes[findTile] != nullptr)
		//				filter->neighbors.push_back(nodes[findTile]);
		//		}

		//		//UP
		//		findTile = _tileMap->getTile(filter->tile->getRow() - 1, x);
		//		if (findTile != nullptr && findTile->getWeight() != 0)
		//		{
		//			if (nodes[findTile] != nullptr)
		//				filter->neighbors.push_back(nodes[findTile]);
		//		}
		//		//DOWN
		//		findTile = _tileMap->getTile(filter->tile->getRow() - 1, x);
		//		if (findTile != nullptr && findTile->getWeight() != 0)
		//		{
		//			if (nodes[findTile] != nullptr)
		//				filter->neighbors.push_back(nodes[findTile]);
		//		}

		//		//SPECIALS
		//		if (filter->tile->getRow() % 2 == 0) //Even Row
		//		{
		//			//UPLEFT
		//			findTile = _tileMap->getTile(filter->tile->getRow() - 1, filter->tile->getColumn() - 1);
		//			if (findTile != nullptr && findTile->getWeight() != 0)
		//			{
		//				if (nodes[findTile] != nullptr)
		//					filter->neighbors.push_back(nodes[findTile]);
		//			}

		//			//DOWNLEFT
		//			findTile = _tileMap->getTile(filter->tile->getRow() + 1, filter->tile->getColumn() - 1);
		//			if (findTile != nullptr && findTile->getWeight() != 0)
		//			{
		//				if (nodes[findTile] != nullptr)
		//					filter->neighbors.push_back(nodes[findTile]);
		//			}
		//		}
		//		else //odd row
		//		{
		//			//UPRIGHT

		//			findTile = _tileMap->getTile(filter->tile->getRow() - 1, filter->tile->getColumn() + 1);
		//			if (findTile != nullptr && findTile->getWeight() != 0)
		//			{
		//				if (nodes[findTile] != nullptr)
		//					filter->neighbors.push_back(nodes[findTile]);
		//			}

		//			//DOWNRIGHT
		//			findTile = _tileMap->getTile(filter->tile->getRow() + 1, filter->tile->getColumn() + 1);
		//			if (findTile != nullptr && findTile->getWeight() != 0)
		//			{
		//				if (nodes[findTile] != nullptr)
		//					filter->neighbors.push_back(nodes[findTile]);
		//			}
		//		}
		//	}
		//}

		//Method will be called after the tile map is loaded.This is usually where the search graph
		//is generated.

		for (int i = 0; i < _tileMap->getRowCount(); i++)
		{
			for (int j = 0; j < _tileMap->getColumnCount(); j++) // check raw data
			{
				//always matches
				Tile* findTile = _tileMap->getTile(i, j);
				
				if (_tileMap->getTile(i, j)->getWeight() == 0)
					continue;
				SearchNode* SN = nodes[_tileMap->getTile(i, j)];
				//UP
				findTile = _tileMap->getTile(SN->tile->getRow() + 1, j);
				if (findTile != nullptr && findTile->getWeight() != 0)
				if (nodes[findTile] != nullptr)
					SN->neighbors.push_back(nodes[findTile]);
				//DOWN
				findTile = _tileMap->getTile(SN->tile->getRow() - 1, j);
				if (findTile != nullptr && findTile->getWeight() != 0)
				if (nodes[findTile] != nullptr)
					SN->neighbors.push_back(nodes[findTile]);
				//RIGHT
				findTile = _tileMap->getTile(i, SN->tile->getColumn() + 1);
				if (findTile != nullptr && findTile->getWeight() != 0)
				if (nodes[findTile] != nullptr)
					SN->neighbors.push_back(nodes[findTile]);
				//LEFT
				findTile = _tileMap->getTile(i, SN->tile->getColumn() - 1);
				if (findTile != nullptr && findTile->getWeight() != 0)
				if (nodes[findTile] != nullptr)
					SN->neighbors.push_back(nodes[findTile]);
				//SPECIALS
				if (SN->tile->getRow() % 2 == 0) //Even Row
				{
					//DOWNLEFT
					findTile = _tileMap->getTile(SN->tile->getRow() + 1, SN->tile->getColumn() - 1);
					if (findTile != nullptr && findTile->getWeight() != 0)
					if (nodes[findTile] != nullptr)
						SN->neighbors.push_back(nodes[findTile]);
					//UPLEFT
					findTile = _tileMap->getTile(SN->tile->getRow() - 1, SN->tile->getColumn() - 1);
					if (findTile != nullptr && findTile->getWeight() != 0)
					if (nodes[findTile] != nullptr)
						SN->neighbors.push_back(nodes[findTile]);
				}
				else //odd row
				{
					//DOWNRIGHT
					findTile = _tileMap->getTile(SN->tile->getRow() + 1, SN->tile->getColumn() + 1);
					if (findTile != nullptr && findTile->getWeight() != 0)
					if (nodes[findTile] != nullptr)
						SN->neighbors.push_back(nodes[findTile]);
					//UPRIGHT
					findTile = _tileMap->getTile(SN->tile->getRow() - 1, SN->tile->getColumn() + 1);
					if (findTile != nullptr && findTile->getWeight() != 0)
					if (nodes[findTile] != nullptr)
						SN->neighbors.push_back(nodes[findTile]);
				}
			}
		}
		/*for (auto node : nodes)
		{
			if (node.second == nullptr) continue;
			for (auto neighbor : node.second->neighbors)
			{
				node.second->tile->addLineTo(neighbor->tile, 0xff0000ff);
			}
		}*/
		//SearchNode* temp = nodes[tileMap->getTile(0, 0)];
	}

	void PathSearch::enter(int startRow, int startColumn, int goalRow, int goalColumn)
	{
		//• Find the SearchNode that represents the starting tile.
		//• Set the goal tile(or node) so that you know when to stop the algorithm.
		//• Add the starting node to the open queueand mark it as visited
		//goalRow = goalRow;
		//goalColumn = goalColumn;


		//goal node
		if (goalTile != nullptr)
		{
			delete goalTile;
			goalTile = nullptr;
		}
		goalTile = new SearchNode;
		//start node
		if (firstTile != nullptr)
		{
			delete firstTile;
			firstTile = nullptr;
		}
		//firstTile = new SearchNode;
		//firstTile = nodes[tileMap->getTile(startRow, startColumn)];
		//add to visited

		//Method will be called before any update of the path plannerand should prepare for a
		//search to be performed between the tiles at the coordinates indicated.
		//SearchNode* start = nodes[firstTile->tile];
		SearchNode* start = nodes[tileMap->getTile(startRow, startColumn)];
		goalTile = nodes[tileMap->getTile(goalRow, goalColumn)];
		PlannerNode* firstNode = new PlannerNode();
		//firstNode->SetParent(nullptr);
		firstNode->searchNode = start;
		firstNode->parent = nullptr;
		firstNode->givenCost = 0;
		firstNode->heuristicCost = Estimate(start, goalTile);
		firstNode->finalCost = firstNode->givenCost + firstNode->heuristicCost * 1.2f;//hWeight;
		open.push(firstNode);

		/*open.front()->givenCost = 0;
		open.front()->heuristicCost = Estimate(start, goalTile);
		open.front()->finalCost = open.front()->givenCost + open.front()->heuristicCost * 1.2f;*/
		//visited[firstNode->searchNode] = open.front();
		//firstNode = firstNode->parent;
		visited[start] = open.front();
		isFinish = false;
	}

	void PathSearch::update(long timeslice)
	{
		//• While the open list contains planner nodes...
		//1. Dequeue what will become the current node.
		//2. Once you find the goal, build the solution listand exit.
		//3. Determine the successor nodes.Make sure that you go through only those
		//nodes whose tiles are adjacent to that of the current node.
		//■ If a node has not been visited—this check is called a dupe check—add it
		//to the open queue and mark it as visited.
		//■ Don't forget the rule regarding impassable tiles

		//Method will be called to allow the path planner to execute for the specified allotted time
		//(in milliseconds).Within this method the search should be performed until the time
		//expires or the solution is found.
		//If the update's allotted time is zero (0), this method should only do a single iteration of 
		//the algorithm.Otherwise the update should only iterate for the time slices number of
		//milliseconds.

		//PriorityQueue open(isGreater);
		//map visited;
		//open.enqueue(new PlannerNode(start));
		//visited[start] = open.front();

		//open.front().givenCost = 0;
		//open.front().heuristicCost = estimate(start, goal);
		//open.front().finalCost = givenCost + heuristicCost * hWeight;

		while (!open.empty())
		{
			//PlannerNode* current = open.dequeue();
			PlannerNode* current = open.front();
			current->searchNode->tile->setFill(0xFF0000FF);
			//if current.vertex is the goal, we’re done;
			if (current->searchNode->tile == goalTile->tile)
			{
				solutionList.clear();
				while (current != nullptr)
				{
					solutionList.push_back(current->searchNode->tile);
					if (current->parent != nullptr)
					{
						current->searchNode->tile->setFill(0xFFFFFF00);
						current->searchNode->tile->addLineTo(current->parent->searchNode->tile, 0xFFFF0000);
					}
					current = current->parent;
				}
				//solutionList.push_back(firstTile->tile);

				isFinish = true;
				break;
			}
			open.pop();
			/*if (current->searchNode->tile == goalTile->tile)
			{
				solutionList.clear();
		
				while (current->searchNode->tile != firstTile->tile)
				{
					solutionList.push_back(current->searchNode->tile);
					current->searchNode->tile->addLineTo(current->parent->searchNode->tile, 0xFFDC143C);
					current->searchNode = current->parent->searchNode;
					current->parent = current->parent->parent;
				}
				solutionList.push_back(firstTile->tile);
				isFinish = true;
				break;
			}*/
			current->searchNode->tile->setOutline(0xFFFFFFFF);
			//for each edge of current.vertex:
			for (size_t i = 0; i < current->searchNode->neighbors.size(); i++)
			{
				//SearchNode* successor = edge.endpoint;
				SearchNode* successor = current->searchNode->neighbors[i];
				//float tempGivenCost = current.givenCost + edge.cost;
				//float tempGivenCost = current->givenCost + (current->searchNode->neighbors[i]->tile->getWeight() * tileMap->getTileRadius() * 2);
				//float tempGivenCost = current->givenCost + Estimate(current->searchNode, current->searchNode->neighbors[i]) * successor->tile->getWeight();//
				//float tempGivenCost = current->givenCost + Estimate(current->searchNode, successor->searchNode) * (successor->searchNode->tile->getWeight());//
				//float temp_Givincost = current->givenCost + EstimateCost(current->searchNode, Edge_node) * successor->searchNode->tile->getWeight();
				//float tempGivenCost = current->givenCost + current->searchNode->neighbors[i]->tile->getWeight();// *tileMap->getTileRadius();//
				
				float tempGivenCost = current->givenCost + Estimate(current->searchNode, successor) * successor->tile->getWeight();

				if (visited[successor] != nullptr)
				{
					PlannerNode* node = visited[successor];
					if (tempGivenCost < node->givenCost)
					{
						open.remove(node);
						node->parent = current;
						node->givenCost = tempGivenCost;
						node->finalCost = node->givenCost + node->heuristicCost *  hWeight;
						node->searchNode->tile->setFill(0x0F00FF00);
						node->searchNode->tile->setFill(node->searchNode->tile->getFill() - 20);
						//open.enqueue(node);
					/*	if (node->searchNode->tile == goalTile->tile)
						{
							while (node->searchNode->tile != firstTile->tile)
							{
								node->searchNode->tile->addLineTo(node->parent->searchNode->tile, 0xFFFFFF00);
								node = node->parent;
							}
							isFinish = true;
							return;
						}*/
						visited[successor] = node;
						open.push(node);
					}
					////node = visited[successor];
					//if (tempGivenCost < node->givenCost)
					//{
					//	open.remove(node);
					//	node->givenCost = tempGivenCost;
					//	node->finalCost = node->givenCost + node->heuristicCost * 1.2f;
					//	node->parent = current;
					//	if (current->searchNode->tile == goalTile->tile)
					//	{
					//		solutionList.clear();
					//
					//		while (current->searchNode->tile != firstTile->tile)
					//		{
					//			solutionList.push_back(current->searchNode->tile);
					//			current->searchNode->tile->addLineTo(current->parent->searchNode->tile, 0xFFDC143C);
					//			current->searchNode = current->parent->searchNode;
					//			current->parent = current->parent->parent;
					//		}
					//		solutionList.push_back(firstTile->tile);
					//		isFinish = true;
					//	}
					//	node->searchNode->tile->setFill(0xFFFF10F0);
					//	open.push(node);
					//}
				}
				else
				{
					PlannerNode* snode = new PlannerNode();
					snode->searchNode = successor;
					snode->parent = current;
					snode->givenCost = tempGivenCost;
					snode->heuristicCost = Estimate(successor, goalTile);
					snode->finalCost = snode->givenCost + snode->heuristicCost * hWeight;
					snode->searchNode->tile->setFill(0x0F00FF00);
					//open.enqueue(node);
					/*if (snode->searchNode->tile == goalTile->tile)
					{
						while (snode->searchNode->tile != firstTile->tile)
						{
							snode->searchNode->tile->addLineTo(snode->parent->searchNode->tile, 0xFFFFFF00);
							snode = snode->parent;
						}
						isFinish = true;
						return;
					}*/
					open.push(snode);
					visited[successor] = snode;
				}
			}
			if (current->parent)
				current->searchNode->tile->addLineTo(current->parent->searchNode->tile, 0xFFFF0000);

			if (timeslice == 0)
			{
				//break;
			}
			current->searchNode->tile->setOutline(0xFF0000FF);
			current->searchNode->tile->clearLines();
			
		}
		//isFinish = false;
		//do
		//{
		//	PlannerNode* Current_node = open.front();
		//	Current_node->searchNode->tile->setMarker(0xFF00FF00);
		//	open.pop();
		//
		//	if (Current_node->searchNode->tile == goalTile->tile)
		//	{
		//		solutionList.clear();
		//
		//		while (Current_node->searchNode->tile != firstTile->tile)
		//		{
		//			solutionList.push_back(Current_node->searchNode->tile);
		//			Current_node->searchNode->tile->addLineTo(Current_node->parent->searchNode->tile, 0xFFDC143C);
		//			Current_node->searchNode = Current_node->parent->searchNode;
		//			Current_node->parent = Current_node->parent->parent;
		//		}
		//		solutionList.push_back(firstTile->tile);
		//		isFinish = true;
		//	}
		//	for (SearchNode* Edge_node : Current_node->searchNode->neighbors)
		//	{
		//		SearchNode* Successor = Edge_node;
		//		PlannerNode* node = new PlannerNode();
		//		double temp_Givincost = Current_node->givenCost + Estimate(Current_node->searchNode, Edge_node) * Edge_node->tile->getWeight();
		//
		//		if (visited[Successor] != NULL)
		//		{
		//			node = visited[Successor];
		//			if (temp_Givincost < node->givenCost)
		//			{
		//				open.remove(node);
		//				node->givenCost = temp_Givincost;
		//				node->finalCost = node->givenCost + node->heuristicCost * 1.2f;
		//				node->parent = Current_node;
		//				if (Current_node->searchNode->tile == goalTile->tile)
		//				{
		//					solutionList.clear();
		//
		//					while (Current_node->searchNode->tile != firstTile->tile)
		//					{
		//						solutionList.push_back(Current_node->searchNode->tile);
		//						Current_node->searchNode->tile->addLineTo(Current_node->parent->searchNode->tile, 0xFFDC143C);
		//						Current_node->searchNode = Current_node->parent->searchNode;
		//						Current_node->parent = Current_node->parent->parent;
		//					}
		//					solutionList.push_back(firstTile->tile);
		//					isFinish = true;
		//				}
		//				node->searchNode->tile->setFill(0xFFFF10F0);
		//				open.push(node);
		//			}
		//		}
		//		else
		//		{
		//			node->searchNode = Successor;
		//			node->givenCost = temp_Givincost;
		//			node->heuristicCost = Estimate(Successor, goalTile);
		//			node->finalCost = node->givenCost + node->heuristicCost * 1.2f;
		//			node->parent = Current_node;
		//			visited[Successor] = node;
		//			if (Current_node->searchNode->tile == goalTile->tile)
		//			{
		//				solutionList.clear();
		//
		//				while (Current_node->searchNode->tile != firstTile->tile)
		//				{
		//					solutionList.push_back(Current_node->searchNode->tile);
		//					Current_node->searchNode->tile->addLineTo(Current_node->parent->searchNode->tile, 0xFFDC143C);
		//					Current_node->searchNode = Current_node->parent->searchNode;
		//					Current_node->parent = Current_node->parent->parent;
		//				}
		//				solutionList.push_back(firstTile->tile);
		//				isFinish = true;
		//			}
		//			node->searchNode->tile->setFill(0xFFFF10F0);
		//			open.push(node);
		//		}
		//	}
		//
		//	if (timeslice == 0)
		//	{
		//		//return;
		//	}
		//
		//} while (!open.empty());
	}

	void PathSearch::exit()
	{
		//• Reset member variables as needed

		//Method will be called when the current search data is no longer needed.It should clean
		//up any memory allocated for this search.Note that this is not exactly the same as the
		//destructor, as the object may be reinitialized to perform another search
		if (!visited.empty())
		{
			auto it = visited.begin();
			while (it != visited.end())
			{
				delete (it->second);
				++it;
			}
		}
		visited.clear();
		open.clear();
		goalTile = nullptr;
		isFinish = false;
	}

	void PathSearch::shutdown()
	{
		//• Reset member variables as needed
		//Method will be called when the tile map is unloaded.It should clean up any memory
		//allocated for this tile map
		//if (!nodes.empty())
		//{
		//	auto it = nodes.begin();
		//	while (it != nodes.end())
		//	{
		//		//size_t edgeSize = it->second->neighbors->neighbors.size();
		//		for (rsize_t i = 0; i < it->second->neighbors->neighbors.size(); i++)
		//		{
		//			Edge* aux = it->second->edges.back();
		//			it->second->edges.pop_back();
		//			delete aux;
		//		}
		//		delete (it->second);
		//		++it;
		//	}
		//	nodes.clear();
		//}
		if (!nodes.empty())
			nodes.clear();

		if (!visited.empty())
		{
			auto it = visited.begin();
			while (it != visited.end())
			{
				delete (it->second);
				++it;
			}
			visited.clear();
		}
		open.clear();
	}

	bool PathSearch::isDone() const
	{
		if (isFinish == true)
			return true;
		else
			return false;
		//Method should return a vector containing the solution path as an ordered series of Tile
		//pointers from finish to start
	}

	std::vector<Tile const*> const PathSearch::getSolution() const
	{
		std::vector<Tile const*> temp;
		PlannerNode* myFirstTile = open.front();
		while (myFirstTile != nullptr)
		{
			temp.push_back(myFirstTile->searchNode->tile);
			myFirstTile = myFirstTile->parent;
		}
		//return temp;
		return solutionList;
		//Method should return a vector containing the solution path as an ordered series of Tile
		//pointers from finish to start
	}
}}  // namespace fullsail_ai::algorithms

