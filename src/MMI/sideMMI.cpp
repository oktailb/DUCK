#include "MMI/sideMMI.h"
#include "MMI/controlPanelMMI.h"
#include "MMI/tribunePanelMMI.h"
#include "MMI/filtersPanelMMI.h"
#include "MMI/pluginsPanelMMI.h"

sideMMI::sideMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *sideMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void sideMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    controlPanelMMI *    configPanel = new controlPanelMMI(m_pParent);
    tribunePanelMMI *   tribunePanel = new tribunePanelMMI(m_pParent);
    filtersPanelMMI *   filtersPanel = new filtersPanelMMI(m_pParent);
    pluginsPanelMMI *   pluginsPanel = new pluginsPanelMMI(m_pParent);

    m_pPanel->Add(configPanel->getPanel(), 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(tribunePanel->getPanel(), 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(filtersPanel->getPanel(), 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(pluginsPanel->getPanel(), 0, wxALL | wxEXPAND, 2);
}
