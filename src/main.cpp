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
		std::cout << std::endl;
		if (!isSolvable(map))
		{
			std::cout << "Map not solvable" << std::endl;
			return (1);
		}
		map.initMapLine();
		if (!map.mapLine)
		std::cout << "ok" << std::endl;
		aStar(map);
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
	Queue close;

	open.push(new Node(&start, NULL));
	while (!open.empty())
	{
		Node *cur = open.top();
		open.pop();
		if (cur->map->isMapLineSolved())
		{
			std::cout << "found ! cout: " << cur->cout << "open: "<< open.size()<< " close: "<< close.size()<< std::endl;

			Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}
			break ;
		}
		int nNeighbors;
		Node **neighbors = cur->map->getNeighbors(nNeighbors, cur);
		for(int i = 0; i < nNeighbors ; i++)
		{
			
			neighbors[i]->cout = cur->cout + 1;
			if (isExistAndBetter(&close, neighbors[i]) || isExistAndBetter(&open, neighbors[i]))
			{}
			else
			{
				neighbors[i]->heuristic = neighbors[i]->cout + neighbors[i]->map->getManhattanDistance();
				/*neighbors[i]->map->print();
				std::cout << "############################" <<std::endl;*/
				open.push(neighbors[i]);
			}
			close.push(cur);
		}
	}
}

bool isExistAndBetter(Queue *list, Node *cur)
{
	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		if (*((*i)->map) == *(cur->map) && (*i)->cout < cur->cout)
		{
			//std::cout << "true\n";
			return (true);
		}
	}
	return (false);
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

Map getMap(std::vector<std::string> &file)/*leaks*/
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