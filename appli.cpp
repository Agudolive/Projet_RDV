#include "appli.h"
#include "cadre.h"

wxIMPLEMENT_APP(appli);

bool appli::OnInit()
{
  auto c = new cadre;
  c->Show(true);

  return true;
}
