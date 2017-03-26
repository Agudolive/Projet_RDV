#include "lcpersonne.h"
#include "lcrdv.h"

#include <vector>
#include <string>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using namespace std;

class LCPersonne;
class LCRdv;

class cadre : public wxFrame
{
  public :
    cadre();
    cadre(string c_nomFrame);
    ~cadre();

  private :
    LCPersonne* repertoirePersonne;
    LCRdv* repertoireRdv;
    void OnCharger(wxCommandEvent& e);
    void OnSave(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);
    void OnAfficherPersonnes(wxCommandEvent& e);
    void OnAjouterPersonne(wxCommandEvent& e);
    void OnAjouterRdv(wxCommandEvent& e);
    void OnBoutonAjouterRdv(wxCommandEvent& e);
    void OnAfficherRdvs(wxCommandEvent& e);
    void OnAfficherEntreDates(wxCommandEvent& e);
    void OnRefreshAfficherEntreDates(wxCommandEvent& e);
    void OnAjoutListeParticipants(wxCommandEvent& e);
    void OnRetirerListeParticipants(wxCommandEvent& e);
    void OnSupprimerPersonne(wxCommandEvent& e);
    void OnBoutonAjouterPersonne(wxCommandEvent& e);
    void OnModifierPersonne(wxCommandEvent& e);
    void OnSelectionModifierPersonne(wxCommandEvent& e);
    void OnBoutonModifierPersonne(wxCommandEvent& e);
    void OnBoutonSupprimerPersonne(wxCommandEvent& e);
    void OnModiferRdv(wxCommandEvent& e);
    void OnSelectionModifierRdv(wxCommandEvent& e);
    void OnValiderModifierRdv(wxCommandEvent& e);
    void OnRdvDe(wxCommandEvent& e);
    void OnSelectionRdvDe(wxCommandEvent& e);
    void OnValiderSupprimerRdv(wxCommandEvent& e);
    void OnSupprimerRdv(wxCommandEvent& e);
    void OnDetailsPersonne(wxCommandEvent& e);
    void OnSelectionDetailsPersonne(wxCommandEvent& e);
    void OnPersonneEstLibre(wxCommandEvent& e);
    void OnSelectionPersonneEstLibre(wxCommandEvent& e);
    void OnDetailRdv(wxCommandEvent& e);
    void OnSelectionDetailRdv(wxCommandEvent& e);
    void OnDocumentation(wxCommandEvent& e);
    void OnAbout(wxCommandEvent& e);

    wxTextCtrl *c_champNom, *c_champPrenom, *c_champNumero, *c_champEmail;
    wxTextCtrl *c_jourD, *c_jourF, *c_moisD, *c_moisF, *c_anneeD, *c_anneeF;
    wxTextCtrl *c_libelle, *c_jour, *c_mois, *c_annee, *c_heureDebut, *c_heureFin;
    wxStaticText* c_choix_libelle;
    wxStaticText *c_listeRdvEntre;
    wxStaticText *txt;
    wxListBox *c_listePersonnes, *c_listeParticipants;
    wxListBox *c_toutesPersonnes, *c_tousRdv;
    wxArrayString c_arrayParticipants, c_arrayRdv;
    wxArrayString c_ajoutParticipants, c_listeBoxParticipants;
    std::vector<string> repertoire;
    wxChoice* c_choix_personne;
    wxChoice* c_choix_rdv;
    wxStaticText* c_nom;
    wxStaticText* c_prenom;
    cadre* CadreAjouterPersonne;
    cadre* CadreModifierPersonne;
    cadre* CadreSupprimerPersonne;
    cadre* CadreSupprimerRdv;
    cadre* CadreModifierRdv;
    cadre* CadreRdvDe;
    cadre* CadreDetailsPersonne;
    cadre* CadrePersonneEstLibre;
    cadre* CadreDetailRdv;
};
