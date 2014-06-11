#ifndef __FILTERS_PANEL_MMI__
#define __FILTERS_PANEL_MMI__


#include <wx/wx.h>


class filtersPanelMMI
{
public:
    enum
    {
        ID_MY_POSTS = 0,
        ID_REPONSES    ,
        ID_BIGORNO     ,
        ID_NOUVEAUX    ,
        ID_PLONK       ,
    };

    filtersPanelMMI(wxFrame *theParent);
    ~filtersPanelMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
