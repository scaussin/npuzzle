#ifndef MAIN_HPP
# define MAIN_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <map>

#include "Map.hpp"
#include "Node.hpp"
#include "isSolvable.hpp"

class Map;
class Node;

class mycomparison
{
	public:
		bool operator() (const Node *lhs, const Node *rhs) const
		{
			return (lhs->heuristic > rhs->heuristic);
		}
};

typedef std::priority_queue<Node *, std::vector<Node *>, mycomparison> pq;

class Queue : public pq
{
	public:
		std::vector<Node *>::iterator begin()
		{
			return (pq::c.begin());
		}
		std::vector<Node *>::iterator end()
		{
			return (pq::c.end());
		}
};

void readFile(std::ifstream &fileStream, std::vector<std::string> &file);
Map getMap(std::vector<std::string> &file);
void errorFormat();
void aStar(Map &start);
Node *findNode(Queue *list, Node *find);

//int nbDoublon(Queue *lst);
bool isExistAndBetter(Queue *list, Node *node);
void initStatics(int mapSize);
bool cmpMap(int **map1, int **map2);
int getNeighbors(Queue *close, Queue *open, Node *cur, Node **neighbors);
void getCoordCase(int &x, int &y, int **mapToFind, int find);

#endif