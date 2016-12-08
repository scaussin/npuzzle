#ifndef SOLVE_HPP
# define SOLVE_HPP


#include "Map.hpp"
#include "main.hpp"

class Map;
class Queue;

void uniformCost(Map &start);
bool isExistAndBetter(Queue *list, Node *node);
bool cmpMap(int **map1, int **map2);
int getNeighbors(Queue *close, Queue *open, Node *cur, Node **neighbors, bool (*cmp)(Queue *list, Node *node));
void getCoordCase(int &x, int &y, int **mapToFind, int find);
void aStar(Map &start);
bool isExist(Queue *list, Node *node);

#endif