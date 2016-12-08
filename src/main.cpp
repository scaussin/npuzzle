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
			std::cout << "r:" <<optarg << std::endl;
				mapMode += 'r';
				if (!optarg)
					PrintUsage();
				sizeMapRand = atoi(optarg);
				break;
			case 'f':
			std::cout << "f:" <<optarg << std::endl;
				mapMode += 'f';
				if (!optarg)
					PrintUsage();
				fileName = optarg;
				break;
			default: 
				PrintUsage();
		}
	}
	if (algo == 0 || (heur1 == 0 && heur2 == 0 && heur3 == 0) || (algo != 'a' && algo != 'g' && algo != 'u' )|| 
		(heur1 != 1 && heur2 != 2 && heur3 != 3) || mapMode == 0 || (mapMode != 'r' && mapMode != 'f'))
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
		std::cout << std::endl;
	}
	else if (mapMode == 'r')
	{
		if (sizeMapRand < 3 || sizeMapRand > 100)
		{
			std::cout << "size map out of range (3 <= size <= 100)" << std::endl;
			return (1);
		}
		mapStart = getMapRand(sizeMapRand);
		initStatics(sizeMapRand);
		mapStart->print();
	}
	else
		return (1);
	if (!isSolvable(*mapStart))
	{
		std::cout << "Map unsolvable" << std::endl;
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
			std::cout << "\t\tg -> greedy searches (without heuristic)" << std::endl;
			std::cout << "\t\tu -> uniform cost (Dijkstra)" << std::endl;
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
	int *table = NULL;
	table = new int[mapSize * mapSize];

	if (!table)
		exit(1);
	bzero(table, mapSize * mapSize);
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		int j = 0;
		while (j < mapSize)
		{
			int r = 0;
			while (table[(r = rand() % (mapSize * mapSize))] == 1)
				;
			table[r] = 1;
			map[i][j] = r;
			j++;
		}
	}

	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			
				std::cout  << map[i][j] << " ";

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	delete[] table;
	initStatics(mapSize);
	return (new Map(map));
}

Map *getMap(std::vector<std::string> &file)/*leaks*/
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

	for (int i = 0; i < Map::nMax; i++)
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