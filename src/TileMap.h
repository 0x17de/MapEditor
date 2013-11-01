#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <GL/gl.h>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include "Image.h"

class Tile
{
public:
    Tile(const std::string &name, std::array<int,4> rect);
    std::string getName();
    bool isPointInRect(std::array<int,2> point);
private:
    std::string name;
    std::array<int,4> rect;
};

class TileMap
{
public:
    TileMap();

    void load(const std::string &configFileName);
    GLuint get();
    int getWidth();
    int getHeight();
    Tile *getTile(std::array<int,2> point);

private:
    std::vector<Tile> tiles;
    std::shared_ptr<GLTexture> texture;
};

#endif // TILEMAP_H_INCLUDED
