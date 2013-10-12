#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <string>
#include <functional>
#include <array>
#include <vector>
#include <type_traits>

#include <SDL2/SDL.h>

#include "LevelView.h"

class Gui;

enum class ActiveView
{
    NONE,
    LEVEL,
    TILES
};

class Window
{
public:
    ~Window();
    void close();
    void idle();

    bool peekEvent();
    bool waitEvent();

    template<class T>
    T createView()
    {
        static_assert(std::is_base_of<IView,T>::value, "T must inherit from View");
        return T(this);
    }

    std::array<int,2> getCursorPosition();
    std::array<int,2> getDimensions();
    void flip();

    std::function<bool()> onClose;
    std::function<void(Window &w)> onIdle;

    typedef std::function<void(Window &w, SDL_Event &event)> EventCallback;
    void addOnEventCallback(EventCallback cb);
    std::vector<EventCallback> onEvent;

    ActiveView getActiveView();
    void setActiveView(ActiveView activeView);

private:
    Window(const std::string &name, int w, int h);

    std::array<int,2> dimensions;
    std::array<int,2> cursorPosition;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    ActiveView activeView;

    friend Gui;
};

class Gui
{
public:
    Gui();
    ~Gui();
    Window createWindow(const std::string &name, int w, int h);
};


#endif // GUI_H_INCLUDED
