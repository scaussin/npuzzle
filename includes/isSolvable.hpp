#ifndef ISSOLVABLE_HPP
# define ISSOLVABLE_HPP

#include "Map.hpp"
class Map;

bool isSolvable(Map &map);
int *mapLineSnailChr(int *mapLineSnail, int nMax, int find);
bool isMapLineSnailSolved(int *mapLineSnail, int nMax);
void printMapLine(int *mapLineSnail, int nMax);
int *getMapLineSnail(Map &map);
void getCoordCase(int &x, int &y, int **mapToFind, int find);

#endif