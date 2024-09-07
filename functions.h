//
// Created by yuanliheng on 4/11/24.
//

#ifndef MINESWEEPER_FUNCTIONS_H
#define MINESWEEPER_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Tile.h"
using namespace std;

vector<int> readConfigFile(const string& filename);
map<string,string> readTxtFile(const string& filename);
void writeTxtFile(const string& filename, map<string,string> content_map);
bool compareTime(const string& time1, const string& time2);

#endif //MINESWEEPER_FUNCTIONS_H
