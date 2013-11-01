#include <sstream>
#include <iostream>
#include <fstream>
#include "TileMap.h"
#include "Utils.h"
#include "ImageLoader.h"
#include "Image.h"

using namespace std;

Tile::Tile(const string &name, std::array<int,4> rect)
:
    name(name),
    rect(rect)
{
}

string Tile::getName()
{
    return name;
}

bool Tile::isPointInRect(std::array<int, 2> point)
{
    return point[0] >= rect[0] && point[0] < rect[2] && point[1] >= rect[1] && point[1] < rect[3];
}

TileMap::TileMap() {}

void TileMap::load(const std::string &configFileName)
{
    ifstream in(configFileName);
    if (!in)
    {
        cout << "TileMap config '" << configFileName << "' does not exist." << endl;
        return;
    }

    string line;
    while(!getLine(in, line).eof())
    {
        if (line.at(0) == '=')
        {
            stringstream ss(line);
            ss.get();
            string tileMap, tileMapData;
            std::getline(ss, tileMap, ':');
            std::getline(ss, tileMapData);
            texture.reset(new GLTexture(ImageLoader().load(tileMap)));

            cout << "TileMap: " << tileMap << " : " << tileMapData << endl;

            {
                ifstream tilesIn(tileMapData);
                string line;
                while(!getLine(tilesIn, line).eof())
                {
                    if (line != "")
                    {
                        string name;
                        std::array<int,4> rect;

                        stringstream ss(line);
                        ss >> name;
                        string ignore;
                        ss >> ignore;
                        ss >> rect[0];
                        ss >> rect[1];
                        ss >> rect[2];
                        ss >> rect[3];
                        rect[2] += rect[0];
                        rect[3] += rect[1];
                        cout << name << ":" << rect[0] << ":" << rect[1] << ":" << rect[2] << ":" << rect[3] << endl;
                        tiles.emplace_back(name, rect);
                    }
                }
            }
        }
    }
}

GLuint TileMap::get()
{
    return texture ? texture->get() : 0;
}

int TileMap::getWidth()
{
    return texture ? texture->getWidth() : 0;
}

int TileMap::getHeight()
{
    return texture ? texture->getHeight() : 0;
}

Tile *TileMap::getTile(std::array<int,2> point)
{
    for(auto it = begin(tiles); it != end(tiles); ++it)
    {
        Tile &t = *it;
        if (t.isPointInRect(point))
            return &t;
    }
    return 0;
}

