#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

#include "Map.hpp"

class Map;

class Node {

	public :
		Node(Map *map);
		Node();
		~Node();

		Map *map;
		int cout;
		int heuristic;

	private :

};

#endif