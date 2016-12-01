#include "Map.hpp"

Map::Map(int **_map, int _mapSize) : map(_map), mapSize(_mapSize), nMax(_mapSize * _mapSize)
{
}

Map::~Map()
{
	for (int i = 0; i < mapSize; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	if (mapLine)
		delete mapLine;
}

int Map::getManhattanDistance(Map &solved)
{
	(void)solved;
	return (1);
}

bool Map::isSolvable()
{
	int nSwap = 0;
	initMapLine();
	int indexToSort = (nMax) - 1;

	while (isSolved() == false)
	{
		while (mapLine[indexToSort] == indexToSort + 1)
		{
			indexToSort--;
		}
		int *tmpCase = getCase(indexToSort + 1);
		*tmpCase = mapLine[indexToSort];
		mapLine[indexToSort] = indexToSort + 1;
		nSwap++;
	}
	if (nSwap % 2 == (nMax) % 2)
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

bool Map::isSolved()
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