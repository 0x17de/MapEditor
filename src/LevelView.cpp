#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "LevelView.h"
#include "Gui.h"

using namespace std;

struct SpaceConverter
{
    SpaceConverter(LevelView *levelView) : levelView(levelView) {};
    std::array<int,2> screenToGame(std::array<int,2> screenPosition) {
        float blockSize = levelView->getBlockSize();
        return std::array<int,2>{{int(screenPosition[0] / blockSize), int(screenPosition[1] / blockSize)}};
    };
    std::array<int,2> gameToScreen(std::array<float,2> gamePosition) {
        float blockSize = levelView->getBlockSize();
        return std::array<int,2>{{int(gamePosition[0] * blockSize), int(gamePosition[1] * blockSize)}};
    };
    LevelView *levelView;
};

LevelView::LevelView(Window* window)
:
    window(window),
    blockSize(50),
    offset{{0, 0}},
    level()
{
    window->addOnEventCallback([&] (Window &w, SDL_Event &event) {
        if (w.getActiveView() != ActiveView::LEVEL)
            return;

        if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
            if (event.button.button == SDL_BUTTON_LEFT)
                cout << "Click" << endl;
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                level.setBlock(SpaceConverter(this).screenToGame(w.getCursorPosition()),
                               Block(BlockType::GRASS, BlockFormType::FULL));
            }
        }
    });
}

struct Mouse
{
    Mouse(Window *window, LevelView *view) : window(window), view(view) {};
    void draw() {
        auto cursorPosition = window->getCursorPosition();
        glColor3f(0.0f, 1.0f, 0.0f);
        glPointSize(10.0f);
        glBegin(GL_POINTS);
            glVertex3f(cursorPosition[0], cursorPosition[1], 0.0f);
        glEnd();
        if (window->getActiveView() == ActiveView::LEVEL) {
            auto gamePos = SpaceConverter(view).screenToGame(cursorPosition);
            int blockSize = view->getBlockSize();
            gamePos[0] *= blockSize;
            gamePos[1] *= blockSize;
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
            glBegin(GL_QUADS);
                glVertex3f(gamePos[0], gamePos[1], 0.0f);
                glVertex3f(gamePos[0] + blockSize, gamePos[1], 0.0f);
                glVertex3f(gamePos[0] + blockSize, gamePos[1] + blockSize, 0.0f);
                glVertex3f(gamePos[0], gamePos[1] + blockSize, 0.0f);
            glEnd();
            glDisable(GL_BLEND);
        }
    }
    Window *window;
    LevelView *view;
};

struct Grid
{
    Grid(LevelView *levelView) : levelView(levelView) {};
    void draw()
    {
        glPushMatrix();
        glLoadIdentity();

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
            auto dimensions = levelView->getDimensions();
            auto offset = levelView->getOffset();
            int blockSize = levelView->getBlockSize();
            for(int i = offset[1] % blockSize; i < dimensions[1]; i += blockSize)
            {
                glVertex3f(0.0f, i, 0.0f);
                glVertex3f(dimensions[0], i, 0.0f);
            }
            for(int i = offset[0] % blockSize; i < dimensions[0]; i += blockSize)
            {
                glVertex3f(i, 0.0f, 0.0f);
                glVertex3f(i, dimensions[1], 0.0f);
            }
        glEnd();

        glPopMatrix();
    }
    LevelView *levelView;
};

struct BlockDrawer
{
    BlockDrawer(LevelView* levelView) : levelView(levelView) {};
    void draw(int x, int y, Block* block)
    {
        switch(block->getType())
        {
        case BlockType::NONE:
            break;
        default:
            drawInvalid(x, y, block);
            break;
        }
    }
    void drawInvalid(int x, int y, Block* block)
    {
        int blockSize = levelView->getBlockSize();
        glColor3f(1.0f, 0.0f, 1.0f);
        x *= blockSize;
        y *= blockSize;
        glBegin(GL_QUADS);
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + blockSize, y, 0.0f);
            glVertex3f(x + blockSize, y + blockSize, 0.0f);
            glVertex3f(x, y + blockSize, 0.0f);
        glEnd();
    }
    LevelView* levelView;
};

struct LevelDrawer
{
    LevelDrawer(LevelView* levelView) : levelView(levelView) {};
    void draw(Level &l)
    {
        auto dimensions = levelView->getDimensions();
        int blockSize = levelView->getBlockSize();

        int maxx = std::ceil(float(dimensions[0]) / float(blockSize));
        int maxy = std::ceil(float(dimensions[1]) / float(blockSize));
        BlockDrawer blockDrawer(levelView);
        for(int j = 0; j < maxy; ++j)
        {
            for(int i = 0; i < maxx; ++i)
            {
                Block* block = l.getBlock({{i, j}});
                if (block != nullptr)
                    blockDrawer.draw(i, j, block);
            }
        }
    }
    LevelView *levelView;
};

void LevelView::tick()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 800, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    LevelDrawer(this).draw(level);

    Grid(this).draw();
    Mouse(window, this).draw();
}

std::array<int,2> LevelView::getDimensions()
{
    return window->getDimensions();
}

std::array<int,2> LevelView::getOffset()
{
    return offset;
}

int LevelView::getBlockSize()
{
    return blockSize;
}
