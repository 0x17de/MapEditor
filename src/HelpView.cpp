#include "Gui.h"
#include "HelpView.h"

HelpView::HelpView(Window *window)
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
}

