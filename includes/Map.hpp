#ifndef MAP_HPP
# define MAP_HPP

#include <cstdlib>
#include <iostream>

class Map {

	public :
		Map(int **map, int mapSize);
		~Map();

		bool isSolvable();
		void print();
		void printMapLine();
		int getManhattanDistance();
		void getCoordCase(int &x, int &y, int **mapToFind, int find);
		bool isSolved();

		int **map;
		int *mapLine;
		int mapSize;
		int nMax;

	private :
		void initMapLine();
		bool isMapLineSolved();
		int *getCase(int find);
		void initMapSolved();

		static int **mapSolved;
};

#endif