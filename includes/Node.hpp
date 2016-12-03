#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

#include "Map.hpp"

class Map;

class Node {

	public:
		Node(Map *map, Node *parentNode);
		Node();
		~Node();

		Map *map;
		Node *parentNode;
		int cout;
		int heuristic;

	private:

};

#endif