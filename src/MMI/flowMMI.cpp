#include "MMI/flowMMI.h"
#include <wx/grid.h>
#include <wx/xml/xml.h>
#include <wx/protocol/http.h>

flowMMI::flowMMI(wxFrame *theParent)
{
    m_pPanel = NULL;
    m_pParent = theParent;
    lastId = 0;
}

void flowMMI::refreshMMI()
{
    wxString link;
    wxHTTP http;

    http.SetTimeout(6);
    http.Connect(_T("linuxfr.org"));
    wxInputStream *httpStream = http.GetInputStream(_T("/board/index.xml"));

    if (http.GetError() == wxPROTO_NOERR)
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
                if (id > lastId)
                    addPost(id, date, autor, message);
            }
            node = node->GetNext();
        }
        lastId = maxId;
    }
    else
        wxMessageBox(_T("Can't connect!"));

    http.Close();
    wxDELETE(httpStream);
}

wxBoxSizer *flowMMI::getPanel()
{
    if (m_pPanel == NULL)
        createPanel();
    return m_pPanel;
}

void flowMMI::addPost(uint64_t id, wxString date, wxString autor, wxString content)
{
/*
 *     m_pPalmipede->AppendText(date.substr(8, 2) + ":" + date.substr(10, 2) + ":" + date.substr(12, 2)
                               + " : " + autor
                               + "  -" + content
                               + "\n");
  */
}

void flowMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxHORIZONTAL);
    m_pPalmipede = new palmipede(m_pParent,
                                 wxID_ANY);

    m_pPanel->Add(m_pPalmipede, 0, wxALL | wxEXPAND, 2);
    refreshMMI();
}
