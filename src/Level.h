#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED


#include <vector>
#include <array>

enum class BlockType
{
    NONE,
    GRASS,
    STONE
};

enum class BlockFormType
{
    FULL,
    S8,
    S9,
    S6,
    S3,
    S2,
    S1,
    S4,
    S7,
};

class Block
{
public:
    Block(BlockType blockType = BlockType::NONE, BlockFormType formType = BlockFormType::FULL);

    BlockType getType();
    BlockFormType getFormType();

    BlockType blockType;
    BlockFormType formType;
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
