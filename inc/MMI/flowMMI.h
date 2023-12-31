#ifndef __FLOW_MMI__
#define __FLOW_MMI__

#include <wx/wx.h>
#include <stdint.h>
#include <wx/htmllbox.h>
#include "core/bouchot.h"
#include <vector>
#include "MMI/editFormMMI.h"

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
    std::vector<bouchot *> getBouchots() const;

    void setEditor(editFormMMI *pEditor);

private:
    wxBoxSizer *                                        m_pPanel;
    wxFrame *                                           m_pParent;
    wxSimpleHtmlListBox *                               m_pPalmipede;
    u_int64_t                                           m_i64LastId;
    std::map<wxString, wxString*>                       m_mData;
    std::vector<bouchot*>                               m_vBouchots;
    std::map<wxString, wxString*>::iterator             m_lastInsert;
    editFormMMI *                                       m_pEditor;


    void            createPanel();
    void            OnLink(wxHtmlLinkEvent &event);
    void            OnNorloge(wxHtmlCellEvent &event);
    void            updateBouchot(wxString base, wxString resource);

};


#endif
