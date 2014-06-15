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
    typedef struct  s_post
    {
        bool        used;
        wxString    info;
        wxString    norloge;
        wxString    name;
        wxString    post;
    }               t_post;

    bouchot(wxString configFile);
    ~bouchot();

    void refresh();
    uint64_t getNextPost(t_post &ret);
    inline wxString fg() {return m_sFgColor;}
    inline wxString bg() {return m_sBgColor;}
    inline wxString clock() {return m_sClockColor;}
    inline wxString norloge() {return m_sNorlogeColor;}
    inline wxString login() {return m_sLoginColor;}
    inline wxString answer() {return m_sAnswerColor;}

private:

    std::map<uint64_t, t_post> m_mData;
    std::map<uint64_t, t_post>::iterator m_iNext;
    std::map<uint64_t, t_post>::iterator m_iLastShow;
    wxXmlDocument * m_pConfigFile;
    wxString        m_sName;
    wxString        m_sBaseUrl;
    wxString        m_sBackendUrl;
    wxString        m_sPostUrl;
    wxString        m_sLogin;
    wxString        m_sCookies;
    wxString        m_sUserAgent;
    wxString        m_sBgColor;
    wxString        m_sFgColor;
    wxString        m_sClockColor;
    wxString        m_sAnswerColor;
    wxString        m_sNorlogeColor;
    wxString        m_sLoginColor;
};

#endif
