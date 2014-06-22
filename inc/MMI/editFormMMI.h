#ifndef __EDIT_FORM_MMI__
#define __EDIT_FORM_MMI__


#include <wx/wx.h>
#include <vector>
#include "core/bouchot.h"

class flowMMI;

class editFormMMI
{
public:

    enum
    {
        ID_CONNERIE = 0,
        ID_DRAMAR_SCENE,
        ID_NSFW,
    };

    editFormMMI(wxFrame *theParent, flowMMI* flow);
    ~editFormMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

    wxTextCtrl *getTheConnerie() const;

private:
    wxBoxSizer *            m_pPanel;
    wxFrame *               m_pParent;
    std::vector<bouchot*>   m_vBouchots;
    wxTextCtrl *            m_pTheConnerie;
    wxChoice *              m_pTheDramarScene;
    wxTextCtrl *            m_pTheNSFW;
    flowMMI *               m_Flow;
    void            createPanel();
    void            OnPost(wxEvent &event);
};
#endif
