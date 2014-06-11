#include "MMI/tribunePanelMMI.h"

tribunePanelMMI::tribunePanelMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *tribunePanelMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void tribunePanelMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    wxListBox *pListeTribunes = new wxListBox(m_pParent, ID_LISTE_BOUCHOTS);

    pListeTribunes->Insert("dlfp", 0);
    pListeTribunes->Insert("euromussels", 1);
    pListeTribunes->Insert("moules", 2);
    m_pPanel->Add(pListeTribunes, 0, wxALL | wxEXPAND, 2);
}
