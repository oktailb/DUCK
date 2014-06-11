#ifndef __EDIT_FORM_MMI__
#define __EDIT_FORM_MMI__


#include <wx/wx.h>


class editFormMMI
{
public:

    enum
    {
        ID_CONNERIE = 0,
        ID_DRAMAR_SCENE,
        ID_NSFW,
    };

    editFormMMI(wxFrame *theParent);
    ~editFormMMI();

    void            refreshMMI();
    void            clearMMI();

    wxBoxSizer *    getPanel();

private:
    wxBoxSizer *    m_pPanel;
    wxFrame *       m_pParent;

    void            createPanel();
};


#endif
