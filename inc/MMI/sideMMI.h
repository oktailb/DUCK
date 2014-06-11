#ifndef __SIDE_MMI__
#define __SIDE_MMI__


#include <wx/wx.h>


class sideMMI
{
public:
    sideMMI(wxFrame *theParent);
    ~sideMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
