#include "Node.hpp"

Node::Node(Map *_map, Node *_parentNode) : map(_map), parentNode(_parentNode)
{
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
	
}