#include "MMI/editFormMMI.h"
#include "MMI/flowMMI.h"

editFormMMI::editFormMMI(wxFrame *theParent, flowMMI* flow)
{
    m_pPanel = NULL;
    m_pParent = theParent;
    m_Flow = flow;
    m_vBouchots = flow->getBouchots();
}

wxBoxSizer *editFormMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

wxTextCtrl *editFormMMI::getTheConnerie() const
{
    return m_pTheConnerie;
}

void editFormMMI::createPanel()
{
    std::vector<wxString> list;
    for (std::vector<bouchot*>::iterator it = m_vBouchots.begin() ; it != m_vBouchots.end() ; it++)
    {
        list.push_back((*it)->name());
    }

    m_pPanel = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText * text1 = new wxStaticText(m_pParent, wxID_ANY, "Post : ");
    wxStaticText * text2 = new wxStaticText(m_pParent, wxID_ANY, "Tribune : ");
    wxStaticText * text3 = new wxStaticText(m_pParent, wxID_ANY, "Cherche totoz : ");
    m_pTheConnerie = new wxTextCtrl(m_pParent, ID_CONNERIE, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    m_pTheDramarScene = new wxChoice(m_pParent, ID_DRAMAR_SCENE,
                                              wxDefaultPosition, wxDefaultSize,
                                              list.size(), list.data());
    m_pTheDramarScene->SetSelection(0);
    m_pTheNSFW = new wxTextCtrl(m_pParent, ID_NSFW);


    m_pPanel->Add(text1             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(m_pTheConnerie      , 9, wxALL | wxEXPAND, 2);
    m_pPanel->Add(text2             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(m_pTheDramarScene   , 1, wxALL | wxEXPAND, 2);
    m_pPanel->Add(text3             , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(m_pTheNSFW          , 2, wxALL | wxEXPAND, 2);

    m_pTheConnerie->Bind(wxEVT_TEXT_ENTER  , &editFormMMI::OnPost, this, ID_CONNERIE);

}

void editFormMMI::OnPost(wxEvent &event)
{
    unsigned int bouchotNum = m_pTheDramarScene->GetSelection();
    bouchot * bouchotData = m_vBouchots[bouchotNum];
    wxString toPost = m_pTheConnerie->GetValue().Clone();
    bouchotData->sendPost(toPost);
    m_pTheConnerie->Clear();
    m_Flow->refreshMMI();
}
