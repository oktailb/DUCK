#ifndef __INI_MANAGER__
#define __INI_MANAGER__

#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <map>

class iniManager
{
public:
    iniManager(wxString input);
    ~iniManager();

    wxString    getParam(wxString name);
    void        setParam(wxString name, wxString value);
    void        setParam(wxString name, int value);
    void        setParam(wxString name, double value);

    void save();
private:
    wxTextFile *                    m_fInput;
    std::map<wxString, wxString>    m_mData;
};

#endif
