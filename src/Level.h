#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED


#include <vector>
#include <array>

class Tile;

class Block
{
public:
    Block(const Tile* tile = 0);
    const Tile* getTile() const;

private:
    const Tile* tile;
};

class Level
{
public:
    Level();
    Block* getBlock(std::array<int,2> position);
    void setBlock(std::array<int,2> position, Block block);
    std::array<int,2> getDimension(int x, int y);
private:
    std::vector<std::vector<Block>> rows;
    std::array<int,2> dimension;
};


#endif // LEVEL_H_INCLUDED
