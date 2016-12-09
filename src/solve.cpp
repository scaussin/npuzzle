#include "solve.hpp"

void aStar(Map *start, int heur1, int heur2, int heur3)
{
	Queue open;
	Queue close;
	Node **neighbors = new Node*[4];
	int nNeighbors;
	int i;

	open.push(new Node(start));
	while (!open.empty())
	{
		Node *cur = open.top();
		open.pop();
		if (cur->map->isMapSolved())
		{
			Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}
			std::cout << "moves: " << cur->cout << std::endl;
			std::cout << "complexity in time: " << open.size() << std::endl;
			std::cout << "complexity in size: " << close.size() + open.size() << std::endl;
			break ;
		}
		cur->cout += 1;
		nNeighbors = getNeighbors(&close, &open, cur, neighbors, &isExistAndBetter);
		cur->cout -= 1;
		i = 0;
		while(i < nNeighbors)
		{
			neighbors[i]->heuristic = neighbors[i]->cout;
			if (heur1 == 1)
				neighbors[i]->heuristic += neighbors[i]->map->getManhattanDistance();
			if (heur2 == 2)
				neighbors[i]->heuristic += neighbors[i]->map->outRowCol();
			if (heur3 == 3)
				neighbors[i]->heuristic += neighbors[i]->map->misplaced();
			open.push(neighbors[i]);
			i++;
		}
		close.push(cur);
	}
	delete[] neighbors;
}

void uniformCost(Map *start)
{
	Queue open;
	Queue close;
	Node **neighbors = new Node*[4];
	int nNeighbors;
	int i;

	open.push(new Node(start));
	while (!open.empty())
	{
		Node *cur = open.top();
		open.pop();
		if (cur->map->isMapSolved())
		{
			Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}
			std::cout << "moves: " << cur->cout << std::endl;
			std::cout << "complexity in time: " << open.size() << std::endl;
			std::cout << "complexity in size: " << close.size() + open.size() << std::endl;
			break ;
		}
		cur->cout += 1;
		nNeighbors = getNeighbors(&close, &open, cur, neighbors, &isExistAndBetter);
		cur->cout -= 1;
		i = 0;
		while(i < nNeighbors)
		{
			neighbors[i]->heuristic = neighbors[i]->cout;
			open.push(neighbors[i]);
			i++;
		}
		close.push(cur);
	}
}

void greedy(Map *start, int heur1, int heur2, int heur3)
{
	Queue open;
	Queue close;
	Node **neighbors = new Node*[4];
	int nNeighbors;
	int i;

	open.push(new Node(start));
	while (!open.empty())
	{
		Node *cur = open.top();
		open.pop();
		if (cur->map->isMapSolved())
		{
			Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}
			std::cout << "moves: " << cur->cout << std::endl;
			std::cout << "complexity in time: " << open.size() << std::endl;
			std::cout << "complexity in size: " << close.size() + open.size() << std::endl;
			break ;
		}
		cur->cout += 1;
		nNeighbors = getNeighbors(&close, &open, cur, neighbors, &isExistAndBetter);
		cur->cout -= 1;
		i = 0;
		while(i < nNeighbors)
		{
			if (heur1 == 1)
				neighbors[i]->heuristic += neighbors[i]->map->getManhattanDistance();
			if (heur2 == 2)
				neighbors[i]->heuristic += neighbors[i]->map->outRowCol();
			if (heur3 == 3)
				neighbors[i]->heuristic += neighbors[i]->map->misplaced();

			neighbors[i]->heuristic = neighbors[i]->map->getManhattanDistance();
			open.push(neighbors[i]);
			i++;
		}
		close.push(cur);
	}
}

void getCoordCase(int &x, int &y, int **mapToFind, int find)
{
	y = 0;
	while (y < Map::mapSize)
	{
		x = 0;
		while (x < Map::mapSize)
		{
			if (mapToFind[y][x] == find)
				return ;
			x++;
		}
		y++;
	}
	return ;
}

int getNeighbors(Queue *close, Queue *open, Node *cur, Node **neighbors, bool (*cmp)(Queue *list, Node *node))
{
	int x, y;
	int nNeighbors = 0;

	getCoordCase(x, y, cur->map->map, 0);
	if (y > 0)
	{
		cur->map->moveUp(x, y);
		if (!(cmp(close, cur) || cmp(open, cur)))
		{
			neighbors[nNeighbors] = new Node(new Map(*cur->map), cur);
			nNeighbors++;
		}
		cur->map->moveDown(x, y - 1);
	}
	if (y < Map::mapSize - 1)
	{
		cur->map->moveDown(x, y);
		if (!(cmp(close, cur) || cmp(open, cur)))
		{
			neighbors[nNeighbors] = new Node(new Map(*cur->map), cur);
			nNeighbors++;
		}
		cur->map->moveUp(x, y + 1);
	}
	if (x > 0)
	{
		cur->map->moveLeft(x, y);
		if (!(cmp(close, cur) || cmp(open, cur)))
		{
			neighbors[nNeighbors] = new Node(new Map(*cur->map), cur);
			nNeighbors++;
		}
		cur->map->moveRight(x - 1, y);
	}
	if (x < Map::mapSize - 1)
	{
		cur->map->moveRight(x, y);
		if (!(cmp(close, cur) || cmp(open, cur)))
		{
			neighbors[nNeighbors] = new Node(new Map(*cur->map), cur);
			nNeighbors++;
		}
		cur->map->moveLeft(x + 1, y);
	}
	return (nNeighbors);
}

bool cmpMap(int **map1, int **map2)
{
	int i = 0;
	int j;

	while (i < Map::mapSize)
	{
		j = 0;
		while (j < Map::mapSize)
		{
			if (map1[i][j] != map2[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool isExistAndBetter(Queue *list, Node *node)
{
	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		if (cmpMap(((*i)->map)->map, (node->map)->map) && (*i)->cout <= node->cout)
			return (true);
	}
	return (false);
}
