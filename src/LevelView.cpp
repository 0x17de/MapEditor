#include <iostream>
#include <sstream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include "LevelView.h"
#include "Gui.h"

using namespace std;

struct SpaceConverter
{
    SpaceConverter(LevelView *levelView) : levelView(levelView) {};

    inline float _screenToGame(std::array<int,2> screenPosition, int x)
    {
        int blockSize = levelView->getBlockSize();
        auto offset = levelView->getOffset();
        return (screenPosition[x] + offset[x] * blockSize) / blockSize;
    };
    std::array<float,2> screenToGamef(std::array<int,2> screenPosition)
    {
        return {{std::floor(_screenToGame(screenPosition, 0)), std::floor(_screenToGame(screenPosition, 1))}};
    };
    std::array<int,2> screenToGamei(std::array<int,2> screenPosition)
    {
        return {{int(std::floor(_screenToGame(screenPosition, 0))), int(std::floor(_screenToGame(screenPosition, 1)))}};
    };
    std::array<int,2> gameToScreen(std::array<float,2> gamePosition)
    {
        float blockSize = levelView->getBlockSize();
        auto offset = levelView->getOffset();
        return {{int((gamePosition[0] - offset[0]) * blockSize), int((gamePosition[1] - offset[1]) * blockSize)}};
    };

    LevelView *levelView;
};

LevelView::LevelView(Window* window)
:
    window(window),
    blockSize(50),
    offset{{0, 0}},
    level(),
    levelViewKeys{}
{
    window->onEvent.add("LevelView", [&] (Window &w, SDL_Event &event) {
        if (w.getActiveView() != ActiveView::LEVEL)
            return;

        if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                cout << "Click" << endl;
        }
        else if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                level.setBlock(SpaceConverter(this).screenToGamei(w.getCursorPosition()),
                               Block(BlockType::GRASS, BlockFormType::FULL));
            }
        }
        else if (event.type == SDL_EventType::SDL_KEYDOWN || event.type == SDL_EventType::SDL_KEYUP)
        {
            bool pressed = event.type == SDL_EventType::SDL_KEYDOWN;
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                this->levelViewKeys.arrowUp = pressed;
                break;
            case SDLK_DOWN:
                this->levelViewKeys.arrowDown = pressed;
                break;
            case SDLK_RIGHT:
                this->levelViewKeys.arrowRight = pressed;
                break;
            case SDLK_LEFT:
                this->levelViewKeys.arrowLeft = pressed;
                break;
            case SDLK_KP_PLUS:
                this->levelViewKeys.zoomIn = pressed;
                break;
            case SDLK_KP_MINUS:
                this->levelViewKeys.zoomOut = pressed;
                break;
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
            auto gamePos = cursorPosition;
            int blockSize = view->getBlockSize();
            auto offset = view->getOffset();
            std::array<int,2> gamePosDiff = {{int(gamePos[0] + offset[0] * blockSize) % blockSize, int(gamePos[1] + offset[1] * blockSize) % blockSize}};
            gamePos[0] -= gamePosDiff[0];
            gamePos[1] -= gamePosDiff[1];
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
        glRasterPos2i(cursorPosition[0] + 16, cursorPosition[1] - 16);
        stringstream ss;
        auto gamePosition = SpaceConverter(view).screenToGamei(cursorPosition);
        ss << gamePosition[0] << ":" << gamePosition[1];
        for (char c : ss.str())
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
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
            for(int i = int(-offset[1] * blockSize) % blockSize; i < dimensions[1]; i += blockSize)
            {
                glVertex3f(0.0f, i, 0.0f);
                glVertex3f(dimensions[0], i, 0.0f);
            }
            for(int i = int(-offset[0] * blockSize) % blockSize; i < dimensions[0]; i += blockSize)
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
    void draw(float x, float y, Block* block)
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
    void drawInvalid(float x, float y, Block* block)
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

        auto offset = levelView->getOffset();

        int maxx = std::ceil(float(dimensions[0]) / float(blockSize) + offset[0]);
        int maxy = std::ceil(float(dimensions[1]) / float(blockSize) + offset[1]);

        BlockDrawer blockDrawer(levelView);
        for(int j = offset[1]; j < maxy; ++j)
        {
            for(int i = offset[0]; i < maxx; ++i)
            {
                Block* block = l.getBlock({{i, j}});
                if (block != nullptr)
                    blockDrawer.draw(i-offset[0], j-offset[1], block);
            }
        }
    }
    LevelView *levelView;
};

void LevelView::setTileView(TileView* tileView)
{
    this->tileView = tileView;
}

void LevelView::tick()
{
    int zoomModifier = (levelViewKeys.zoomIn ? 1 : 0) + (levelViewKeys.zoomOut ? -1 : 0);
    int oldBlockSize = this->blockSize;
    this->blockSize += zoomModifier;
    if (this->blockSize < 1)
        this->blockSize = 1;
    auto dimension = getDimensions();

    std::array<float,2> difference = {{
        (dimension[0] / float(oldBlockSize) - dimension[0] / float(this->blockSize)) / 2.0f,
        (dimension[1] / float(oldBlockSize) - dimension[1] / float(this->blockSize)) / 2.0f
    }};
    moveOffset(difference);

    int blockSize = getBlockSize();
    moveOffset({{
        ((levelViewKeys.arrowRight ? 5.0f : 0.0f) + (levelViewKeys.arrowLeft ? -5.0f : 0.0f)) / blockSize,
        ((levelViewKeys.arrowUp ? 5.0f : 0.0f) + (levelViewKeys.arrowDown ? -5.0f : 0.0f)) / blockSize,
    }});

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

std::array<float,2> LevelView::getOffset()
{
    return offset;
}

void LevelView::setOffset(const std::array<float,2> &newOffset)
{
    offset = newOffset;
}

void LevelView::moveOffset(const std::array<float,2> &moveDistance)
{
    offset[0] += moveDistance[0];
    offset[1] += moveDistance[1];
}

int LevelView::getBlockSize()
{
    return blockSize;
}
