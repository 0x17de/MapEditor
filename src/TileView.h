#ifndef TILEVIEW_H_INCLUDED
#define TILEVIEW_H_INCLUDED

#include "TileMap.h"
#include "IView.h"

class Tile;
class Window;
class TileView : public IView
{
public:
    void tick();
    const Tile *getActiveTile() const;
    const TileMap *getTileMap() const;

private:
    TileView(Window *window, const std::string &tileMapConfigName);

    Window *window;
    TileMap tileMap;
    Tile *activeTile;

    friend Window;
};


#endif // TILEVIEW_H_INCLUDED
