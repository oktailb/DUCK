#include "MMI/tribunePanelMMI.h"

tribunePanelMMI::tribunePanelMMI(wxFrame *theParent, std::vector<bouchot *> vBouchots)
{
    m_pPanel = NULL;
    m_pParent = theParent;
    m_vBouchots = vBouchots;
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
    m_pListeTribunes = new wxCheckListBox(m_pParent, ID_LISTE_BOUCHOTS, wxDefaultPosition, wxDefaultSize, 0, NULL,
                                          wxLB_MULTIPLE | wxLB_EXTENDED | wxLB_NEEDED_SB/* | wxLB_SORT*/);

    int i = 0;
    for (std::vector<bouchot *>::iterator it = m_vBouchots.begin() ;
         it != m_vBouchots.end() ;
         it++)
    {
        m_pListeTribunes->Insert((*it)->name(), i++);
//        m_pListeTribunes->get
    }
    for (unsigned int i = 0 ; i < m_vBouchots.size() ; i++)
    {
        m_pListeTribunes->Check(i);
    }
    m_pPanel->Add(m_pListeTribunes, 0, wxALL | wxEXPAND, 2);
}
