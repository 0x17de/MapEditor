#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <GL/gl.h>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

class TileMap
{
public:
    TileMap();

    void load(const std::string &configFileName);
    GLuint get();

private:
    std::shared_ptr<GLTexture> texture;
};

#endif // TILEMAP_H_INCLUDED
