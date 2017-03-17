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
    void OnAfficherRdvs(wxCommandEvent& e);
    void OnAfficherEntreDates(wxCommandEvent& e);
    void OnRefreshAfficherEntreDates(wxCommandEvent& e);

    wxTextCtrl* c_champNom;
    wxTextCtrl* c_champPrenom;
    wxTextCtrl* c_champNumero;
    wxTextCtrl* c_champEmail;
    wxTextCtrl *c_jourD, *c_jourF, *c_moisD, *c_moisF, *c_anneeD, *c_anneeF;
    wxStaticText *c_listeRdvEntre;
    std::vector<string> repertoire;

};
