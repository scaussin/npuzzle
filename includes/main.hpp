#ifndef MAIN_HPP
# define MAIN_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

void readFile(std::ifstream &fileStream, std::vector<std::string> &file);
int** getMap(std::vector<std::string> &file, int &mapSize);
void errorFormat();
bool isSolvable(int **map, int mapSize);
int *mapSnailOnLine(int **map, int mapSize);
bool isSolved(int *mapLine, int mapSize, int max);
void convertMapLineToFinalMax(int *mapLine, int mapSize);
int *getCase(int *mapLine, int mapSize, int find);
void convertMapLineToZeroFinal(int *mapLine, int mapSize);
void printMap(int *mapLine, int mapSize);

#endif