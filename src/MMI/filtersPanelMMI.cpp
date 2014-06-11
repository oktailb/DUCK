#include "MMI/filtersPanelMMI.h"

filtersPanelMMI::filtersPanelMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *filtersPanelMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void filtersPanelMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    wxStaticText * text     = new wxStaticText(m_pParent, wxID_ANY , "Filtres : ");
    wxCheckBox * myPosts    = new wxCheckBox(m_pParent, ID_MY_POSTS, "Mes Posts");
    wxCheckBox * myReponses = new wxCheckBox(m_pParent, ID_REPONSES, "Reponses");
    wxCheckBox * myBigorno  = new wxCheckBox(m_pParent, ID_BIGORNO , "Bigorno<");
    wxCheckBox * myNouveaux = new wxCheckBox(m_pParent, ID_NOUVEAUX, "Nouveaux");
    wxCheckBox * myPlonk    = new wxCheckBox(m_pParent, ID_PLONK   , "Plonk");

    m_pPanel->Add(text      , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myPosts   , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myReponses, 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myBigorno , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myNouveaux, 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myPlonk   , 0, wxALL | wxEXPAND, 2);
}
