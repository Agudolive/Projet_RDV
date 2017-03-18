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
    void OnAjouterRdv(wxCommandEvent& e);
    void OnBoutonAjouterRdv(wxCommandEvent& e);
    void OnAfficherRdvs(wxCommandEvent& e);
    void OnAfficherEntreDates(wxCommandEvent& e);
    void OnRefreshAfficherEntreDates(wxCommandEvent& e);
    void OnAjoutListeParticipants(wxCommandEvent& e);
    void OnRetirerListeParticipants(wxCommandEvent& e);

    wxTextCtrl *c_champNom, *c_champPrenom, *c_champNumero, *c_champEmail;
    wxTextCtrl *c_jourD, *c_jourF, *c_moisD, *c_moisF, *c_anneeD, *c_anneeF;
    wxTextCtrl *c_libelle, *c_jour, *c_mois, *c_annee, *c_heureDebut, *c_heureFin;
    wxStaticText *c_listeRdvEntre;
    wxListBox *c_listePersonnes, *c_listeParticipants;
    wxListBox *c_toutesPersonnes, *c_tousRdv;
    wxArrayString c_arrayParticipants, c_arrayRdv;
    wxArrayString c_ajoutParticipants;
    std::vector<string> repertoire;

};
