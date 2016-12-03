#include "isSolvable.hpp"

bool isSolvable(Map &map)
{
	int nSwap = 0;
	int *mapLineSnail = getMapLineSnail(map);
	int indexToSort = (map.nMax) - 1;

	while (isMapLineSnailSolved(mapLineSnail, map.nMax) == false)
	{
		while (mapLineSnail[indexToSort] == indexToSort + 1)
		{
			indexToSort--;
		}
		int *tmpCase = mapLineSnailChr(mapLineSnail, map.nMax, indexToSort + 1);
		*tmpCase = mapLineSnail[indexToSort];
		mapLineSnail[indexToSort] = indexToSort + 1;
		nSwap++;
		//printMapLine();
	}
	delete[] mapLineSnail;
	int x, y;
	map.getCoordCase(x, y, map.mapSolved, 0);
	int i, j;
	map.getCoordCase(i, j, map.map, 0);
	int ManhattanDistanceVide = abs(y - i) + abs(x - j);
	if (nSwap % 2 == (ManhattanDistanceVide) % 2)
		return (true);
	return (false);
}

int *mapLineSnailChr(int *mapLineSnail, int nMax, int find)
{
	for (int i = 0; i < nMax; i++)
	{
		if (mapLineSnail[i] == find)
			 return (&(mapLineSnail[i]));
	}
	return (NULL);
}

bool isMapLineSnailSolved(int *mapLineSnail, int nMax)
{
	for (int i = 0; i < nMax; i++)
	{
		if (mapLineSnail[i] != i + 1)
			return (false);
	}
	return (true);
}

void printMapLine(int *mapLineSnail, int nMax)
{
	for (int i = 0; i < nMax; i++)
	{
		std::cout << mapLineSnail[i] << " ";
	}
	std::cout << std::endl;
}

int *getMapLineSnail(Map &map)
{
	int margin = 0, i = 0, j = 0, k = 0;
	int *mapLine = new int[map.nMax];

	while (42)
	{
		while (k < map.mapSize - margin)
		{
			mapLine[i] = map.map[j][k];
			i++;
			k++;
		}
		if (i == map.nMax)
			break;
		k--;
		j++;
		while (j < map.mapSize - margin)
		{
			mapLine[i] = map.map[j][k];
			i++;
			j++;
		}
		if (i == map.nMax)
			break;
		j--;
		k--;
		while (k >= 0 + margin)
		{
			mapLine[i] = map.map[j][k];
			i++;
			k--;
		}
		if (i == map.nMax)
			break;
		k++;
		j--;
		margin++;
		while (j >= 0 + margin)
		{
			mapLine[i] = map.map[j][k];
			i++;
			j--;
		}
		if (i == map.nMax)
			break;
		j++;
		k++;
	}
	for (int i = 0; i < map.nMax; i++)
	{
		if (mapLine[i] == 0)
			mapLine[i] = map.nMax;
	}
	return (mapLine);
}