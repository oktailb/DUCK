#ifndef __CONFIG_PANEL_MMI__
#define __CONFIG_PANEL_MMI__


#include <wx/wx.h>


class controlPanelMMI
{
public:
    enum
    {
        ID_BALLTRAP = 0,
        ID_ATTACH    ,
        ID_DISPALL   ,
        ID_REFRESHALL,
        ID_STOPALL   ,
        ID_CONFIG    ,
        ID_BOSSMODE  ,

    };

    controlPanelMMI(wxFrame *theParent);
    ~controlPanelMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
