#include "Node.hpp"

Node::Node(Map *_map, Node *_parentNode) : map(_map), parentNode(_parentNode)
{
	cout = _parentNode->cout;
	heuristic = 0;
}

Node::Node(Map *_map) : map(_map)
{
	parentNode = NULL;
	cout = 0;
	heuristic = 0;
}

Node::Node()
{
	cout = 0;
	heuristic = 0;
}

Node::~Node()
{
	delete map;
}