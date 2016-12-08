#include "Map.hpp"

int **Map::mapSolved = NULL;
int Map::nMax = 0;
int Map::mapSize = 0;
//char *Map::mapStringSolved = NULL;

Map::Map(int **_map) : map(_map)
{
	//mapString = NULL;
}

Map::Map(Map const &rhs)
{
	*this = rhs;
}

bool Map::operator==(Map const& rhs)
{
	int i = 0;
	int j;
	while (i < mapSize)
	{
		j = 0;
		while (j < mapSize)
		{
			if (map[i][j] != rhs.map[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
	//return(memcmp(mapString, rhs.mapString, nMax) == 0);
}

Map &Map::operator=(Map const &rhs)
{
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		memcpy(map[i], rhs.map[i], mapSize * sizeof(int));
	}
	return (*this);
}

Map::~Map()
{
	if (map)
	{
		if (*map)
		{
			for (int i = 0; i < mapSize; i++)
				delete[] map[i];
		}
		delete[] map;
	}
	/*if (mapString)
		delete mapString;*/
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


/*
Node **Map::getNeighbors(int &nNeighbors, Node *parentNode)
{
	int x, y;
	nNeighbors = 0;
	Node **neighbors = new Node*[4];

	getCoordCase(x, y, map, 0);
	if (y > 0)
	{

		neighbors[nNeighbors] = new Node(new Map(*this), parentNode);
		neighbors[nNeighbors]->map->moveUp(x, y);
		nNeighbors++;
	}
	if (y < mapSize - 1)
	{
		neighbors[nNeighbors] = new Node(new Map(*this), parentNode);
		neighbors[nNeighbors]->map->moveDown(x, y);
		nNeighbors++;
	}
	if (x > 0)
	{
		neighbors[nNeighbors] = new Node(new Map(*this), parentNode);
		neighbors[nNeighbors]->map->moveLeft(x, y);
		nNeighbors++;
	}
	if (x < mapSize - 1)
	{
		neighbors[nNeighbors] = new Node(new Map(*this), parentNode);
		neighbors[nNeighbors]->map->moveRight(x, y);
		nNeighbors++;
	}
	return (neighbors);
}
*/
void Map::moveUp(int x, int y)
{
	map[y][x] = map[y - 1][x];
	map[y - 1][x] = 0;
	//initMapString();
}

void Map::moveDown(int x, int y)
{
	map[y][x] = map[y + 1][x];
	map[y + 1][x] = 0;
	//initMapString();
}

void Map::moveLeft(int x, int y)
{
	map[y][x] = map[y][x - 1];
	map[y][x - 1] = 0;
	//initMapString();
}

void Map::moveRight(int x, int y)
{
	map[y][x] = map[y][x + 1];
	map[y][x + 1] = 0;
	//initMapString();
}
/*
void Map::initMapString()
{
	if (!mapString)
		mapString = new char[nMax];
	int c = 0;
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			mapString[c] = map[i][j];
			c++;
		}
	}
}*/
/*
bool Map::isMapStringSolved()
{
	return(memcmp(mapString, mapStringSolved, nMax) == 0);
}
*/

bool Map::isMapSolved()
{
	int i = 0;
	int j;
	while (i < mapSize)
	{
		j = 0;
		while (j < mapSize)
		{
			if (map[i][j] != mapSolved[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void Map::print()
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (mapSize > 3) 
				std::cout << (map[i][j] < 10 ? " " : "") << map[i][j] << " ";
			else
				std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
