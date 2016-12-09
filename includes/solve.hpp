#ifndef SOLVE_HPP
# define SOLVE_HPP


#include "Map.hpp"
#include "main.hpp"

class Map;
class Queue;

void aStar(Map *start, int heur1, int heur2, int heur3);
void greedy(Map *start, int heur1, int heur2, int heur3);
void uniformCost(Map *start);
bool isExistAndBetter(Queue *list, Node *node);
bool cmpMap(int **map1, int **map2);
int getNeighbors(Queue *close, Queue *open, Node *cur, Node **neighbors, bool (*cmp)(Queue *list, Node *node));
void getCoordCase(int &x, int &y, int **mapToFind, int find);

#endif