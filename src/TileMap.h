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
    Tile(const std::string &name, std::array<int,4> rect, std::array<float,4> texCoords);
    std::string getName() const;
    bool isPointInRect(std::array<int,2> point) const;
    std::array<float,4> getTexCoords() const;
private:
    std::string name;
    std::array<int,4> rect;
    std::array<float,4> texCoords;
};

class TileMap
{
public:
    TileMap();

    void load(const std::string &configFileName);
    GLuint get();
    int getWidth();
    int getHeight();
    const GLTexture *getTexture() const;
    Tile *getTile(std::array<int,2> point);

private:
    std::vector<Tile> tiles;
    std::shared_ptr<GLTexture> texture;
};

#endif // TILEMAP_H_INCLUDED
