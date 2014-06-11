#ifndef APPLI_H
#define APPLI_H

#include <wx/wx.h>
#include "MainWindow.h"

class Appli: public wxApp
{
public:
     bool OnInit();

private:
     MainWindow * window;  	// Un pointeur vers notre fenêtre
};

DECLARE_APP(Appli)

#endif
