#ifndef MAP_HPP
# define MAP_HPP

#include "main.hpp"
#include <cstdlib>

class Map {

	public :
		Map(int **map, int mapSize);
		~Map();

		bool isSolvable();
		void print();
		void printMapLine();
		bool isSolved();
		int getManhattanDistance(Map &solved);
		void getCoordCase(int &x, int &y, int find);

		int **map;
		int *mapLine;
		int mapSize;
		int nMax;

	private :
		void initMapLine();
		int *getCase(int find);
};

#endif