#include "MMI/editFormMMI.h"

editFormMMI::editFormMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *editFormMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void editFormMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText * text1 = new wxStaticText(m_pParent, wxID_ANY, "Post : ");
    wxStaticText * text2 = new wxStaticText(m_pParent, wxID_ANY, "Tribune : ");
    wxStaticText * text3 = new wxStaticText(m_pParent, wxID_ANY, "Cherche totoz : ");
    wxTextCtrl * pTheConnerie = new wxTextCtrl(m_pParent, ID_CONNERIE);
    wxChoice * pTheDramarScene = new wxChoice(m_pParent, ID_DRAMAR_SCENE);
    wxTextCtrl * pTheNSFW = new wxTextCtrl(m_pParent, ID_NSFW);

    m_pPanel->Add(text1             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(pTheConnerie      , 9, wxALL | wxEXPAND, 2);
    m_pPanel->Add(text2             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(pTheDramarScene   , 1, wxALL | wxEXPAND, 2);
    m_pPanel->Add(text3             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(pTheNSFW          , 2, wxALL | wxEXPAND, 2);
    m_pPanel->SetMinSize(-1, 100);
}
