#include <iostream>
#include <chrono>
#include <thread>
#include "Gui.h"
#include "LevelView.h"
#include "TileView.h"


using namespace std;

class FPS
{
public:
    FPS(float fps) : nextUpdate(chrono::high_resolution_clock::now()), timeBetweenFrames(int(1000.0 / fps))
    {
        cout << "Time between frames in ms: " << timeBetweenFrames.count() << endl;
    };
    void waitTick()
    {
        while (chrono::high_resolution_clock::now() > nextUpdate)
            nextUpdate += timeBetweenFrames;
        std::this_thread::sleep_for(nextUpdate - chrono::high_resolution_clock::now());
    };

private:
    decltype(chrono::high_resolution_clock::now()) nextUpdate;
    chrono::milliseconds timeBetweenFrames;
};

int main()
{
    Gui g;
    Window w = g.createWindow("MapEditor", 800, 600);
    FPS timer(30.0f);

    /* w.onClose = [] () {
        cout << "onClose" << endl;
        return true;
    }; */

    LevelView levelView = w.createView<LevelView>();
    TileView tileView = w.createView<TileView>("tiles.cfg");
    levelView.setTileView(&tileView);

    w.onEvent.add("main", [] (Window &w, SDL_Event &event) {
        if (event.type == SDL_EventType::SDL_WINDOWEVENT)
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                w.close();

        if (event.type == SDL_EventType::SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_SPACE:
                w.setActiveView(w.getActiveView() == ActiveView::LEVEL ? ActiveView::TILES : ActiveView::LEVEL);
                break;
            case SDLK_ESCAPE:
                w.close();
                break;
            }
        }
    });

    auto nextSecond = chrono::high_resolution_clock::now() + chrono::seconds(1);
    int fps = 0;
    w.onIdle = [&] (Window &w) {
        auto tick = chrono::high_resolution_clock::now();
        if (tick > nextSecond)
        {
            nextSecond += chrono::seconds(1);
            cout << "FPS: " << fps << endl;
            auto cursorPosition = w.getCursorPosition();
            cout << "CursorPos: " << cursorPosition[0] << ":" << cursorPosition[1] << endl;
            fps = 0;
        }
        ++fps;

        levelView.tick();
        tileView.tick();

        w.flip();

        timer.waitTick();
    };

    w.idle();
    return 0;
}
