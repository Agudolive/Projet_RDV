#include "appli.h"
#include "cadre.h"

wxIMPLEMENT_APP(appli);

/**
  Initialise le cadre principale et appel son affichage
*/
bool appli::OnInit()
{
  auto c = new cadre;
  c->Show(true);

  return true;
}
