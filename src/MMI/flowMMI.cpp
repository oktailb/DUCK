#include "MMI/flowMMI.h"
#include <wx/xml/xml.h>
#include <wx/protocol/http.h>
#include <wx/url.h>
#include <wx/utils.h>
#include "util/iniManager.h"
#include "wx/dir.h"

flowMMI::flowMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
    m_i64LastId = 0;
    m_pIniManager = new iniManager("./res/conf/config.ini");
    wxString proxy = m_pIniManager->getParam("proxy");
    wxURL::SetDefaultProxy(proxy);
    wxArrayString bouchots;
    wxDir::GetAllFiles("./res/conf/", &bouchots, "*.xml");
    for (u_int32_t i = 0 ; i < bouchots.size() ; ++i)
    {
        bouchot * tmp = new bouchot(bouchots[i]);
        m_vBouchots.push_back(tmp);
    }
}

void flowMMI::refreshMMI()
{
    for (u_int32_t i = 0 ; i < m_vBouchots.size() ; ++i)
    {
        m_vBouchots[i]->refresh();
        bouchot::t_post next;
        u_int64_t id = 0;
        while((id = m_vBouchots[i]->getNextPost(next)) != 0)
            addPost(id, next.norloge, (next.name.size() == 0)?next.info:next.name, next.post,
                    m_vBouchots[i]->fg(),
                    m_vBouchots[i]->bg(),
                    m_vBouchots[i]->clock(),
                    m_vBouchots[i]->norloge(),
                    m_vBouchots[i]->login(),
                    m_vBouchots[i]->answer()
                    );
    }
    m_pPalmipede->Refresh();
}

wxBoxSizer *flowMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void flowMMI::addPost(uint64_t id,
                      wxString date,
                      wxString autor,
                      wxString content,
                      wxString fg, wxString bg, wxString clock, wxString norloge, wxString login, wxString answer)
{
    m_pPalmipede->Insert(wxString("<table border=0 cellspacing=0 cellpadding=0 bgcolor='" + bg + "'><tr>")
                         + "<td><font color='" + norloge + "'>"
                         + "<b>[" + date.substr(8, 2) + ":" + date.substr(10, 2) + ":" + date.substr(12, 2) + "]</b>"
                         + "</font></td>"
                         + "<td width=100><font color='" + login + "'>"
                         + " : "
                         + autor
                         + "</font></td><td width='100%'><font color='" + fg + "'>- "
                         + content
                         + "</font></td>"
                         + "</tr></table>",
                         0);
}

void flowMMI::OnLink(wxHtmlLinkEvent &event)
{
    wxString target = event.GetLinkInfo().GetHref();
    wxLaunchDefaultBrowser(target);
}

void flowMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    m_pPalmipede = new wxSimpleHtmlListBox(m_pParent, ID_FLOW);
    m_pPalmipede->SetMargins(-2, -2);
    m_pPanel->Add(m_pPalmipede, 1, wxALL | wxEXPAND, 0);
    m_pPalmipede->Bind(wxEVT_HTML_LINK_CLICKED, &flowMMI::OnLink, this, ID_FLOW);
    refreshMMI();
}
