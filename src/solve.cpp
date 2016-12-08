#include "solve.hpp"

void aStar(Map &start)
{
	Queue open;
	Queue close;
	Node **neighbors = new Node*[4];
	int nNeighbors;
	int i;

	open.push(new Node(&start));
	while (!open.empty())
	{
		Node *cur = open.top();
		open.pop();
		if (cur->map->isMapSolved())
		{
			std::cout << "found ! cout: " << cur->cout << " open: " << open.size() << " close: " << close.size() << std::endl;
			/*Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}*/
			break ;
		}
		cur->cout += 1;
		nNeighbors = getNeighbors(&close, &open, cur, neighbors, &isExistAndBetter);
		cur->cout -= 1;
		/*if(close.size() % 500 == 0)
		{
			std::cout << open.size() << "\t" <<close.size() << std::endl;
		}*/
		i = 0;
		while(i < nNeighbors)
		{
			neighbors[i]->heuristic = neighbors[i]->cout + neighbors[i]->map->getManhattanDistance();
			open.push(neighbors[i]);
			i++;
		}
		close.push(cur);
	}
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
			std::cout << "found ! cout: " << cur->cout << " open: " << open.size() << " close: " << close.size() << std::endl;
			/*Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}*/
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

void greedy(Map *start)
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
			std::cout << "found ! cout: " << cur->cout << " open: " << open.size() << " close: " << close.size() << std::endl;
			/*Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}*/
			break ;
		}
		cur->cout += 1;
		nNeighbors = getNeighbors(&close, &open, cur, neighbors, &isExistAndBetter);
		cur->cout -= 1;
		i = 0;
		while(i < nNeighbors)
		{
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

bool isExist(Queue *list, Node *node)
{
	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		if (cmpMap(((*i)->map)->map, (node->map)->map) && (*i)->heuristic <= node->heuristic)
			return (true);
	}
	return (false);
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
