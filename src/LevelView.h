#ifndef LevelView_H_INCLUDED
#define LevelView_H_INCLUDED


#include <array>
#include "Level.h"
#include "IView.h"


class Window;
class LevelView : public IView
{
public:
    void tick();

    std::array<int,2> getDimensions();
    std::array<int,2> getOffset();
    int getBlockSize();

private:
    LevelView(Window *window);
    Window *window;
    int blockSize;

    std::array<int,2> offset;

    Level level;

    friend Window;
};


#endif // LevelView_H_INCLUDED
