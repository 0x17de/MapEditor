#include <iostream>
#include <GL/glut.h>
#include "Gui.h"

using namespace std;

Window::Window(const std::string& name, int w, int h)
:
    dimensions{{w,h}},
    cursorPosition{{w/2,h/2}},
    activeView(ActiveView::LEVEL)
{
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int argCount = 1;
    char progName[] = "mapeditor";
    char *argValues[] = {progName, nullptr};
    glutInit(&argCount, argValues);
}

Window::~Window()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
}

void Window::close()
{
    if (window && (!onClose || onClose()))
    {
        SDL_DestroyWindow(window);
        window = 0;
    }
}

TileMap *Window::getTileMap()
{
    return &tileMap;
}

std::array<int,2> Window::getCursorPosition()
{
    return cursorPosition;
}

std::array<int,2> Window::getDimensions()
{
    return dimensions;
}

void Window::flip()
{
    SDL_RenderPresent(renderer);
}

void Window::idle()
{
    while (window)
    {
        if (onIdle)
        {
            int x = 0;
            while(++x < 20 && peekEvent())
            {
                if (onEvent.size() > 0)
                {
                    if (event.type == SDL_EventType::SDL_MOUSEMOTION)
                    {
                        cursorPosition[0] = event.motion.x;
                        cursorPosition[1] = getDimensions()[1] - event.motion.y;
                    }

                    onEvent(*this, event);
                }
            }
            if (window && onIdle)
                onIdle(*this);
        }
        else
        {
            if (waitEvent())
            {
                onEvent(*this, event);
            }
        }
    }
}

bool Window::peekEvent()
{
    return SDL_PollEvent(&event);
}

bool Window::waitEvent()
{
    return SDL_WaitEvent(&event);
}

ActiveView Window::getActiveView()
{
    return activeView;
}

void Window::setActiveView(ActiveView activeView)
{
    this->activeView = activeView;
}

Gui::Gui()
{
    SDL_Init(SDL_INIT_VIDEO);
}

Gui::~Gui()
{
    SDL_Quit();
}

Window Gui::createWindow(const std::string& name, int w, int h)
{
    return Window(name, w, h);
}
