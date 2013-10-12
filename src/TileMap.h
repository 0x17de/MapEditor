#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <string>
#include <vector>

class Tile
{
public:
    Tile();
};

class TileMap
{
public:
    TileMap();

    void load(const std::string &configFileName);
private:
    std::vector<Tile> tiles;
};

#endif // TILEMAP_H_INCLUDED
