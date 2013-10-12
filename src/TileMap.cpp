#include <sstream>
#include <iostream>
#include <fstream>
#include "TileMap.h"

using namespace std;

Tile::Tile()
{
}

TileMap::TileMap() {}

void TileMap::load(const std::string &configFileName)
{
    ifstream in(configFileName);
}
