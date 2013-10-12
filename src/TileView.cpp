
#include <GL/gl.h>

#include "Gui.h"
#include "TileView.h"

TileView::TileView(Window *window)
:
    window(window)
{
    window->addOnEventCallback([&] (Window &w, SDL_Event &event){
        if (w.getActiveView() != ActiveView::TILES)
            return;
    });
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
}
