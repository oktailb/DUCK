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

    wxArrayString bouchots;
    wxDir::GetAllFiles("./res/conf/", &bouchots, "*.xml");
    for (u_int32_t i = 0 ; i < bouchots.size() ; ++i)
    {
        bouchot * tmp = new bouchot(bouchots[i]);
        m_vBouchots.push_back(tmp);
    }
    m_lastInsert = m_mData.begin();
}

void flowMMI::refreshMMI()
{
    static bool firstTime = true;
    for (u_int32_t i = 0 ; i < m_vBouchots.size() ; i++)
    {
        m_vBouchots[i]->refresh();
        bouchot::t_post next;
        int64_t id = 0;
        id = m_vBouchots[i]->getNextPost(next);
        while(id > 0)
        {
            addPost(id, next.norloge, (next.name.size() == 0)?("<i>" + next.info + "</i>"):("<b>" + next.name + "</b>"), next.post,
                    m_vBouchots[i]->fg(),
                    m_vBouchots[i]->bg(),
                    m_vBouchots[i]->clock(),
                    m_vBouchots[i]->norloge(),
                    m_vBouchots[i]->login(),
                    m_vBouchots[i]->answer()
                    );
            id = m_vBouchots[i]->getNextPost(next);
        }
    }

    if (firstTime)
    {
        m_lastInsert = m_mData.begin();
        firstTime = false;
    }
    m_lastInsert++;
    while (m_lastInsert != m_mData.end())
    {
        wxString date = m_lastInsert->first.substr(8, 2) + ":" + m_lastInsert->first.substr(10, 2) + ":" + m_lastInsert->first.substr(12, 2);
        wxString data = wxString("<table border=0 cellspacing=0 cellpadding=0 bgcolor='" + m_vBouchots[0]->bg() + "'><tr>")
                        + "<td><font color='" + m_vBouchots[0]->norloge() + "'>"
                        + "<a href='norlogeref_" + date + "'><b>[" + date + "]</b></a>"
                        + *(m_lastInsert->second)
                        + "</tr></table>";
        m_pPalmipede->Append(data);
        m_lastInsert++;
    }
    m_lastInsert--;
    m_pPalmipede->ScrollToRow(m_pPalmipede->GetItemCount());
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
    wxString key = date;
    wxString postData = "<td width=200 bgcolor='" + bg + "'><font color='" + login + "'>"
                    + " : "
                    + autor
                    + "</font></td>"
                    + "<td width='100%' bgcolor='" + bg + "'><font color='" + fg + "'>- "
                    + content
                    + "</font></td>";

    uint32_t level = 0;
    wxString keyOrig = key;
    while ((m_mData.find(key) != m_mData.end()) && (m_mData[key]->compare(postData) == 0))
    {
        level++;
        if (level == 1)
            key = keyOrig + "²";
        if (level == 2)
            key = keyOrig + "³";
        if (level > 2)
            key = keyOrig + "^" + wxString::FromCDouble(level);
    }
    wxString *dataCopy = new wxString(postData);
    if (dataCopy == NULL)
        return;
    m_mData.insert(std::make_pair<wxString, wxString*>(key.Clone(), dataCopy));
}

std::vector<bouchot *> flowMMI::getBouchots() const
{
    return m_vBouchots;
}

void flowMMI::setEditor(editFormMMI *pEditor)
{
    m_pEditor = pEditor;
}


void flowMMI::OnLink(wxHtmlLinkEvent &event)
{
    wxString target = event.GetLinkInfo().GetHref();
    wxLaunchDefaultBrowser(target);
}

void flowMMI::OnNorloge(wxHtmlCellEvent &event)
{
    wxString id;

    if (event.GetEventType() == wxEVT_HTML_CELL_CLICKED)
    {
        id = event.GetCell()->GetLink()->GetHref();
        if (id.BeforeFirst('_') == "norloge")
        {
            wxString ref = id.AfterFirst('_');
        }
        else if (id.BeforeFirst('_') == "norlogeref")
        {
            wxString ref = id.AfterFirst('_');
            m_pEditor->getTheConnerie()->AppendText(ref);
        }
        else
            event.Skip();
    }
    else if (event.GetEventType() == wxEVT_HTML_CELL_HOVER)
    {
        id = event.GetCell()->GetLink()->GetHref();
        if (id.BeforeFirst('_') == "norloge")
        {
            wxString ref = id.AfterFirst('_');
        }
        else
            event.Skip();
    }
    else
        event.Skip();
}

void flowMMI::createPanel()
{
    m_pPanel = new wxBoxSizer(wxVERTICAL);
    m_pPalmipede = new wxSimpleHtmlListBox(m_pParent, ID_FLOW);
    m_pPalmipede->SetMargins(-2, -2);
    m_pPanel->Add(m_pPalmipede, 1, wxALL | wxEXPAND, 0);
    m_pPalmipede->Bind(wxEVT_HTML_LINK_CLICKED  , &flowMMI::OnLink, this, ID_FLOW);
    //m_pPalmipede->Bind(wxEVT_HTML_CELL_HOVER    , &flowMMI::OnNorloge, this, ID_FLOW);
    m_pPalmipede->Bind(wxEVT_HTML_CELL_CLICKED  , &flowMMI::OnNorloge, this, ID_FLOW);
    refreshMMI();
}
