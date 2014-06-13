#include "MMI/flowMMI.h"
#include <wx/xml/xml.h>
#include <wx/protocol/http.h>
#include <wx/url.h>
#include <wx/utils.h>
#include "util/iniManager.h"

flowMMI::flowMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
    m_i64LastId = 0;
    m_pIniManager = new iniManager("./res/conf/config.ini");
}

void flowMMI::updateBouchot(wxString base, wxString resource)
{
    wxString proxy = m_pIniManager->getParam("proxy");
    wxURL::SetDefaultProxy(proxy);
    wxURL * myUrl = new wxURL();
    myUrl->SetURL("http://" + base + "/" +  resource);

    wxInputStream *httpStream = myUrl->GetInputStream();

    if (myUrl->GetError() != wxURL_PROTOERR)
    {
        // will crash here, if xml content is not formatted PERFECTLY
        wxXmlDocument xml(*httpStream);

        wxString    autor;
        wxString    message;
        uint64_t    id;
        uint64_t    maxId = 0;
        wxString  date;
        wxXmlNode * node = xml.GetRoot()->GetChildren();
        while (node)
        {
            if (node->GetName() == _T("post"))
            {
                node->GetAttribute("id").ToCULong(&id);
                date = node->GetAttribute("time");
                wxXmlNode * post = node->GetChildren();
                while (post)
                {
                    if (post->GetName() == "info")
                    {
                        //post->GetAttribute();
                    }
                    else if (post->GetName() == "message")
                    {
                        message = post->GetNodeContent();
                    }
                    else if (post->GetName() == "login")
                    {
                        autor = post->GetNodeContent();
                    }
                    post = post->GetNext();
                }
                if (id > maxId)
                    maxId = id;
                if (id > m_i64LastId)
                    addPost(id, date, autor, message);
            }
            node = node->GetNext();
        }
        m_i64LastId = maxId;
    }
    else
        wxMessageBox(_T("Can't connect!"));
    wxDELETE(httpStream);
}

void flowMMI::refreshMMI()
{
    updateBouchot("linuxfr.org", "board/index.xml");
    m_pPalmipede->Refresh();
}

wxBoxSizer *flowMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void flowMMI::addPost(uint64_t id, wxString date, wxString autor, wxString content)
{
    m_pPalmipede->Insert(wxString("<body bgcolor=#ffffff>")
                         + "<b>[" + date.substr(8, 2) + ":" + date.substr(10, 2) + ":" + date.substr(12, 2) + "]</b>"
                         + " : " + autor
                         + "  -" + content
                         + "</body>",
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
    m_pPanel->Add(m_pPalmipede, 1, wxALL | wxEXPAND, 2);
    m_pPalmipede->Bind(wxEVT_HTML_LINK_CLICKED, &flowMMI::OnLink, this, ID_FLOW);
    refreshMMI();
}
