#include "heuristic.hpp"


int manhattanDistance(int **map, int mapSize)
{
	(void)map;
	(void)mapSize;
	//printMap(mapSolved, mapSize);

	return (0);
}

int getDistance()
{
	return (0);
}

Map genMapSolved(int mapSize)
{
	int margin = 0, i = 0, j = 0, k = 0;
	int **mapSolved = new int*[mapSize];

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
	return (Map(mapSolved, mapSize));
}