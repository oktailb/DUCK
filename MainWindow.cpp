#include "MainWindow.h"
#include "MMI/editFormMMI.h"
#include "MMI/flowMMI.h"
#include "MMI/sideMMI.h"
#include <wx/animate.h>

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_TIMER(ID_TIMER, MainWindow::OnTimerTimeout)
END_EVENT_TABLE()

MainWindow::MainWindow()
    :
    wxFrame(NULL, -1 ,_T("\\_x<~ Da Ultimate Coin Koin"), wxDefaultPosition, wxSize(800, 600))
{
    m_pTimer = new wxTimer(this,ID_TIMER);
}

void MainWindow::OnTimerTimeout(wxTimerEvent& event)
{
    refreshMMI();
}

void MainWindow::createPanel()
{
    wxInitAllImageHandlers();

    wxBoxSizer *    MainSizer   = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *    UpSizer     = new wxBoxSizer(wxHORIZONTAL);
    m_pFlow       = new flowMMI(this);
    m_pEditForm   = new editFormMMI(this, m_pFlow);
    m_pFlow->setEditor(m_pEditForm);
    m_pSide       = new sideMMI(this, m_pFlow->getBouchots());

    m_pTimer->Start(15000);
    UpSizer->Add(m_pSide->getPanel(), 1, wxALL | wxEXPAND, 2);
    UpSizer->Add(m_pFlow->getPanel(), 42, wxALL | wxEXPAND, 2);
    MainSizer->Add(UpSizer, 42, wxALL | wxEXPAND, 2);
    MainSizer->Add(m_pEditForm->getPanel(), 0, wxBOTTOM |  wxALIGN_BOTTOM | wxEXPAND, 2);

    this->SetSizer(MainSizer);
}

void MainWindow::refreshMMI()
{
    m_pFlow->refreshMMI();
}

void MainWindow::OnCloseWindow(wxCloseEvent &event)
{
    wxLogMessage("Bye !");
}
