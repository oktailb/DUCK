#ifndef __SIDE_MMI__
#define __SIDE_MMI__


#include <wx/wx.h>
#include <vector>
#include <core/bouchot.h>

class sideMMI
{
public:
    sideMMI(wxFrame *theParent, std::vector<bouchot*> vBouchots);
    ~sideMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *            m_pPanel;
    wxFrame *               m_pParent;
    std::vector<bouchot*>   m_vBouchots;

    void            createPanel();
};


#endif
