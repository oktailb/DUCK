#ifndef __TRIBUNE_PANEL_MMI__
#define __TRIBUNE_PANEL_MMI__


#include <wx/wx.h>


class tribunePanelMMI
{
    enum
    {
        ID_LISTE_BOUCHOTS = 0,
    };

public:
    tribunePanelMMI(wxFrame *theParent);
    ~tribunePanelMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
