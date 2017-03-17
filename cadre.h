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
    cadre(string c_nomFrame);
  private :
    LCPersonne* repertoirePersonne;
    LCRdv* repertoireRdv;
    void OnCharger(wxCommandEvent& e);
    void OnSave(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);
    void OnAfficherPersonnes(wxCommandEvent& e);
    void OnAjouterPersonne(wxCommandEvent& e);
    void OnBoutonAjouterPersonne(wxCommandEvent& e);
    void OnModifierPersonne(wxCommandEvent& e);

    wxTextCtrl* c_champNom;
    wxTextCtrl* c_champPrenom;
    wxTextCtrl* c_champNumero;
    wxTextCtrl* c_champEmail;
    std::vector<string> repertoire;

};
