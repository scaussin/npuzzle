#include "main.hpp"

int	main(int ac, char **av)
{
	std::ifstream fileStream;
	std::vector<std::string> file;
	Map *mapStart;
	int opt;
	char algo = 0;
	char heur1 = 0;
	char heur2 = 0;
	char heur3 = 0;
	char mapMode = 0;
	char *fileName = NULL;
	int sizeMapRand = 0;
	
	while ((opt = getopt(ac, av, "agu123r:f:")) != -1) 
	{
		switch (opt) 
		{
			case 'a':
				algo += 'a';
				break;
			case 'g':
				algo += 'g';
				break;
			case 'u':
				algo += 'u';
				break;
			case '1':
				heur1 += 1;
				break;
			case '2':
				heur2 += 2;
				break;
			case '3':
				heur3 += 3;
				break;
			case 'r':
				mapMode += 'r';
				if (!optarg)
					PrintUsage();
				sizeMapRand = atoi(optarg);
				break;
			case 'f':
				mapMode += 'f';
				if (!optarg)
					PrintUsage();
				fileName = optarg;
				break;
			default: 
				PrintUsage();
		}
	}
	if (algo == 0 || (heur1 == 0 && heur2 == 0 && heur3 == 0 && algo != 'u') || (algo != 'a' && algo != 'g' && algo != 'u' )|| 
		mapMode == 0 || (mapMode != 'r' && mapMode != 'f') || (heur1 != 0 && heur1 != 1)
		|| (heur2 != 0 && heur2 != 2) || (heur3 != 0 && heur3 != 3))
		PrintUsage();
	
	if (mapMode == 'f')
	{
		fileStream.open(fileName);
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
		mapStart = getMap(file);
		std::cout << "---------------------" << std::endl;
	}
	else if (mapMode == 'r')
	{
		if (sizeMapRand < 3 || sizeMapRand > 50)
		{
			std::cout << "size map out of range (3 <= size <= 50)" << std::endl;
			return (1);
		}
		mapStart = getMapRand(sizeMapRand);
		mapStart->print();
		std::cout << "---------------------" << std::endl;
	}
	else
	{
		std::cout << "exit" << std::endl;
		return (1);
	}

	if (!isSolvable(*mapStart))
		std::cout << "Map unsolvable" << std::endl;
	else
	{
		if (algo == 'a')
			aStar(mapStart, heur1, heur2, heur3);
		else if (algo == 'g')
			greedy(mapStart, heur1, heur2, heur3);
		else
			uniformCost(mapStart);
	}

	delete mapStart;
	return (0);
}

void PrintUsage()
{
	std::cout << "Usage: ./npuzzle -[<algorithm>] -[<heuristics>] [-f <file_name> | -r <size_random_puzzle>]" << std::endl;
	std::cout << "Usage: ./npuzzle -[ a | g | u ] -[123] [-f <file_name> | -r <size_random_puzzle>]" << std::endl;
		std::cout << "\t<algorithm> :" << std::endl;
			std::cout << "\t\ta -> A*" << std::endl;
			std::cout << "\t\tg -> greedy searches" << std::endl;
			std::cout << "\t\tu -> uniform cost (Dijkstra) (without heuristic)" << std::endl;
		std::cout << "\t<heuristics> :" << std::endl;
			std::cout << "\t\t1 -> Manhattan Distance" << std::endl;
			std::cout << "\t\t2 -> Tiles out of row and column" << std::endl;
			std::cout << "\t\t3 -> Misplaced Tiles" << std::endl << std::endl;
		std::cout << "\texample :" << std::endl;
			std::cout << "\t\t./npuzzle -a -1 -f file_name" << std::endl;
			std::cout << "\t\t./npuzzle -a -23 -r 3" << std::endl;
			std::cout << "\t\t./npuzzle -u -123 -r 4" << std::endl;
			std::cout << "\t\t./npuzzle -g -f file_name" << std::endl;
	exit(1);
}

void readFile(std::ifstream &fileStream, std::vector<std::string> &file)
{
	std::string s;

	while (getline(fileStream, s, '\n'))
	{
		std::cout << s << std::endl;
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

Map *getMapRand(int mapSize)
{
	int **map;
	srand (time(NULL));
	int *table = new int[mapSize * mapSize];
	int j;
	int r;

	int i = 0;
	while (i < mapSize * mapSize)
	{
		table[i] = 0;
		i++;
	}
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		j = 0;
		while (j < mapSize)
		{
			r = 0;
			while (1)
			{
				r = rand() % (mapSize * mapSize);
				if (table[r] == 0)
					break;
			}
			table[r] = 1;
			map[i][j] = r;
			j++;
		}
	
	}
	delete[] table;
	initStatics(mapSize);
	return (new Map(map));
}

Map *getMap(std::vector<std::string> &file)
{
	int mapSize;
	int **map;
	int *check;
	char *token;
	char *tmp;

	mapSize = atoi(file.front().c_str());	
	if ((int)file.size() - 1 != mapSize || mapSize < 3)
		errorFormat();
	check = new int[mapSize * mapSize];
	file.erase(file.begin());
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		tmp = strdup(file[i].c_str());
		token = strtok(tmp, "\t ");
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
		free(tmp);
	}
	for (int i = 0; i < mapSize * mapSize ; i++)
	{
		if (check[i] != 1)
			errorFormat();
	}

	delete[] check;
	initStatics(mapSize);
	return (new Map(map));
}

void errorFormat()
{
	std::cout << "[error] Map format" << std::endl;
	exit(1);
}

void initStatics(int _mapSize)
{
	Map::mapSize = _mapSize;
	Map::nMax = _mapSize * _mapSize;
	int margin = 0, i = 0, j = 0, k = 0;
	Map::mapSolved = new int*[Map::mapSize];

	for (int i = 0; i < Map::mapSize; i++)
		Map::mapSolved[i] = new int[Map::mapSize];
	while (42)
	{
		while (k < Map::mapSize - margin)
		{
			Map::mapSolved[j][k] = i + 1;
			i++;
			k++;
		}
		k--;
		if (i == Map::nMax)
			break;
		j++;
		while (j < Map::mapSize - margin)
		{
			Map::mapSolved[j][k] = i + 1;
			i++;
			j++;
		}
		j--;
		if (i == Map::nMax)
			break;
		k--;
		while (k >= 0 + margin)
		{
			Map::mapSolved[j][k] = i + 1;
			i++;
			k--;
		}
		k++;
		if (i == Map::nMax)
			break;
		j--;
		margin++;
		while (j >= 0 + margin)
		{
			Map::mapSolved[j][k] = i + 1;
			i++;
			j--;
		}
		j++;
		if (i == Map::nMax)
			break;
		k++;
	}
	Map::mapSolved[j][k] = 0;
}