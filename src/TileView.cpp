
#include <GL/gl.h>

#include "Gui.h"
#include "TileView.h"

TileView::TileView(Window *window, const std::string &tileMapConfigName)
:
    window(window)
{
    window->onEvent.add("TileView", [&] (Window &w, SDL_Event &event){
        if (w.getActiveView() != ActiveView::TILES)
            return;
    });
    tileMap.load(tileMapConfigName);
}

void TileView::tick()
{
    if (window->getActiveView() != ActiveView::TILES)
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);

    auto dimensions = window->getDimensions();
    glBegin(GL_QUADS);
        glVertex3f(20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, dimensions[1] - 20.0f, 0.0f);
        glVertex3f(20.0f, dimensions[1] - 20.0f, 0.0f);
    glEnd();
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tileMap.get());
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(100.0f, 100.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(500, 100.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(500.0f, 500.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(100.0f, 500.0f, 0.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
