#include "main.hpp"

int	main(int ac, char **av)
{
	std::ifstream fileStream;
	std::vector<std::string> file;
	int **map;
	int mapSize;

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
		for (int i = 0; i < mapSize; ++i)
		{
			for (int j = 0; j < mapSize; ++j)
			{
				std::cout << map[i][j] << " " <<std::endl;	
			}
		}
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
	/*while (i < (int)file.size())
	{
		std::cout << file[i] << std::endl;
		i++;
	}*/
}

int** getMap(std::vector<std::string> &file, int &mapSize)
{
	int **map;
	char *token;

	mapSize = atoi(file.front().c_str());	
	if ((int)file.size() - 1 != mapSize || mapSize < 3)
	{
		std::cout << "[error] File format" << std::endl;
		exit(1);
	}
	file.erase(file.begin());
	map = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		map[i] = new int[mapSize];
		//std::string s = file[i];
		//char *yourMother = s.c_str();
		token = strtok(strdup(file[i].c_str()), "\t ");
		int j = 0;
		while (token != NULL && j < mapSize)
		{
			map[i][j] = atoi(token);

			token = strtok(NULL, "\t ");
			j++;
		}
		if (j != mapSize)
		{
			std::cout << "[error] File format" << std::endl;
			exit(1);
		}		
	}
	return map;
}




































