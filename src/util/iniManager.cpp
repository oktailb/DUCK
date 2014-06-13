#include "util/iniManager.h"

iniManager::iniManager(wxString input)
{
    m_fInput = new wxTextFile();
    if (m_fInput->Open(input) != wxInvalidOffset)
    {
        wxString str;
        for ( str = m_fInput->GetFirstLine(); !m_fInput->Eof(); str = m_fInput->GetNextLine() )
        {
            str.Trim();
            wxString param = str.BeforeFirst('=');
            wxString value = str.AfterFirst('=');
            m_mData.insert(std::make_pair<wxString, wxString>(param, value));
        }
    }
}

iniManager::~iniManager()
{
    m_fInput->Close();
}

wxString    iniManager::getParam(wxString name)
{
    if (m_mData.find(name) != m_mData.end())
        return (m_mData[name]);
    return ("");
}

void        iniManager::setParam(wxString name, wxString value)
{
    m_mData.insert(std::make_pair<wxString, wxString>(name, value));
}

void        iniManager::setParam(wxString name, int value)
{
    m_mData.insert(std::make_pair<wxString, wxString>(name, wxString::FromCDouble(value)));
}

void        iniManager::setParam(wxString name, double value)
{
    m_mData.insert(std::make_pair<wxString, wxString>(name, wxString::FromCDouble(value)));
}

void        iniManager::save()
{
    m_fInput->Clear();
    for(std::map<wxString, wxString>::iterator it = m_mData.begin() ; it != m_mData.end() ; it++)
    {
        m_fInput->AddLine((*it).first + " = " + (*it).second);
    }
}
