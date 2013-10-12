#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <string>
#include <functional>
#include <array>
#include <map>
#include <type_traits>

#include <SDL2/SDL.h>

#include "LevelView.h"
#include "TileMap.h"

class Gui;

enum class ActiveView
{
    NONE,
    LEVEL,
    TILES
};

template <class T>
struct SetableCallback
{
    typedef std::function<T> EventCallback;
    std::map<std::string, EventCallback> callbacks;

    void add(const std::string &key, EventCallback cb)
    {
        callbacks.insert(std::make_pair(key, cb));
    }

    void remove(const std::string &key)
    {
        callbacks.erase(key);
    }

    template <class ...U>
    void operator()(U&&... args)
    {
        for(auto cbit : callbacks)
            cbit.second(std::forward<U>(args)...);
    }

    auto size() -> decltype(callbacks.size())
    {
        return callbacks.size();
    }
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
    TileMap *getTileMap();
    void flip();

    std::function<bool()> onClose;
    std::function<void(Window &w)> onIdle;

    SetableCallback<void(Window &w, SDL_Event &event)> onEvent;

    ActiveView getActiveView();
    void setActiveView(ActiveView activeView);

private:
    Window(const std::string &name, int w, int h);

    std::array<int,2> dimensions;
    std::array<int,2> cursorPosition;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    TileMap tileMap;
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
