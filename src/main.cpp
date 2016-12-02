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
		aStar(map);
		std::cout << map.getManhattanDistance() << std::endl;
	}
	else if (ac == 1)
		std::cout << "TODO random" << std::endl;
	else
		std::cout << "usage: ./npuzzle [file_puzzle]" << std::endl;
	return (0);
}

void aStar(Map &start)
{
	Queue open;

	open.push(Node(&start));
	while (!open.empty())
	{
		Node cur = open.top();
		if (cur.map->isSolved())
		{
			//reconstituer chemin
			break ;
		}

		Node *neighbors = cur.map->getNeighbors();
		for(int i = 0; &neighbors[i]; i++)
		{
			//neighbors[i].map->print();
			std::cout << std::endl;
		}
	}

	/*for (std::vector<Node>::iterator i = open.begin(); i != open.end(); ++i)*/
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

void errorFormat()
{
	std::cout << "[error] File format" << std::endl;
	exit(1);
}