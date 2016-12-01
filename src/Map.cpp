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
}

bool Map::isSolvable()
{
	int nSwap = 0;
	mapLine = new MapLine();
	int indexToSort = (nMax) - 1;

	while (mapLine->isSolved() == false)
	{
		while (mapLine->line[indexToSort] == indexToSort + 1)
		{
			indexToSort--;
		}
		int *tmpCase = mapLine->getCase(indexToSort + 1);
		*tmpCase = mapLine[indexToSort];
		mapLine[indexToSort] = indexToSort + 1;
		nSwap++;
	}
	if (nSwap % 2 == (nMax) % 2)
		return (true);
	return (false);
}

int *Map::MapLine::getCase(int find)
{
	for (int i = 0; i < nMax; i++)
	{
		if (line[i] == find)
			 return (&(line[i]));
	}
	return (NULL);
}

bool Map::MapLine::isSolved()
{
	for (int i = 0; i < nMax; i++)
	{
		if ((i < (nMax) - 1 && i + 1 != line[i]) || (i == (nMax) - 1 && line[i] != nMax))
			return (false);
	}
	return (true);
}

void Map::MapLine::print()
{
	for (int i = 0; i < nMax; i++)
	{
		std::cout << line[i] << " ";
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

Map::MapLine::~MapLine()
{
	if (mapLine)
		delete line;
}

Map::MapLine::MapLine()
{
	int margin = 0, i = 0, j = 0, k = 0;
	line = new int[nMax];

	while (42)
	{
		while (k < mapSize - margin)
		{
			line[i] = map[j][k];
			i++;
			k++;
		}
		if (i == nMax)
			break;
		k--;
		j++;
		while (j < mapSize - margin)
		{
			line[i] = map[j][k];
			i++;
			j++;
		}
		if (i == nMax)
			break;
		j--;
		k--;
		while (k >= 0 + margin)
		{
			line[i] = map[j][k];
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
			line[i] = map[j][k];
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
		if (line[i] == 0)
			line[i] = nMax;
	}
	return (line);
}