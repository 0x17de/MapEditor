#ifndef TILEVIEW_H_INCLUDED
#define TILEVIEW_H_INCLUDED


#include "IView.h"

class Window;
class TileView : public IView
{
public:
    void tick();

private:
    TileView(Window *window, const std::string &tileMapConfigName);

    TileMap tileMap;
    Window *window;

    friend Window;
};


#endif // TILEVIEW_H_INCLUDED
