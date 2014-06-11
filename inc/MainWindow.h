#ifndef WIN_H
#define WIN_H

#include <wx/wx.h>
#include "MMI/editFormMMI.h"
#include "MMI/flowMMI.h"
#include "MMI/sideMMI.h"

class MainWindow: public wxFrame
{
    enum
    {
        ID_TB = 0,
        ID_TB_ADD,
        ID_TIMER,
    };

public:
    MainWindow();
    void createPanel();
    void refreshMMI();

private:
    virtual void    OnTimerTimeout(wxTimerEvent& event);
    virtual void    OnCloseWindow(wxCloseEvent &event);

    wxTimer *       m_pTimer;
    editFormMMI *   m_pEditForm;
    flowMMI *       m_pFlow;
    sideMMI *       m_pSide;

    DECLARE_EVENT_TABLE();
};
#endif
