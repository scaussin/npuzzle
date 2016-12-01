#include "main.hpp"

int	main(int ac, char **av)
{
	std::ifstream fileStream;
	std::vector<std::string> file;

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
		Map map = getMap(file);
		if (!map.isSolvable())
		{
			std::cout << "Map not solvable" << std::endl;
			return (1);
		}
		/*mapSnailOnLine(map, mapSize);
		isSolvable(map, mapSize);
		genMapSolved(mapSize);
		manhattanDistance(map, mapSize);*/
	}
	else if (ac == 1)
		std::cout << "TODO random" << std::endl;
	else
		std::cout << "usage: ./npuzzle [file_puzzle]" << std::endl;
	return (0);
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

Map getMap(std::vector<std::string> &file)
{
	int mapSize;
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
	for (int i = 0; i < mapSize * mapSize ; i++)
	{
		if (check[i] != 1)
			errorFormat();
	}
	return (Map(map, mapSize));
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

void errorFormat()
{
	std::cout << "[error] File format" << std::endl;
	exit(1);
}