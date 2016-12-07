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
		Map mapStart = getMap(file);
		std::cout << std::endl;
		if (!isSolvable(mapStart))
		{
			std::cout << "Map unsolvable" << std::endl;
			return (1);
		}
		//mapStart.initMapString();
		aStar(mapStart);
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
		if (cur->map->isMapSolved())
		{
			std::cout << "found ! cout: " << cur->cout << " open: "<< open.size()<< " close: "<< close.size()<< std::endl;
			//std::cout << "nbDoublon open: " << nbDoublon(&open) << " close: "<< nbDoublon(&close)<< std::endl;
			/*Node *tmp = cur;
			while (tmp)
			{
				tmp->map->print();
				tmp = tmp->parentNode;
			}*/
			break ;
		}
		int nNeighbors;
		Node **neighbors = cur->map->getNeighbors(nNeighbors, cur);
		/*if(close.size() % 500 == 0)
		{
			std::cout << open.size() << "\t" <<close.size() << std::endl;
		}*/
		for(int i = 0; i < nNeighbors ; i++)
		{
			neighbors[i]->cout = cur->cout + 1;
			if (isExistAndBetter(&close, neighbors[i]) || isExistAndBetter(&open, neighbors[i]))
			{
				delete neighbors[i]->map;
				delete neighbors[i];
			}
			else
			{
				neighbors[i]->heuristic = neighbors[i]->cout + neighbors[i]->map->getManhattanDistance();
				open.push(neighbors[i]);
			}
			close.push(cur);
		}
		delete[] neighbors;
	}
}

inline bool cmpMap(int **map1, int **map2)
{
	int i = 0;
	int j;

	while (i < Map::mapSize)
	{
		j = 0;
		while (j < Map::mapSize)
		{
			if (map1[i][j] != map2[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool isExistAndBetter(Queue *list, Node *node)
{
	

	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{

		
		
// if (*((*i)->map) == *(node->map) && (*i)->cout < node->cout)
		if (cmpMap(((*i)->map)->map, (node->map)->map) && (*i)->cout < node->cout)
			return (true);
	}
	return (false);
}

/*int nbDoublon(Queue *list)
{
	int n = 0;

	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		for (std::vector<Node*>::iterator j = i + 1; j != list->end(); ++j)
		{
			if (((*j)->map)->mapString != NULL && ((*i)->map)->mapString != NULL &&
			memcmp(((*j)->map)->mapString, ((*i)->map)->mapString, ((*i)->map)->nMax) == 0)
			{
				((*j)->map)->mapString = NULL;
				n++;
			}
		}
	}
	return n;
}*/

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
	initStatics(mapSize);
	return (Map(map));
}

void errorFormat()
{
	std::cout << "[error] File format" << std::endl;
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