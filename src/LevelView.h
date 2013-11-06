#ifndef LevelView_H_INCLUDED
#define LevelView_H_INCLUDED


#include <array>
#include <memory>
#include "Level.h"
#include "IView.h"

struct LevelViewKeys
{
    bool arrowUp;
    bool arrowDown;
    bool arrowLeft;
    bool arrowRight;
    bool zoomIn;
    bool zoomOut;
};

struct OperationMoveView;

class Window;
class TileView;
class LevelView : public IView
{
public:
    void tick();

    std::array<int,2> getDimensions();
    std::array<float,2> getOffset();
    void setOffset(const std::array<float,2> &newOffset);
    void moveOffset(const std::array<float,2> &moveDistance);
    void setTileView(TileView *tileView);
    const TileView *getTileView() const;
    int getBlockSize() const;

private:
    LevelView(Window *window);
    Window *window;
    int blockSize;

    std::array<float,2> offset;

    Level level;
    LevelViewKeys levelViewKeys;

    TileView *tileView;

    // @TODO: std::unique_ptr<OperationMoveView> operationMoveView;

    friend Window;
};


#endif // LevelView_H_INCLUDED
