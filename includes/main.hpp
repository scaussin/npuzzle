#ifndef MAIN_HPP
# define MAIN_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "heuristic.hpp"
#include "Map.hpp"

void readFile(std::ifstream &fileStream, std::vector<std::string> &file);
Map getMap(std::vector<std::string> &file);
void errorFormat();

/*bool isSolvable(int **map, int mapSize);
int *mapSnailOnLine(int **map, int mapSize);
bool isSolved(int *mapLine, int mapSize, int nFinal);
void convertMapLineToFinalMax(int *mapLine, int mapSize);
int *getCase(int *mapLine, int mapSize, int find);
void printMapLine(int *mapLine, int mapSize);
void printMap(int **map, int mapSize);*/

#endif