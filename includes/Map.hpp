#ifndef MAP_HPP
# define MAP_HPP

#include <cstdlib>
#include <iostream>

#include "Node.hpp"

class Node;

class Map {

	public:
		Map(int **map);
		Map(Map const &rhs);
		Map &operator=(Map const &rhs);
		bool operator==(Map const& rhs);
		~Map();

		int getManhattanDistance();
		int misplaced();
		int outRowCol();
		bool isMapSolved();
		void print();
		void moveUp(int x, int y);
		void moveDown(int x, int y);
		void moveLeft(int x, int y);
		void moveRight(int x, int y);
		

		int **map;
		static int mapSize;
		static int nMax;
		static int **mapSolved;

	private:
		
};

void getCoordCase(int &x, int &y, int **mapToFind, int find);

#endif