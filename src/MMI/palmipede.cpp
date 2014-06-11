#include "MMI/palmipede.h"

palmipede::palmipede(wxWindow* parent, wxWindowID id,
                const wxPoint& pos, const wxSize& size,
                long style, const wxString& name) :
    wxHtmlListBox(parent, id, pos, size, style, name)
{
}

wxString
palmipede::OnGetItem(size_t n) const
{
  return wxString("list <b>HelloWorld</b>");  // << Change this to return something more useful
}
