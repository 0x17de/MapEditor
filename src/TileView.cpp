#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "Gui.h"
#include "TileView.h"

using namespace std;

TileView::TileView(Window *window, const std::string &tileMapConfigName)
:
    window(window)
{
    tileMap.load(tileMapConfigName);

    window->onEvent.add("TileView", [&] (Window &w, SDL_Event &event){
        if (w.getActiveView() != ActiveView::TILES)
            return;
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
        {
            int x = event.button.x;
            int y = w.getDimensions()[1] - event.button.y;
            cout << x << ":" << y << endl;
            float pY = 1.0 - ((y - 100.0f) / 400.0f);
            float pX = (x - 100.0f) / 400.0f;
            cout << pX << ":" << pY << endl;
            int texX = pX * tileMap.getWidth();
            int texY = pY * tileMap.getHeight();
            cout << texX << ":" << texY << endl;

            Tile *t = tileMap.getTile({{texX, texY}});
            if (t != 0)
            {
                cout << t->getName() << endl;
            }
        }
    });
}

void TileView::tick()
{
    if (window->getActiveView() != ActiveView::TILES)
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);

    auto dimensions = window->getDimensions();
    glBegin(GL_QUADS);
        glVertex3f(20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, dimensions[1] - 20.0f, 0.0f);
        glVertex3f(20.0f, dimensions[1] - 20.0f, 0.0f);
    glEnd();
    glDisable(GL_BLEND);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, tileMap.get());

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(100.0f, 100.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(500, 100.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(500.0f, 500.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(100.0f, 500.0f, 0.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}
