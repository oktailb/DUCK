#include "MMI/controlPanelMMI.h"

controlPanelMMI::controlPanelMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
}

wxBoxSizer *controlPanelMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void controlPanelMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxHORIZONTAL);
    wxBitmapButton * ballTrapButton     = new wxBitmapButton(m_pParent, ID_BALLTRAP     , wxBitmap("./res/icons/coin.png"));
    wxBitmapButton * attachButton       = new wxBitmapButton(m_pParent, ID_ATTACH       , wxBitmap("./res/icons/attach.png"));
    wxBitmapButton * displayAllButton   = new wxBitmapButton(m_pParent, ID_DISPALL      , wxBitmap("./res/icons/dispall.png"));
    wxBitmapButton * refreshAllButton   = new wxBitmapButton(m_pParent, ID_REFRESHALL   , wxBitmap("./res/icons/refreshall.png"));
    wxBitmapButton * stopAllButton      = new wxBitmapButton(m_pParent, ID_STOPALL      , wxBitmap("./res/icons/stopall.png"));
    wxBitmapButton * configButton       = new wxBitmapButton(m_pParent, ID_CONFIG       , wxBitmap("./res/icons/config.png"));
    wxBitmapButton * bossModeButton     = new wxBitmapButton(m_pParent, ID_BOSSMODE     , wxBitmap("./res/icons/bossmode.png"));

    m_pPanel->Add(ballTrapButton  , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(attachButton    , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(displayAllButton, 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(refreshAllButton, 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(stopAllButton   , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(configButton    , 0, wxALL | wxEXPAND, 2);
    m_pPanel->Add(bossModeButton  , 0, wxALL | wxEXPAND, 2);
}
