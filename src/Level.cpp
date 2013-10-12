#include <iostream>

#include "Level.h"

using namespace std;

Block::Block(BlockType blockType, BlockFormType formType)
:
    blockType(blockType),
    formType(formType)
{}

Level::Level()
:
    dimension{{0, 0}}
{}

Block *Level::getBlock(std::array<int,2> position)
{
    if (position[1] >= rows.size())
        return 0;
    auto &cols = rows[position[1]];
    if (position[0] >= cols.size())
        return 0;
    return &cols[position[0]];
}

void Level::setBlock(std::array<int,2> position, Block block)
{
    cout << "New block at: " << position[0] << ":" << position[1] << endl;
    while (rows.size() <= position[1])
        rows.push_back(vector<Block>());
    auto &cols = rows[position[1]];
    while (cols.size() <= position[0])
        cols.push_back(Block());
    cols[position[0]] = block;
}

BlockType Block::getType()
{
    return blockType;
}

BlockFormType Block::getFormType()
{
    return formType;
}
