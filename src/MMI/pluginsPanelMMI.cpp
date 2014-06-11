#include "MMI/pluginsPanelMMI.h"

pluginsPanelMMI::pluginsPanelMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *pluginsPanelMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void pluginsPanelMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    wxStaticText * text     = new wxStaticText(m_pParent, wxID_ANY , "Plugins : ");
    wxCheckBox * myTrollo   = new wxCheckBox(m_pParent, ID_TROLLO, "Trollometre");
    wxCheckBox * myBoto     = new wxCheckBox(m_pParent, ID_BOTO  , "Botometre");
    wxCheckBox * myBaldo    = new wxCheckBox(m_pParent, ID_BALDO , "Detecteur de chauve");
    wxCheckBox * myZoo      = new wxCheckBox(m_pParent, ID_ZOO   , "Zoode20scenes");

    m_pPanel->Add(text    , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myTrollo, 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myBoto  , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myBaldo , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(myZoo   , 0, wxALL | wxEXPAND, 2);
}
