#ifndef __FLOW_MMI__
#define __FLOW_MMI__

#include <wx/wx.h>
#include <stdint.h>
#include "MMI/palmipede.h"

class flowMMI
{
public:
    flowMMI(wxFrame *theParent);
    ~flowMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();
    void            addPost(uint64_t id, wxString date, wxString autor, wxString content);
private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;
    palmipede *     m_pPalmipede;
    u_int64_t       lastId;
    void            createPanel();
};


#endif
