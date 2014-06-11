#ifndef __FLOW_MMI__
#define __FLOW_MMI__

#include <wx/wx.h>
#include <stdint.h>
#include <wx/htmllbox.h>

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
    void            addPost(uint64_t id, wxString date, wxString autor, wxString content);
private:
    wxBoxSizer *            m_pPanel;
    wxFrame *               m_pParent;
    wxSimpleHtmlListBox *   m_pPalmipede;
    u_int64_t               lastId;
    void                    createPanel();

    void            OnLink(wxHtmlLinkEvent &event);
};


#endif
