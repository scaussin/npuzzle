#include "Map.hpp"

int **Map::mapSolved = NULL;

Map::Map(int **_map, int _mapSize) : map(_map), mapSize(_mapSize), nMax(_mapSize * _mapSize)
{
	mapLine = NULL;
	if (!mapSolved)
		initMapSolved();
}

Map::~Map()
{
	if (map)
	{
		if (*map)
		{
			for (int i = 0; i < mapSize; i++)
			{
				delete[] map[i];
			}
		}
		delete[] map;
	}
	if (mapLine)
		delete mapLine;
}

int Map::getManhattanDistance()
{
	int ManhattanDistance = 0;

	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			int x, y;
			getCoordCase(x, y, mapSolved, map[i][j]);
			ManhattanDistance += abs(y - i) + abs(x - j);
		}
	}
	return (ManhattanDistance);
}

void Map::getCoordCase(int &x, int &y, int **mapToFind, int find)
{
	for (y = 0; y < mapSize; y++)
	{
		for (x = 0; x < mapSize; x++)
		{
			if (mapToFind[y][x] == find)
				return ;
		}
	}
	return ;
}

bool Map::isSolvable()
{
	int nSwap = 0;
	initMapLine();
	int indexToSort = (nMax) - 1;

	while (isMapLineSolved() == false)
	{
		while (mapLine[indexToSort] == indexToSort + 1)
		{
			indexToSort--;
		}
		int *tmpCase = getCase(indexToSort + 1);
		*tmpCase = mapLine[indexToSort];
		mapLine[indexToSort] = indexToSort + 1;
		nSwap++;
		//printMapLine();
	}
	int x, y;
	getCoordCase(x, y, mapSolved, 0);
	int i, j;
	getCoordCase(i, j, map, 0);
	int ManhattanDistanceVide = abs(y - i) + abs(x - j);
	if (nSwap % 2 == (ManhattanDistanceVide) % 2)
		return (true);
	return (false);
}

int *Map::getCase(int find)
{
	for (int i = 0; i < nMax; i++)
	{
		if (mapLine[i] == find)
			 return (&(mapLine[i]));
	}
	return (NULL);
}

Node *Map::getNeighbors()
{
	int x, y, i = 0;
	Node *neighbors = new Node[5];

	bzero(neighbors, sizeof(Node) * 5);
	getCoordCase(x, y, map, 0);

	if (y > 0)
	{
		neighbors[i] = Node(this);
		neighbors[i].map->moveUp(x, y);
		neighbors[i].map->print();
		i++;
	}
	if (y < mapSize - 1)
	{
		neighbors[i] = Node(this);
		neighbors[i].map->moveDown(x, y);
		neighbors[i].map->print();
		i++;
	}
	if (x > 0)
	{
		neighbors[i] = Node(this);
		neighbors[i].map->moveLeft(x, y);
		i++;
	}
	if (x < mapSize - 1)
	{
		neighbors[i] = Node(this);
		neighbors[i].map->moveLeft(x, y);
		i++;
	}
	return (neighbors);
}

void Map::moveUp(int x, int y)
{
	int tmp = map[y - 1][x];

	map[y - 1][x] = map[y][x];
	map[y][x] = tmp;
}

void Map::moveDown(int x, int y)
{
	int tmp = map[y + 1][x];

	map[y + 1][x] = map[y][x];
	map[y][x] = tmp;
}

void Map::moveLeft(int x, int y)
{
	int tmp = map[y][x - 1];

	map[y][x - 1] = map[y][x];
	map[y][x] = tmp;
}

void Map::moveRight(int x, int y)
{
	int tmp = map[y][x + 1];

	map[y][x + 1] = map[y][x];
	map[y][x] = tmp;
}

bool Map::isSolved()
{
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			if (mapSolved[y][x] != map[y][x])
				return false;
		}
	}
	return true;
}

bool Map::isMapLineSolved()
{
	for (int i = 0; i < nMax; i++)
	{
		if ((i < (nMax) - 1 && i + 1 != mapLine[i]) || (i == (nMax) - 1 && mapLine[i] != nMax))
			return (false);
	}
	return (true);
}

void Map::printMapLine()
{
	for (int i = 0; i < nMax; i++)
	{
		std::cout << mapLine[i] << " ";
	}
	std::cout << std::endl;
}

void Map::print()
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
			std::cout << (map[i][j] < 10 ? " " : "") << map[i][j] << " ";
		std::cout << std::endl;
	}
}

void Map::initMapLine()
{
	int margin = 0, i = 0, j = 0, k = 0;
	mapLine = new int[nMax];

	while (42)
	{
		while (k < mapSize - margin)
		{
			mapLine[i] = map[j][k];
			i++;
			k++;
		}
		if (i == nMax)
			break;
		k--;
		j++;
		while (j < mapSize - margin)
		{
			mapLine[i] = map[j][k];
			i++;
			j++;
		}
		if (i == nMax)
			break;
		j--;
		k--;
		while (k >= 0 + margin)
		{
			mapLine[i] = map[j][k];
			i++;
			k--;
		}
		if (i == nMax)
			break;
		k++;
		j--;
		margin++;
		while (j >= 0 + margin)
		{
			mapLine[i] = map[j][k];
			i++;
			j--;
		}
		if (i == nMax)
			break;
		j++;
		k++;
	}
	for (int i = 0; i < nMax; i++)
	{
		if (mapLine[i] == 0)
			mapLine[i] = nMax;
	}
}

void Map::initMapSolved()
{
	int margin = 0, i = 0, j = 0, k = 0;
	mapSolved = new int*[mapSize];

	for (int i = 0; i < mapSize * mapSize; i++)
		mapSolved[i] = new int[mapSize];
	while (42)
	{
		while (k < mapSize - margin)
		{
			mapSolved[j][k] = i + 1;
			i++;
			k++;
		}
		k--;
		if (i == mapSize * mapSize)
			break;
		j++;
		while (j < mapSize - margin)
		{
			mapSolved[j][k] = i + 1;
			i++;
			j++;
		}
		j--;
		if (i == mapSize * mapSize)
			break;
		k--;
		while (k >= 0 + margin)
		{
			mapSolved[j][k] = i + 1;
			i++;
			k--;
		}
		k++;
		if (i == mapSize * mapSize)
			break;
		j--;
		margin++;
		while (j >= 0 + margin)
		{
			mapSolved[j][k] = i + 1;
			i++;
			j--;
		}
		j++;
		if (i == mapSize * mapSize)
			break;
		k++;
	}
	mapSolved[j][k] = 0;
}