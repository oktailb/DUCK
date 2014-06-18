#ifndef __TRIBUNE_PANEL_MMI__
#define __TRIBUNE_PANEL_MMI__


#include <wx/wx.h>
#include <vector>
#include <core/bouchot.h>

class tribunePanelMMI
{
    enum
    {
        ID_LISTE_BOUCHOTS = 0,
    };

public:
    tribunePanelMMI(wxFrame *theParent, std::vector<bouchot *> vBouchots);
    ~tribunePanelMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *            m_pPanel;
    wxFrame *               m_pParent;
    wxCheckListBox *        m_pListeTribunes;
    std::vector<bouchot *>  m_vBouchots;

    void            createPanel();
};


#endif
