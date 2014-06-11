#ifndef __PLUGINS_PANEL_MMI__
#define __PLUGINS_PANEL_MMI__


#include <wx/wx.h>


class pluginsPanelMMI
{
public:
    enum
    {
        ID_TROLLO = 0,
        ID_BOTO      ,
        ID_BALDO     ,
        ID_ZOO       ,
    };

    pluginsPanelMMI(wxFrame *theParent);
    ~pluginsPanelMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
