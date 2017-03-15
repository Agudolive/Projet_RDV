#include "lcpersonne.h"
#include "lcrdv.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class LCPersonne;
class LCRdv;

class cadre : public wxFrame
{
  public :
    cadre();
  private :
    LCPersonne* repertoirePersonne;
    LCRdv* repertoireRdv;
    void OnCharger(wxCommandEvent& e);
    void OnSave(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);
    void OnAfficherPersonnes(wxCommandEvent& e);

};
