#ifndef HELPVIEW_H_INCLUDED
#define HELPVIEW_H_INCLUDED


#include "IView.h"

enum class ViewType;
class HelpView : public IView
{
public:
    void initHelp(ViewType activeView);
    ViewType getPreviousViewType();

    void tick();

    friend Window;

private:
    HelpView(Window *window);

    ViewType activeView;
};


#endif // HELPVIEW_H_INCLUDED
