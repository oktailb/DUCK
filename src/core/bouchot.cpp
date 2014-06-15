#include "core/bouchot.h"
#include <wx/url.h>
#include <wx/regex.h>

bouchot::bouchot(wxString configFile)
{
    m_iNext = m_mData.begin();
    m_pConfigFile = new wxXmlDocument(configFile);
    wxXmlNode * TribuneNode     = m_pConfigFile->GetRoot(); //tribune
    wxXmlNode * UrlNode         = TribuneNode->GetChildren();
    wxXmlNode * IdentityNode    = UrlNode->GetNext();
    wxXmlNode * ColorsNode      = IdentityNode->GetNext();

    m_sName         = TribuneNode->GetAttribute("name");
    m_sBaseUrl      = UrlNode->GetAttribute("base");
    m_sBackendUrl   = UrlNode->GetAttribute("backend");
    m_sPostUrl      = UrlNode->GetAttribute("post");
    m_sLogin        = IdentityNode->GetAttribute("login");
    m_sCookies      = IdentityNode->GetAttribute("cookie");
    m_sUserAgent    = IdentityNode->GetAttribute("useragent");
    m_sAnswerColor  = ColorsNode->GetAttribute("answer");
    m_sBgColor      = ColorsNode->GetAttribute("bg");
    m_sFgColor      = ColorsNode->GetAttribute("fg");
    m_sClockColor   = ColorsNode->GetAttribute("clock");
    m_sNorlogeColor = ColorsNode->GetAttribute("norloge");
    m_sLoginColor   = ColorsNode->GetAttribute("login");
}

bouchot::~bouchot()
{
    delete m_pConfigFile;
}

uint64_t bouchot::getNextPost(t_post &ret)
{
    m_iNext++;
    if (m_iNext == m_mData.end())
    {
        m_iNext--;
        return 0;
    }
    m_iNext->second.used = true;
    ret = m_iNext->second;
    return m_iNext->first;
}

void bouchot::refresh()
{
    static bool firstCall = true;
    wxURL * myUrl = new wxURL();
    myUrl->SetURL("http://" + m_sBaseUrl + "/" +  m_sBackendUrl);

    wxInputStream *httpStream = myUrl->GetInputStream();

    if (myUrl->GetError() != wxURL_PROTOERR)
    {
        // will crash here, if xml content is not formatted PERFECTLY
        wxXmlDocument xml(*httpStream);

        wxString    autor;
        wxString    message;
        wxString    info;
        wxString    date;
        uint64_t    id;
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
                        info = post->GetNodeContent();
                        //post->GetAttribute();
                    }
                    else if (post->GetName() == "message")
                    {
                        message = post->GetNodeContent();

                        wxRegEx reTotoz;
                        bool ok = reTotoz.Compile("[:([[:alnum:]_ ]+)]");

                        size_t count = reTotoz.ReplaceAll(&message, "<img src='http://totoz.eu/\\1'>");
                        count = count;

                    }
                    else if (post->GetName() == "login")
                    {
                        autor = post->GetNodeContent();
                    }
                    post = post->GetNext();
                }
                t_post tmp = {false, info, date, autor, message};
                m_mData.insert(std::make_pair<uint64_t, t_post>(id, tmp));
            }
            node = node->GetNext();
        }
    }
    else
        wxMessageBox(_T("Can't connect!"));
    if (firstCall)
    {
        m_iNext = m_mData.begin();
        firstCall = false;
    }
    wxDELETE(httpStream);
}
