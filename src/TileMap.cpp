#include <sstream>
#include <iostream>
#include <fstream>
#include "TileMap.h"
#include "Utils.h"
#include "ImageLoader.h"
#include "Image.h"

using namespace std;

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
        }
    }
}

GLuint TileMap::get()
{
    return texture ? texture->get() : 0;
}
