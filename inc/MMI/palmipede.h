#include "wx/htmllbox.h"

class palmipede : public wxHtmlListBox
{
public:
  palmipede (wxWindow* parent, wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxVListBoxNameStr);

protected:
  virtual wxString OnGetItem(size_t n) const;

  DECLARE_NO_COPY_CLASS(palmipede)
};

