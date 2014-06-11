#include "Appli.h"

IMPLEMENT_APP(Appli)

bool Appli::OnInit()
{
  window = new MainWindow();	// Création de notre fenêtre
  window->createPanel();
  window->Show(TRUE); 	// Rendre visible notre fenêtre
  SetTopWindow(window);	// notre fenêtre est la fenêtre principale
  return true;
}
