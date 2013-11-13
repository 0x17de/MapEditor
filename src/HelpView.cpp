#include <GL/glut.h>
#include <string>

#include "Gui.h"
#include "HelpView.h"

using namespace std;

HelpView::HelpView(Window *window)
:
    window(window)
{
}

void HelpView::initHelp(ViewType activeView)
{
    this->activeView = activeView;
}

ViewType HelpView::getPreviousViewType()
{
    return activeView;
}

void HelpView::tick()
{
    if (window->getActiveView() != ViewType::HELP)
        return;

    auto dimensions = window->getDimensions();
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, 20.0f, 0.0f);
        glVertex3f(dimensions[0] - 20.0f, dimensions[1] - 20.0f, 0.0f);
        glVertex3f(20.0f, dimensions[1] - 20.0f, 0.0f);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(30, window->getDimensions()[1] - 45);
    for (char c : "Help")
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

