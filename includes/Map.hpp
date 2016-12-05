#ifndef MAP_HPP
# define MAP_HPP

#include <cstdlib>
#include <iostream>
// #include <string>

#include "Node.hpp"

class Node;

class Map {

	public:
		Map(int **map, int mapSize);
		Map(Map const &rhs);
		Map &operator=(Map const &rhs);
		bool operator==(Map const& rhs);
		~Map();

		int getManhattanDistance();
		void getCoordCase(int &x, int &y, int **mapToFind, int find);
		Node **getNeighbors(int &nNeighbors, Node *prevNode);
		bool isMapStringSolved();
		void print();
		void initMapString();

		int **map;
		char *mapString;
		int mapSize;
		int nMax;
		static int **mapSolved;
		static char *mapStringSolved;

	private:
		void moveUp(int x, int y);
		void moveDown(int x, int y);
		void moveLeft(int x, int y);
		void moveRight(int x, int y);
		void initMapsSolved();
};

#endif