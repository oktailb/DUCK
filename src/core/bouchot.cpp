#include "core/bouchot.h"

bouchot::bouchot(wxString configFile)
{

}


bouchot::~bouchot()
{

}


void bouchot::refresh()
{

}
wxString bouchot::sBaseUrl() const
{
    return m_sBaseUrl;
}

void bouchot::setSBaseUrl(const wxString &sBaseUrl)
{
    m_sBaseUrl = sBaseUrl;
}

