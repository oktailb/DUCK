#ifndef __FLOW_MMI__
#define __FLOW_MMI__

#include <wx/wx.h>
#include <stdint.h>
#include <wx/htmllbox.h>
#include "util/iniManager.h"
#include "core/bouchot.h"
#include <vector>

class flowMMI
{
public:
    enum
    {
        ID_FLOW = 0,
    };

    flowMMI(wxFrame *theParent);
    ~flowMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();
    void            addPost(uint64_t id,
                            wxString date,
                            wxString autor,
                            wxString content,
                            wxString fg, wxString bg, wxString clock, wxString norloge, wxString login, wxString answer);
private:
    wxBoxSizer *                                        m_pPanel;
    wxFrame *                                           m_pParent;
    wxSimpleHtmlListBox *                               m_pPalmipede;
    u_int64_t                                           m_i64LastId;
    iniManager *                                        m_pIniManager;
    std::map<wxString, std::pair<wxString, wxString> >  m_mData;
    std::vector<bouchot*>                               m_vBouchots;

    void            createPanel();
    void            OnLink(wxHtmlLinkEvent &event);
    void            updateBouchot(wxString base, wxString resource);

};


#endif
