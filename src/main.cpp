#include "main.hpp"

int	main(int ac, char **av)
{
	std::ifstream fileStream;
	std::vector<std::string> file;
	int **map;
	int mapSize;
	mapSize = 0;	

	if (ac == 2)
	{
		fileStream.open(av[1]);
		if (fileStream.is_open())
		{
			readFile(fileStream, file);
			fileStream.close();
		}
		else
		{
			std::cout << "[error] open file" << std::endl;
			return (1);
		}
		map = getMap(file, mapSize);
		mapSnailOnLine(map, mapSize);
		isSolvable(map, mapSize);

		/*for (int i = 0; i < mapSize; ++i)
		{
			for (int j = 0; j < mapSize; ++j)
			{
				std::cout << map[i][j] << " " <<std::endl;	
			}
		}*/
	}
	else if (ac == 1)
		std::cout << "TODO random" << std::endl;
	else
		std::cout << "usage: ./npuzzle [file_puzzle]" << std::endl;
	return (0);
}

bool isSolvable(int **map, int mapSize)
{
	int nSwap = 0;
	int *mapLine = mapSnailOnLine(map, mapSize);
	int indexToSort = (mapSize * mapSize) - 1;

	convertMapLineToFinalMax(mapLine, mapSize);
	printMap(mapLine, mapSize);
	while (isSolved(mapLine, mapSize, mapSize * mapSize) == false)
	{
		while (mapLine[indexToSort] == indexToSort + 1)
		{
			indexToSort--;
		}
		int *tmpCase = getCase(mapLine, mapSize, indexToSort + 1);
		*tmpCase = mapLine[indexToSort];
		mapLine[indexToSort] = indexToSort + 1;
		printMap(mapLine, mapSize);
		nSwap++;
	}
	std::cout << nSwap << std::endl;
	return (true);
}

int *getCase(int *mapLine, int mapSize, int find)
{
	for (int i = 0; i < mapSize * mapSize; i++)
	{
		if (mapLine[i] == find)
			 return (&(mapLine[i]));
	}
	return (NULL);
}

bool isSolved(int *mapLine, int mapSize, int max)
{
	for (int i = 0; i < mapSize * mapSize; i++)
	{
		if ((i < (mapSize * mapSize) - 1 && i + 1 != mapLine[i]) || (i == (mapSize * mapSize) - 1 && mapLine[i] != max))
		{
			return (false);
		}
	}
	return (true);
}

void printMap(int *mapLine, int mapSize)
{
	for (int i = 0; i < mapSize * mapSize; i++)
	{
		std::cout << mapLine[i] << " ";
	}
	std::cout << std::endl;
}

void convertMapLineToFinalMax(int *mapLine, int mapSize)
{
	for (int i = 0; i < mapSize * mapSize; i++)
	{
		if (mapLine[i] == 0)
			mapLine[i] = mapSize * mapSize;
	}
}
/*
void convertMapLineToZeroFinal(int *mapLine, int mapSize)
{
	for (int i = 0; i < mapSize * mapSize; i++)
	{
		if (mapLine[i] == (mapSize * mapSize))
			mapLine[i] = 0;
	}
}*/

int *mapSnailOnLine(int **map, int mapSize)
{
	int margin = 0, i = 0, j = 0, k = 0;
	int *mapLine = new int[mapSize * mapSize];

	while (42)
	{
		while (k < mapSize - margin)
		{
			mapLine[i] = map[j][k];
			i++;
			k++;
		}
		if (i == mapSize * mapSize)
			break;
		k--;
		j++;
		while (j < mapSize - margin)
		{
			mapLine[i] = map[j][k];
			i++;
			j++;
		}
		if (i == mapSize * mapSize)
			break;
		j--;
		k--;
		while (k >= 0 + margin)
		{
			mapLine[i] = map[j][k];
			i++;
			k--;
		}
		if (i == mapSize * mapSize)
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
		if (i == mapSize * mapSize)
			break;
		j++;
		k++;
	}
	return (mapLine);
}

void readFile(std::ifstream &fileStream, std::vector<std::string> &file)
{
	std::string s;

	while (getline(fileStream, s, '\n'))
	{
		if (s.find('#') != std::string::npos)
			s.resize(s.find('#'));
		if (s.size() > 0)
			file.push_back(s);
	}
	if(file.size() < 4)
	{
		std::cout << "[error] File format" << std::endl;
		exit(1);
	}
}

int** getMap(std::vector<std::string> &file, int &mapSize)
{
	int **map;
	int *check;
	char *token;

	mapSize = atoi(file.front().c_str());	
	if ((int)file.size() - 1 != mapSize || mapSize < 3)
		errorFormat();
	check = new int[mapSize * mapSize];
	file.erase(file.begin());
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		token = strtok(strdup(file[i].c_str()), "\t ");
		int j = 0;
		while (token != NULL && j < mapSize)
		{
			map[i][j] = atoi(token);
			if (map[i][j] < mapSize * mapSize && map[i][j] >= 0)
				check[map[i][j]] = 1;
			token = strtok(NULL, "\t ");
			j++;
		}
		if (j != mapSize || token != NULL)
			errorFormat();
	}
	for (int i = 0; i < mapSize ; i++)
	{
		if (check[i] != 1)
			errorFormat();
	}
	return map;
}

void errorFormat()
{
	std::cout << "[error] File format" << std::endl;
	exit(1);
}