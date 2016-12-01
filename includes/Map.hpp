#ifndef MAP_HPP
# define MAP_HPP

#include "main.hpp"

class Map {

	public :
		Map(int **map, int mapSize);
		~Map();

		void printMapLine();
		bool isSolvable();
		void print();
		int getManhattanDistance(Map &solved);

		int **map;
		int *mapLine;
		int mapSize;
		int nMax;
		void initMapLine();
		
		bool isSolved();
		int *getCase(int find);
	private :
};

#endif