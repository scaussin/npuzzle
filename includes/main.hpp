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

#endif