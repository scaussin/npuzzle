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
		map.initMapString();
		
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
		if (cur->map->isMapStringSolved())
		{
			std::cout << "found ! cout: " << cur->cout << " open: "<< open.size()<< " close: "<< close.size()<< std::endl;
			std::cout << "nbDoublon open: " << nbDoublon(&open) << " close: "<< nbDoublon(&close)<< std::endl;
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
		if(close.size() % 500 == 0)
		{
			//std::cout<<" nbDoublon open: " << nbDoublon(&open) << " close: "<< nbDoublon(&close)<< std::endl;
			std::cout << open.size() << "\t" <<close.size() << std::endl;
		}
		for(int i = 0; i < nNeighbors ; i++)
		{
			neighbors[i]->cout = cur->cout + 1;
			bool curExist;
			if (isExistClose(&close, neighbors[i], cur, curExist) || isExistAndBetter(&open, neighbors[i]))
			{
				delete neighbors[i]->map;
				delete neighbors[i];
			}
			else
			{
				neighbors[i]->heuristic = neighbors[i]->cout + neighbors[i]->map->getManhattanDistance();
				/*neighbors[i]->map->print();
				std::cout << "############################" <<std::endl;*/
				open.push(neighbors[i]);
			}
			if (!curExist)
				close.push(cur);
		}
//delete cur;
		delete[] neighbors;
	}
}

bool isExistClose(Queue *list, Node *neighbor, Node *cur, bool &curExist)
{
	curExist = false;
	bool ret = false;
	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		//if (*((*i)->map) == *(neighbor->map) && (*i)->cout < neighbor->cout)
		if (memcmp(((*i)->map)->mapString, (neighbor->map)->mapString, (cur->map)->nMax) == 0 &&
		(*i)->cout < neighbor->cout)
			ret = true;
		//if (*((*i)->map) == *(cur->map))
		if (memcmp(((*i)->map)->mapString, (cur->map)->mapString, (cur->map)->nMax) == 0)
			curExist = true;
	}
	return ret;
}

int nbDoublon(Queue *list)
{
	int n = 0;

	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		for (std::vector<Node*>::iterator j = i + 1; j != list->end(); ++j)
		{
			if (((*j)->map)->mapString != NULL && ((*i)->map)->mapString != NULL &&
			memcmp(((*j)->map)->mapString, ((*i)->map)->mapString, ((*i)->map)->nMax) == 0)
			{
				/*printMapLine(tmp, 9);
				printMapLine(((*j)->map)->mapLine, 9);
				std::cout << "############################" <<std::endl;*/
				((*j)->map)->mapString = NULL;
				n++;
			}
		}
	}
	return n;
}

bool isExistAndBetter(Queue *list, Node *cur)
{
	for (std::vector<Node*>::iterator i = list->begin(); i != list->end(); ++i)
	{
		//if (*((*i)->map) == *(cur->map))
		if (memcmp(((*i)->map)->mapString, (cur->map)->mapString, (cur->map)->nMax) == 0)
		{
			if ((*i)->cout < cur->cout) // <= ?? <
				return (true);
			else
			{
				
				//list->erase(i);
				//list->push(cur);
			}
			//std::cout << "true\n";
		}
	}
	return (false);
}

/*bool isExistAndBetter(Queue *list, Node *cur)
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
	return (Map(map, mapSize));
}

void errorFormat()
{
	std::cout << "[error] File format" << std::endl;
	exit(1);
}