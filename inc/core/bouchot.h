#ifndef __BOUCHOT_H__
#define __BOUCHOT_H__

#include <map>
#include <wx/wx.h>
#include <stdint.h>
#include <wx/xml/xml.h>
#include <wx/colour.h>

class bouchot
{
public:
    bouchot(wxString configFile);
    ~bouchot();

    void refresh();

    wxString sBaseUrl() const;
    void setSBaseUrl(const wxString &sBaseUrl);

private:
    typedef struct  s_post
    {
        wxString    info;
        wxString    norloge;
        wxString    name;
        wxString    post;
    }               t_post;

    std::map<uint64_t, t_post> m_mData;
    wxXmlDocument * m_pConfigFile;
    wxString        m_sBaseUrl;
    wxString        m_sBackendUrl;
    wxString        m_sPostUrl;
    wxString        m_sLogin;
    wxString        m_sCookies;
    wxString        m_sUserAgent;
    wxColor         m_cMyPostColor;
    wxColor         m_cAnswerPostColor;
    wxColor         m_cClockColor;

};

#endif
