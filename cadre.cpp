#include "cadre.h"

#include "lcpersonne.h"
#include "lcrdv.h"
#include "fromJson.h"

#include <wx/utils.h>
#include <wx/filefn.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

cadre::~cadre()
{
  delete repertoirePersonne;
  delete repertoireRdv;
}

/**
  Construit le cadre principal et créé les élements de la fenêtre principale
*/
cadre::cadre() : wxFrame{nullptr, wxID_ANY, "Gestion de rendez-vous", wxDefaultPosition}
{
  enum
  {
    ID_LOAD, ID_NEW_PERSONNE, ID_EDIT_PERSONNE, ID_DELETE_PERSONNE,
    ID_NEW_RDV, ID_EDIT_RDV, ID_DELETE_RDV, ID_DOC, ID_A_PROPOS,
    ID_LISTE_PERSONNES, ID_LISTE_RDV, ID_RDV_DE, ID_RDV_ENTRE,
    ID_DETAIL_RDV, ID_DETAIL_PERSONNE, ID_TOUTES_PERSONNES,ID_EST_LIBRE
  };

  // auto  CadreMenuPrithisncipal = new cadre("Menu Principal");

  //initialisation des repertoires
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  //creation du panneau vide
  auto panneau = new wxPanel{this, wxID_ANY};

  //creation des menus
  auto menufichier = new wxMenu;
  menufichier -> Append(wxID_SAVE, "Sauvegarder");
  menufichier -> Append(ID_LOAD, "Charger");
  menufichier -> Append(wxID_EXIT, "Quitter");

  auto menupersonne = new wxMenu;
  menupersonne -> Append(ID_NEW_PERSONNE, "Nouvelle personne");
  menupersonne -> Append(ID_EDIT_PERSONNE, "Editer personne");
  menupersonne -> Append(ID_DELETE_PERSONNE, "Supprimer personne");

  auto menurdv = new wxMenu;
  menurdv -> Append(ID_NEW_RDV, "Nouveau rendez-vous");
  menurdv -> Append(ID_EDIT_RDV, "Editer rendez-vous");
  menurdv -> Append(ID_DELETE_RDV, "Supprimer rendez-vous");

  auto menuediter = new wxMenu;
  menuediter -> AppendSubMenu(menupersonne, "Personnes");
  menuediter -> AppendSubMenu(menurdv, "Rendez-vous");

  auto menuafficher = new wxMenu;
  menuafficher -> Append(ID_LISTE_PERSONNES, "Liste personnes");
  menuafficher -> Append(ID_LISTE_RDV, "Liste rendez-vous");
  menuafficher -> Append(ID_RDV_DE, "Rendez-vous de ...");
  menuafficher -> Append(ID_RDV_ENTRE, "Rendez-vous entre ...");
  menuafficher -> Append(ID_DETAIL_RDV, "Details du rendez-vous");
  menuafficher -> Append(ID_DETAIL_PERSONNE, "Details de la personne");
  menuafficher -> Append(ID_EST_LIBRE, "Personne est libre");

  auto menuaide = new wxMenu;
  menuaide -> Append(ID_DOC, "Documentation");
  menuaide -> Append(ID_A_PROPOS, "A propos");

  //creation de la barre de menus
  auto menubar = new wxMenuBar;
  menubar -> Append(menufichier, "Fichier");
  menubar -> Append(menuediter, "Editer");
  menubar -> Append(menuafficher, "Afficher");
  menubar -> Append(menuaide, "Aide");
  SetMenuBar(menubar);


  //affichage des focntionnalités disponibles
  wxString champ = "";
      // wxString::FromUTF8("\xC2\xA0");

  champ += wxString::FromUTF8("Fonctionnalites disponibles :\x000D\x000D");
  champ += "Menu Fichier :\x000D\x0009- Sauvegarde et recuperation d'une liste de personnes et de rendez-vous\x000D\x000D";
  champ += "Menu Editer :\x000D\x0009- Creation/Edition/suppressions de personnes et rendez-vous\x000D\x000D";
  champ += "Menu Afficher :\x000D\x0009- Liste des personnes avec leurs informations\x000D\x0009- Liste des rendez-vous avec date et heure\x000D\x0009- Tous les rendez vous d'une personne\x000D\x0009- Les details d'un rdv c-a-d les personnes le composant\x000D\x0009- Les rdv entre 2 date\x000D\x000D";
  champ += "Menu Aide :\x000D\x0009- Un lien vers la documentation du projet\x000D\x0009- Les acteurs du projet";

  auto txt = new wxStaticText{panneau,wxID_STATIC,champ,wxDefaultPosition, wxDefaultSize,0, wxStaticTextNameStr};

  auto sizer = new wxBoxSizer{wxHORIZONTAL};
  sizer->Add(txt,1, wxEXPAND | wxALL,10);

  panneau->SetSizerAndFit(sizer);
  SetClientSize(panneau->GetSize());
  SetMinSize(panneau->GetSize());

  //liaisons
  Bind(wxEVT_MENU, &cadre::OnCharger, this, ID_LOAD);
  Bind(wxEVT_MENU, &cadre::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &cadre::OnExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &cadre::OnAfficherPersonnes, this, ID_LISTE_PERSONNES);
  Bind(wxEVT_MENU, &cadre::OnAfficherRdvs, this, ID_LISTE_RDV);
  Bind(wxEVT_MENU, &cadre::OnAjouterPersonne, this, ID_NEW_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnAjouterRdv, this, ID_NEW_RDV);
  Bind(wxEVT_MENU, &cadre::OnAfficherEntreDates, this, ID_RDV_ENTRE);
  Bind(wxEVT_MENU, &cadre::OnAjouterPersonne, this, ID_NEW_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnModifierPersonne, this, ID_EDIT_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnSupprimerPersonne, this, ID_DELETE_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnModiferRdv, this, ID_EDIT_RDV);
  Bind(wxEVT_MENU, &cadre::OnRdvDe, this, ID_RDV_DE);
  Bind(wxEVT_MENU, &cadre::OnSupprimerRdv, this, ID_DELETE_RDV);
  Bind(wxEVT_MENU, &cadre::OnDetailsPersonne, this, ID_DETAIL_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnPersonneEstLibre, this, ID_EST_LIBRE);
  Bind(wxEVT_MENU, &cadre::OnDetailRdv, this, ID_DETAIL_RDV);
  Bind(wxEVT_MENU, &cadre::OnDocumentation, this, ID_DOC);
  Bind(wxEVT_MENU, &cadre::OnAbout, this, ID_A_PROPOS);
}

/**
  Construit un objet de type cadre, permet la création de plusieures fenêtres différentes au seins de l'application
  @param[in] c_nomFrame - un string contenant le nom de la fenêtre à créer
*/
cadre::cadre(string c_nomFrame) : wxFrame{nullptr, wxID_ANY, c_nomFrame, wxDefaultPosition}{

}

/**
  Charge la liste de personnes et rendez-vous à partir du fichier json
  @param[in] e - un evenement declanché par le menu "Fichier -> Charger"
  @param[out] repertoirePersonne, repertoireRdv - les répertoires remplis
*/
void cadre::OnCharger(wxCommandEvent& e){

  delete repertoirePersonne;
  delete repertoireRdv;

  //appel lors du chargement json
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  fromJson json_load = fromJson{repertoirePersonne, repertoireRdv};

  json_load.getRepertoire();
  json_load.getRdv();
}

/**
  Sauvegarde la liste de personnes et de rendez-vous dans un fichier json
  @param[in] e - un evenement declanché par le menu "Fichier -> Save"
  @param[out] repertoirePersonne, repertoireRdv - les répertoires à sauvegarder
*/
void cadre::OnSave(wxCommandEvent& e)
{
  //appel de la sauvegarde json
  fromJson json_save = fromJson{repertoirePersonne, repertoireRdv};

  json_save.saveRepertoire();
  json_save.saveRdv();
}

/**
  Ferme le cadre principale
  @param[in] e - un evenement declanché par le menu "Fichier -> Quit"
*/
void cadre::OnExit(wxCommandEvent& e)
{
  Close();
}

/**
  Ouvre un fenêtre et affiche la liste de toutes les prsonnes
  @param[in] e - un evenement declanché par le menu "Afficher -> Liste personnes"
*/
void cadre::OnAfficherPersonnes(wxCommandEvent& e)
{
  auto  CadreListePersonne = new cadre("Liste des contacts");
  CadreListePersonne -> Show(true);
  auto panneau = new wxPanel{CadreListePersonne, wxID_ANY};

  chainonPersonne* crt = repertoirePersonne->getTete();
  wxString t;
  while(crt){
    t += wxString::FromUTF8("\xC2\xA0");
    t += repertoirePersonne->getNom(crt);
    t += wxString::FromUTF8("\xC2\xA0;\xC2\xA0");
    t += repertoirePersonne->getPrenom(crt);
    t += wxString::FromUTF8("\xC2\xA0;\xC2\xA0");
    t += repertoirePersonne->getNumero(crt);
    t += wxString::FromUTF8("\xC2\xA0;\xC2\xA0");
    t += repertoirePersonne->getEmail(crt);
    t += "\n";
    crt = repertoirePersonne->getSuivant(crt);
  }
  auto txt = new wxStaticText{panneau,wxID_STATIC,t};
  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(txt,1, wxEXPAND | wxALL,10);
  panneau->SetSizerAndFit(sizer);
  CadreListePersonne->SetSize(panneau->GetSize());
  CadreListePersonne->SetMinSize({300,50});
}

/**
  Ouvre un fenêtre et affiche la liste de toutes les rendez-vous
  @param[in] e - un evenement declanché par le menu "Afficher -> Liste rendez-vous"
*/
void cadre::OnAfficherRdvs(wxCommandEvent& e)
{
  auto  CadreListeRdvs = new cadre("Liste des rendez-vous");
  CadreListeRdvs -> Show(true);
  auto panneau = new wxPanel{CadreListeRdvs, wxID_ANY};

  chainonRdv* crt = repertoireRdv->getTete();
  wxString t;
  while(crt){

    t += wxString::FromUTF8("\xC2\xA0");
    t += repertoireRdv->getLibelle(crt);
    t += " le " + wxString::Format(wxT("%i"),repertoireRdv->getJour(crt));
    t += "/" + wxString::Format(wxT("%i"),repertoireRdv->getMois(crt));
    t += "/" + wxString::Format(wxT("%i"),repertoireRdv->getAnnee(crt));
    t += " de " + wxString::Format(wxT("%i"),repertoireRdv->getHeureDebut(crt)) + "h";
    t += " a " + wxString::Format(wxT("%i"),repertoireRdv->getHeureFin(crt)) + "h";

    t += "\n";

    crt = repertoireRdv->getSuivant(crt);
  }

  auto txt = new wxStaticText{panneau,wxID_STATIC,t};
  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(txt,1, wxEXPAND | wxALL,10);
  panneau->SetSizerAndFit(sizer);
  CadreListeRdvs->SetSize(panneau->GetSize());
  CadreListeRdvs->SetMinSize({300,50});

}

/**
  Ouvre un fenêtre et demande a l'utilisateur les informations pour ajouter une nouvelle personne
  @param[in] e - un evenement declanché par le menu "Editer -> Personnes -> Editer personne"
*/
void cadre::OnAjouterPersonne(wxCommandEvent& e){

  enum{ID_BOUTON};

  CadreAjouterPersonne = new cadre("Ajouter une personne");
  CadreAjouterPersonne -> Show(true);
  auto panneau = new wxPanel{CadreAjouterPersonne, wxID_ANY};

  auto txt1 = new wxStaticText{panneau, wxID_STATIC,("Nom : ")};
  auto txt2 = new wxStaticText{panneau, wxID_STATIC,("Prenom : ")};
  auto txt3 = new wxStaticText{panneau, wxID_STATIC,("Numero : ")};
  auto txt4 = new wxStaticText{panneau, wxID_STATIC,("Email : ")};

  c_champNom = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_champPrenom = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_champNumero = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_champEmail = new wxTextCtrl(panneau, wxID_STATIC,"");

  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto sizer1 = new wxBoxSizer{wxHORIZONTAL};
  sizer1->Add(txt1,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer1->AddStretchSpacer(1);
  sizer1->Add(c_champNom,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer2 = new wxBoxSizer{wxHORIZONTAL};
  sizer2->Add(txt2,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer2->AddStretchSpacer(1);
  sizer2->Add(c_champPrenom,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer3 = new wxBoxSizer{wxHORIZONTAL};
  sizer3->Add(txt3,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer3->AddStretchSpacer(1);
  sizer3->Add(c_champNumero,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer4 = new wxBoxSizer{wxHORIZONTAL};
  sizer4->Add(txt4,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer4->AddStretchSpacer(1);
  sizer4->Add(c_champEmail,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer5 = new wxBoxSizer{wxVERTICAL};
  sizer5->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer5->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer5->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer5->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer5->Add(bouton,0,wxALIGN_LEFT | wxALL, 10);

  panneau->SetSizerAndFit(sizer5);
  CadreAjouterPersonne->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnBoutonAjouterPersonne, this);
}

/**
  Ajoute une personne avec les informations données par l'utilisateur
  @param[in] e - un evenement declanché par la méthode "cadre::OnAjouterPersonne"
*/
void cadre::OnBoutonAjouterPersonne(wxCommandEvent& e){

  repertoirePersonne->ajouter(std::string(c_champNom->GetValue()), std::string(c_champPrenom->GetValue()), std::string(c_champNumero->GetValue()), std::string(c_champEmail->GetValue()));
  CadreAjouterPersonne->Close(true);
}

/**
  Ouvre un fenêtre et demande a l'utilisateur les informations pour ajouter un nouveau rendez-vous
  @param[in] e - un evenement declanché par le menu "Editer -> Rendez-vous -> Editer rendez-vous"
*/
void cadre::OnAjouterRdv(wxCommandEvent& e)
{
  enum{
    ID_BOUTON_AJOUTER_RDV, ID_LISTE_PERSONNES, ID_LISTE_PARTICIPANTS,
    ID_BOUTON_AJOUTER, ID_BOUTON_RETIRER
  };

  auto CadreAjouterRdv = new cadre{"Ajouter un rendez-vous"};
  CadreAjouterRdv -> Show(true);
  CadreAjouterRdv -> SetMaxSize({500, 700});
  auto panneau = new wxPanel{CadreAjouterRdv, wxID_ANY};

  auto txt1 = new wxStaticText{panneau, wxID_STATIC,("Libelle : ")};
  auto txt2 = new wxStaticText{panneau, wxID_STATIC,("Jour : ")};
  auto txt3 = new wxStaticText{panneau, wxID_STATIC,("Mois : ")};
  auto txt4 = new wxStaticText{panneau, wxID_STATIC,("Annee : ")};
  auto txt5 = new wxStaticText{panneau, wxID_STATIC,("Heure debut : ")};
  auto txt6 = new wxStaticText{panneau, wxID_STATIC,("Heure fin : ")};

  c_libelle = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_jour = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_mois = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_annee = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureDebut = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureFin = new wxTextCtrl(panneau, wxID_STATIC,"");

  auto boutonConfirmer = new wxButton(panneau, ID_BOUTON_AJOUTER_RDV, "Ajouter");
  auto boutonAjouter = new wxButton(panneau, ID_BOUTON_AJOUTER, ">");
  auto boutonRetirer = new wxButton(panneau, ID_BOUTON_RETIRER, "<");

  c_ajoutParticipants.Empty();
  chainonPersonne* crt = repertoirePersonne->getTete();
  while(crt)
  {
    wxString nom = repertoirePersonne->getNom(crt);
    wxString prenom = repertoirePersonne->getPrenom(crt);
    c_ajoutParticipants.Add(nom + " " + prenom);
    crt = repertoirePersonne->getSuivant(crt);
  }
  c_listePersonnes = new wxListBox(panneau, ID_LISTE_PERSONNES, wxDefaultPosition, {150, 200}, c_ajoutParticipants, 0, wxDefaultValidator, wxListBoxNameStr);
  c_listeParticipants = new wxListBox(panneau, ID_LISTE_PARTICIPANTS, wxDefaultPosition, {150, 200}, 0, nullptr, 0, wxDefaultValidator, wxListBoxNameStr);

  auto sizer1 = new wxBoxSizer{wxHORIZONTAL};
  sizer1->Add(txt1,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer1->AddStretchSpacer(1);
  sizer1->Add(c_libelle,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer2 = new wxBoxSizer{wxHORIZONTAL};
  sizer2->Add(txt2,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer2->AddStretchSpacer(1);
  sizer2->Add(c_jour,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer3 = new wxBoxSizer{wxHORIZONTAL};
  sizer3->Add(txt3,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer3->AddStretchSpacer(1);
  sizer3->Add(c_mois,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer4 = new wxBoxSizer{wxHORIZONTAL};
  sizer4->Add(txt4,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer4->AddStretchSpacer(1);
  sizer4->Add(c_annee,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer5 = new wxBoxSizer{wxHORIZONTAL};
  sizer5->Add(txt5,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer5->AddStretchSpacer(1);
  sizer5->Add(c_heureDebut,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer6 = new wxBoxSizer{wxHORIZONTAL};
  sizer6->Add(txt6,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer6->AddStretchSpacer(1);
  sizer6->Add(c_heureFin,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer7 = new wxBoxSizer{wxVERTICAL};
  sizer7->Add(boutonAjouter, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);
  sizer7->Add(boutonRetirer, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer8 = new wxBoxSizer{wxHORIZONTAL};
  sizer8->Add(c_listePersonnes, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer7, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(c_listeParticipants, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);

  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer5,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer6,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer8,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(boutonConfirmer,0,wxALIGN_LEFT | wxALL, 10);


  panneau->SetSizerAndFit(sizer);
  CadreAjouterRdv->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  boutonAjouter->Bind(wxEVT_BUTTON, &cadre::OnAjoutListeParticipants, this);
  boutonRetirer->Bind(wxEVT_BUTTON, &cadre::OnRetirerListeParticipants, this);
  boutonConfirmer->Bind(wxEVT_BUTTON, &cadre::OnBoutonAjouterRdv, this);

}

/**
  Ajoute une personne à la liste de participants d'un rendez-vous
  @param[in] e - un evenement declanché par la méthode "cadre::OnAjouterRdv"
*/
void cadre::OnAjoutListeParticipants(wxCommandEvent& e)
{
  int i = c_listePersonnes->GetSelection();
  if(i>=0)
  {
    bool dejaAjoute = false;
    int nb = c_listeParticipants->GetCount();
    for(int j=0; j<nb; j++)
    {
      if(c_listePersonnes->GetString(i) == c_listeParticipants->GetString(j))
        dejaAjoute = true;
    }

    if(!dejaAjoute)
      c_listeParticipants->InsertItems(1, &c_ajoutParticipants[i], 0);
  }
}

/**
  Retire une personne de la liste de participants d'un rendez-vous
  @param[in] e - un evenement declanché par la méthode "cadre::OnAjouterRdv"
*/
void cadre::OnRetirerListeParticipants(wxCommandEvent& e)
{
  int i = c_listeParticipants->GetSelection();
  if(i>=0)
    c_listeParticipants->Delete(i);
}

/**
  Ajoute un rendez-vous avec les informations données par l'utilisateur
  @param[in] e - un evenement declanché par la méthode "cadre::OnAjouterRdv"
*/
void cadre::OnBoutonAjouterRdv(wxCommandEvent& e)
{
  wxArrayString liste;
  int nb = c_listeParticipants->GetCount();

  for(int i=0; i<nb; i++)
    liste.Add(c_listeParticipants->GetString(i));
  liste.Sort();

  vector<vector<string>>listeVector(nb, vector<string>(2, ""));
  for(int i=0; i<nb; i++)
  {
    string tmp, nom, prenom;
    tmp = string(liste[i]);
    stringstream ss(tmp);
    getline(ss, nom, ' ');
    getline(ss, prenom, ' ');

    listeVector[i][0]=nom;
    listeVector[i][1]=prenom;
  }

  string libelle = std::string(c_libelle->GetValue());
  int jour = wxAtoi(c_jour->GetValue());
  int mois = wxAtoi(c_mois->GetValue());
  int annee = wxAtoi(c_annee->GetValue());
  int heureDebut = wxAtoi(c_heureDebut->GetValue());
  int heureFin = wxAtoi(c_heureFin->GetValue());

  //on vérifie si tous les participants de la liste sont libres
  bool conditionParticipants = true;
  unsigned i = 0;
  while( (conditionParticipants==true) & (i<listeVector.size()) )
  {
    conditionParticipants = repertoireRdv->estLibre(listeVector[i][0], listeVector[i][1], jour, mois, annee, heureDebut, jour, mois, annee, heureFin);
    ++i;
  }

  //on vérifie si le rdv n'existe pas deja
  bool conditionLibelle = true;
  chainonRdv* crt = repertoireRdv->getTete();
  while( (conditionLibelle==true) & (crt!=nullptr))
  {
    if(libelle==repertoireRdv->getLibelle(crt))
      conditionLibelle = false;

    crt = repertoireRdv->getSuivant(crt);
  }

  if( !conditionLibelle )
    wxMessageBox("Ce rendez-vous existe deja");
  else if( (jour>=32) | (jour<=0) )
    wxMessageBox("Le jour choisi est invalide");
  else if( (mois>=13) | (mois<=0) )
    wxMessageBox("Le mois choisi est invalide");
  else if( annee==0 )
    wxMessageBox("L'annee choisie est invalide");
  else if( (heureDebut>=24) | (heureDebut<=0) )
    wxMessageBox("L'heure de commencement choisie est invalide");
  else if( (heureFin>=24) | (heureFin<=0) )
    wxMessageBox("L'heure de fin choisie est invalide");
  else if(!conditionParticipants)
  {
    wxString txt = listeVector[i-1][0] + " " + listeVector[i-1][1];
    txt.Printf(wxT("%s a deja un rendez-vous"), txt);
    wxMessageBox(txt);
  }
  else
    repertoireRdv->ajouter(libelle, jour, mois, annee, heureDebut, heureFin, listeVector);
}


/**
  Créé une fenêtre et affiche les rendez-vous entre deux dates
  @param[in] e - un evenement declanché par le menu "Afficher -> Rendez-vous entre..."
*/
void cadre::OnAfficherEntreDates(wxCommandEvent& e)
{
  enum{
    ID_BOUTON_AFFICHER
  };

  auto cadreAfficherEntreDates = new cadre{"Rendez-vous entre dates"};
  cadreAfficherEntreDates -> Show(true);
  auto panneau = new wxPanel{cadreAfficherEntreDates, wxID_ANY};


  auto jourD = new wxStaticText{panneau, wxID_STATIC,("Jour debut : ")};
  auto jourF = new wxStaticText{panneau, wxID_STATIC,("Jour fin : ")};
  auto moisD = new wxStaticText{panneau, wxID_STATIC,("Mois debut : ")};
  auto moisF = new wxStaticText{panneau, wxID_STATIC,("Mois Fin : ")};
  auto anneeD = new wxStaticText{panneau, wxID_STATIC,("Annee debut : ")};
  auto anneeF = new wxStaticText{panneau, wxID_STATIC,("Annee Fin : ")};

  c_jourD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_jourF = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_moisD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_moisF = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_anneeD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_anneeF = new wxTextCtrl(panneau, wxID_STATIC,"");

  auto bouton = new wxButton(panneau, ID_BOUTON_AFFICHER, "Afficher");


  auto sizer1 = new wxBoxSizer{wxHORIZONTAL};
  sizer1->Add(jourD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer1->AddStretchSpacer(1);
  sizer1->Add(c_jourD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer2 = new wxBoxSizer{wxHORIZONTAL};
  sizer2->Add(jourF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer2->AddStretchSpacer(1);
  sizer2->Add(c_jourF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer3 = new wxBoxSizer{wxHORIZONTAL};
  sizer3->Add(moisD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer3->AddStretchSpacer(1);
  sizer3->Add(c_moisD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer4 = new wxBoxSizer{wxHORIZONTAL};
  sizer4->Add(moisF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer4->AddStretchSpacer(1);
  sizer4->Add(c_moisF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer5 = new wxBoxSizer{wxHORIZONTAL};
  sizer5->Add(anneeD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer5->AddStretchSpacer(1);
  sizer5->Add(c_anneeD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer6 = new wxBoxSizer{wxHORIZONTAL};
  sizer6->Add(anneeF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer6->AddStretchSpacer(1);
  sizer6->Add(c_anneeF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  c_listeRdvEntre = new wxStaticText{panneau,wxID_STATIC,""};

  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer5,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer6,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(bouton,0,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(c_listeRdvEntre,1,wxALIGN_LEFT | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  cadreAfficherEntreDates->SetSize(panneau->GetSize());
  cadreAfficherEntreDates->SetMinSize({300,50});

  bouton->Bind(wxEVT_BUTTON, &cadre::OnRefreshAfficherEntreDates, this);
}

/**
  Raffraichis la liste des rendez-vous lorsque l'utilisateur change les dates
  @param[in] e - un evenement declanché par la méthode "cadre::OnAfficherEntreDates"
*/
void cadre::OnRefreshAfficherEntreDates(wxCommandEvent& e)
{
  wxString t;

  vector<string> liste =  repertoireRdv->afficherEntreDates(wxAtoi(c_jourD->GetValue()),wxAtoi(c_moisD->GetValue()),wxAtoi(c_anneeD->GetValue()),wxAtoi(c_jourF->GetValue()),wxAtoi(c_moisF->GetValue()),wxAtoi(c_anneeF->GetValue()));
  for(unsigned i=0; i<liste.size(); i++)
  {
    t += liste[i];
    t += wxString::FromUTF8("\xC2\xA0;\xC2\xA0");
  }

  c_listeRdvEntre->SetLabel(t);
  c_champNom->SetValue("");
  c_champPrenom->SetValue("");
  c_champNumero->SetValue("");
  c_champEmail->SetValue("");
}

/**
  Ouvre un fenêtre et demande a l'utilisateur les informations pour modifier une personne
  @param[in] e - un evenement declanché par le menu "Editer -> Personnes -> Editer personnes"
*/
void cadre::OnModifierPersonne(wxCommandEvent& e){

  enum{ID_CHOIX,ID_BOUTON};

  wxArrayString repertoire;

  chainonPersonne* crt = repertoirePersonne->getTete();
  while(crt){
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }

  CadreModifierPersonne = new cadre("Modifier une personne");
  CadreModifierPersonne -> Show(true);
  auto panneau = new wxPanel{CadreModifierPersonne, wxID_ANY};

  c_choix_personne = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);

  c_nom = new wxStaticText{panneau, wxID_STATIC,("Nom")};
  c_prenom = new wxStaticText{panneau, wxID_STATIC,("Prenom")};
  c_champNumero = new wxTextCtrl(panneau, wxID_STATIC,"Numero");
  c_champEmail = new wxTextCtrl(panneau, wxID_STATIC,"Email");

  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto sizer1 = new wxBoxSizer{wxVERTICAL};
  sizer1->Add(c_choix_personne,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);
  sizer1->Add(c_nom,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);
  sizer1->Add(c_prenom,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);
  sizer1->Add(c_champNumero,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);
  sizer1->Add(c_champEmail,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);
  sizer1->Add(bouton,2.5,wxALIGN_LEFT | wxEXPAND | wxALL, 10);

  panneau->SetSizerAndFit(sizer1);
  CadreModifierPersonne->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  c_choix_personne->Bind(wxEVT_CHOICE, &cadre::OnSelectionModifierPersonne, this);
  bouton->Bind(wxEVT_BUTTON, &cadre::OnBoutonModifierPersonne, this);
}

/**
  Met a jour l'affichage des informations lorsque la personne a modifier est choisie
  @param[in] e - un evenement declanché par la méthode "cadre::OnModifierPersonne"

*/
void cadre::OnSelectionModifierPersonne(wxCommandEvent& e){

  int sel = c_choix_personne->GetSelection();
  chainonPersonne* crt = repertoirePersonne->getTete();
  int i = 0;
  while(i != sel){
    crt = repertoirePersonne->getSuivant(crt);
    i++;
  }

  c_nom->SetLabel(repertoirePersonne->getNom(crt));
  c_prenom->SetLabel(repertoirePersonne->getPrenom(crt));
  c_champNumero->SetValue(repertoirePersonne->getNumero(crt));
  c_champEmail->SetValue(repertoirePersonne->getEmail(crt));
}

/**
  Applique les modifications demandées par l'utilisateur
  @param[in] e -   @param[in] e - un evenement declanché par la méthode "cadre::OnModifierPersonne"
*/
void cadre::OnBoutonModifierPersonne(wxCommandEvent& e){

  if(c_choix_personne->GetSelection() == wxNOT_FOUND){
    CadreModifierPersonne->Close(true);
    return;
  }
  repertoirePersonne->modifierNumero(string(c_nom->GetLabel()),string(c_prenom->GetLabel()),string(c_champNumero->GetValue()));
  repertoirePersonne->modifierEmail(string(c_nom->GetLabel()),string(c_prenom->GetLabel()),string(c_champEmail->GetValue()));
  CadreModifierPersonne->Close(true);
}

/**
  Affiche un fenêtre permettant à l'utilisateur de selectionner une personne à Supprimer
  @param[in] e - un evenement declanché par le menu "Editer -> Personnes -> Supprimer personne"
*/
void cadre::OnSupprimerPersonne(wxCommandEvent& e){

  enum{ID_CHOIX,ID_BOUTON};

  wxArrayString repertoire;

  chainonPersonne* crt = repertoirePersonne->getTete();
  while(crt){
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }

  CadreSupprimerPersonne = new cadre("Supprimer une personne");
  CadreSupprimerPersonne -> Show(true);
  auto panneau = new wxPanel{CadreSupprimerPersonne, wxID_ANY};

  c_choix_personne = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);

  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto sizer1 = new wxBoxSizer{wxVERTICAL};
  sizer1->Add(c_choix_personne,6,wxALIGN_CENTER | wxEXPAND | wxALL, 10);
  sizer1->Add(bouton,6,wxALIGN_LEFT | wxEXPAND | wxALL, 10);

  panneau->SetSizerAndFit(sizer1);
  CadreSupprimerPersonne->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnBoutonSupprimerPersonne, this);
}

/**
  Supprime la personne selectionnée
  @param[in] e - un evenement declanché par la méthode "cadre::OnSupprimerPersonne"
*/
void cadre::OnBoutonSupprimerPersonne(wxCommandEvent& e){

  if(c_choix_personne->GetSelection() == wxNOT_FOUND){
    CadreSupprimerPersonne->Close(true);
    return;
  }
  bool b;
  enum{ID_CHOIX};
  wxArrayString repertoire;
  int sel = c_choix_personne->GetSelection();
  chainonPersonne* crt = repertoirePersonne->getTete();
  int i = 0;
  while(i != sel){
    crt = repertoirePersonne->getSuivant(crt);
    i++;
  }
  b = repertoirePersonne->supprimer(string(repertoirePersonne->getNom(crt)),string(repertoirePersonne->getPrenom(crt)),repertoireRdv);
  if(!b)
    wxMessageBox("Impossible de supprimer ce contact","Attention",wxOK);
  CadreSupprimerPersonne->Close(true);
}

/**
  Ouvre un fenêtre et demande a l'utilisateur les informations pour modifier un rendez-vous
  @param[in] e - un evenement declanché par le menu "Editer -> Rendez-vous -> Editer rendez-vous"
*/
void cadre::OnModiferRdv(wxCommandEvent& e){

  wxArrayString listeRDV;

  chainonRdv* crt = repertoireRdv->getTete();
  while(crt){
    listeRDV.Add(repertoireRdv->getLibelle(crt));
    crt = repertoireRdv->getSuivant(crt);
  }

  enum{ID_CHOIX,ID_BOUTON, ID_BOUTON_AJOUTER,
    ID_BOUTON_RETIRER, ID_LISTE_PERSONNES,
    ID_LISTE_PARTICIPANTS};

  CadreModifierRdv = new cadre("Modifier un rendez-vous");
  CadreModifierRdv -> Show(true);
  auto panneau = new wxPanel{CadreModifierRdv, wxID_ANY};

  c_choix_rdv = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,listeRDV, ID_CHOIX);
  c_choix_libelle = new wxStaticText{panneau, wxID_STATIC,("Libelle")};
  auto jour = new wxStaticText{panneau, wxID_STATIC,("Jour")};
  auto mois = new wxStaticText{panneau, wxID_STATIC,("Mois")};
  auto annee = new wxStaticText{panneau, wxID_STATIC,("Annee")};
  auto heureDebut = new wxStaticText{panneau, wxID_STATIC,("Heure de debut")};
  auto heureFin = new wxStaticText{panneau, wxID_STATIC,("Heure de fin")};

  c_jour = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_mois = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_annee = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureDebut = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureFin = new wxTextCtrl(panneau, wxID_STATIC,"");
  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto boutonAjouter = new wxButton(panneau, ID_BOUTON_AJOUTER, ">");
  auto boutonRetirer = new wxButton(panneau, ID_BOUTON_RETIRER, "<");

  //initialisation de la liste avec toutes les personnes
  c_ajoutParticipants.Empty();
  chainonPersonne* crtp = repertoirePersonne->getTete();
  while(crtp)
  {
    wxString nom = repertoirePersonne->getNom(crtp);
    wxString prenom = repertoirePersonne->getPrenom(crtp);
    c_ajoutParticipants.Add(nom + " " + prenom);
    crtp = repertoirePersonne->getSuivant(crtp);
  }

  c_listePersonnes = new wxListBox(panneau, ID_LISTE_PERSONNES, wxDefaultPosition, {150, 200}, c_ajoutParticipants, 0, wxDefaultValidator, wxListBoxNameStr);
  c_listeParticipants = new wxListBox(panneau, ID_LISTE_PARTICIPANTS, wxDefaultPosition, {150, 200}, 0, nullptr, 0, wxDefaultValidator, wxListBoxNameStr);

  auto sizer1 = new wxBoxSizer{wxHORIZONTAL};
  sizer1->Add(jour,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer1->AddStretchSpacer(1);
  sizer1->Add(c_jour,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer2 = new wxBoxSizer{wxHORIZONTAL};
  sizer2->Add(mois,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer2->AddStretchSpacer(1);
  sizer2->Add(c_mois,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer3 = new wxBoxSizer{wxHORIZONTAL};
  sizer3->Add(annee,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer3->AddStretchSpacer(1);
  sizer3->Add(c_annee,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer4 = new wxBoxSizer{wxHORIZONTAL};
  sizer4->Add(heureDebut,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer4->AddStretchSpacer(1);
  sizer4->Add(c_heureDebut,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer5 = new wxBoxSizer{wxHORIZONTAL};
  sizer5->Add(heureFin,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer5->AddStretchSpacer(1);
  sizer5->Add(c_heureFin,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer6 = new wxBoxSizer{wxVERTICAL};
  sizer6->Add(boutonAjouter, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);
  sizer6->Add(boutonRetirer, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer7 = new wxBoxSizer{wxHORIZONTAL};
  sizer7->Add(c_listePersonnes, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer7->Add(sizer6, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer7->Add(c_listeParticipants, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);

  auto sizer8 = new wxBoxSizer{wxVERTICAL};
  sizer8->Add(c_choix_rdv,0,wxALIGN_CENTER | wxALL, 10);
  sizer8->Add(c_choix_libelle,1,wxALIGN_CENTER | wxALL, 10);
  sizer8->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer5,1,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(sizer7,0,wxALIGN_LEFT | wxALL, 10);
  sizer8->Add(bouton,1,wxALIGN_CENTER | wxALL, 10);

  panneau->SetSizerAndFit(sizer8);
  CadreModifierRdv->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  c_choix_rdv->Bind(wxEVT_CHOICE, &cadre::OnSelectionModifierRdv, this);
  bouton->Bind(wxEVT_BUTTON, &cadre::OnValiderModifierRdv, this);
  boutonAjouter->Bind(wxEVT_BUTTON, &cadre::OnAjoutListeParticipants, this);
  boutonRetirer->Bind(wxEVT_BUTTON, &cadre::OnRetirerListeParticipants, this);

}

/**
  Met a jour l'affichage des informations lorsque le rendez-vous a modifier est choisi
  @param[in] e - un evenement declanché par la méthode "cadre::OnModiferRdv"

*/
void cadre::OnSelectionModifierRdv(wxCommandEvent& e){

  int index;
  int i = 0;
  index = c_choix_rdv->GetSelection();
  chainonRdv* crt = repertoireRdv->getTete();

  while(i != index){
    crt = repertoireRdv->getSuivant(crt);
    i++;
  }

  c_choix_libelle->SetLabel(repertoireRdv->getLibelle(crt));
  c_jour->SetValue(wxString::Format(wxT("%i"),repertoireRdv->getJour(crt)));
  c_mois->SetValue(wxString::Format(wxT("%i"),repertoireRdv->getMois(crt)));
  c_annee->SetValue(wxString::Format(wxT("%i"),repertoireRdv->getAnnee(crt)));
  c_heureDebut->SetValue(wxString::Format(wxT("%i"),repertoireRdv->getHeureDebut(crt)));
  c_heureFin->SetValue(wxString::Format(wxT("%i"),repertoireRdv->getHeureFin(crt)));

  while(c_listeParticipants->GetCount() >= 1)
  {
    c_listeParticipants->Delete(0);
  }

  c_listeBoxParticipants.Empty();

  vector<vector<string>> liste = repertoireRdv->getParticipants(crt);
  for(unsigned j=0; j<liste.size(); j++)
  {
    wxString nom = liste[j][0];
    wxString prenom = liste[j][1];
    c_listeBoxParticipants.Add(nom + " " + prenom);
    c_listeParticipants->InsertItems(1, &c_listeBoxParticipants[j], 0);
  }
}


/**
  Réalise les modifications demandées par l'utilisateur
  @param[in] e - un evenement declanché par la méthode "cadre::OnModiferRdv"
*/
void cadre::OnValiderModifierRdv(wxCommandEvent& e){

if(c_choix_rdv->GetSelection() == wxNOT_FOUND){
  CadreModifierRdv->Close(true);
  return;
}

wxArrayString liste;
int nb = c_listeParticipants->GetCount();

for(int i=0; i<nb; i++)
  liste.Add(c_listeParticipants->GetString(i));
liste.Sort();

vector<vector<string>>listeVector(nb, vector<string>(2, ""));
for(int i=0; i<nb; i++)
{
  string tmp, nom, prenom;
  tmp = string(liste[i]);
  stringstream ss(tmp);
  getline(ss, nom, ' ');
  getline(ss, prenom, ' ');

  listeVector[i][0]=nom;
  listeVector[i][1]=prenom;
}

int index;
string libelle;
index = c_choix_rdv->GetSelection();
libelle = c_choix_rdv->GetString(index);

int jour = wxAtoi(c_jour->GetValue());
int mois = wxAtoi(c_mois->GetValue());
int annee = wxAtoi(c_annee->GetValue());
int heureDebut = wxAtoi(c_heureDebut->GetValue());
int heureFin = wxAtoi(c_heureFin->GetValue());

//on vérifie si tous les participants de la liste sont libres
bool conditionParticipants = true;
unsigned i = 0;
while( (conditionParticipants==true) & (i<listeVector.size()) )
{
  conditionParticipants = repertoireRdv->estLibre(listeVector[i][0], listeVector[i][1], jour, mois, annee, heureDebut, jour, mois, annee, heureFin);
  ++i;
}

if( (jour>=32) | (jour<=0) )
  wxMessageBox("Le jour choisi est invalide");
else if( (mois>=13) | (mois<=0) )
  wxMessageBox("Le mois choisi est invalide");
else if( annee==0 )
  wxMessageBox("L'annee choisie est invalide");
else if( (heureDebut>=24) | (heureDebut<=0) )
  wxMessageBox("L'heure de commencement choisie est invalide");
else if( (heureFin>=24) | (heureFin<=0) )
  wxMessageBox("L'heure de fin choisie est invalide");
else if(!conditionParticipants)
{
  wxString txt = listeVector[i-1][0] + " " + listeVector[i-1][1];
  txt.Printf(wxT("%s a deja un rendez-vous"), txt);
  wxMessageBox(txt);
}
else
{
  repertoireRdv->modifierDate(libelle, jour, mois, annee);
  repertoireRdv->modifierHeure(libelle, heureDebut, heureFin);
  repertoireRdv->modifierListePersonnes(libelle, listeVector);
}

CadreModifierRdv->Close(true);
}

/**
  Affiche la liste de rendez-vous d'une personne choisie par l'utilisateur
  @param[in] e - un evenement declanché par le menu "Afficher -> Rendez-vous de..."
*/
void cadre::OnRdvDe(wxCommandEvent& e){

  enum{ID_CHOIX};

  wxArrayString repertoire;
  CadreRdvDe = new cadre("Afficher rendez-vous de");
  CadreRdvDe -> Show(true);
  auto panneau = new wxPanel{CadreRdvDe, wxID_ANY};
  chainonPersonne* crt = repertoirePersonne->getTete();

  while(crt){
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }
  c_choix_personne = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);

  txt = new wxStaticText{panneau,wxID_STATIC,""};
  auto sizer = new wxBoxSizer{wxVERTICAL};

  sizer->Add(c_choix_personne,1,wxALIGN_CENTER | wxALL, 10);
  sizer->Add(txt,1,wxALIGN_CENTER | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  CadreRdvDe->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  c_choix_personne->Bind(wxEVT_CHOICE, &cadre::OnSelectionRdvDe, this);

}

/**Met a jour l'affichage de la liste de rendez-vous
  @param[in] e - un evenement declanché par la méthode "cadre::OnRdvDe"
*/
void cadre::OnSelectionRdvDe(wxCommandEvent& e){

  wxString t;
  int sel = c_choix_personne->GetSelection();
  chainonPersonne* crt_p = repertoirePersonne->getTete();
  int i = 0;
  while(i != sel){
    crt_p = repertoirePersonne->getSuivant(crt_p);
    i++;
  }

  string nom = repertoirePersonne->getNom(crt_p);
  string prenom = repertoirePersonne->getPrenom(crt_p);

  chainonRdv* crt_r = repertoireRdv->getTete();
  while(crt_r){
    vector<vector<string>> rep = repertoireRdv->getParticipants(crt_r);
    for(unsigned i = 0; i < rep.size(); i++){
      if((rep[i][0]==nom) && (rep[i][1]==prenom)){
        t += repertoireRdv->getLibelle(crt_r);
        t += wxString::FromUTF8("\xC2\xA0 le \xC2\xA0");
        t += wxString::Format(wxT("%i"),repertoireRdv->getJour(crt_r));
        t += wxString::FromUTF8("/");
        t += wxString::Format(wxT("%i"),repertoireRdv->getMois(crt_r));
        t += wxString::FromUTF8("/");
        t += wxString::Format(wxT("%i"),repertoireRdv->getAnnee(crt_r));
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::FromUTF8("de");
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::Format(wxT("%i"),repertoireRdv->getHeureDebut(crt_r));
        t += wxString::FromUTF8("h");
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::FromUTF8("a");
        t += wxString::Format(wxT("%i"),repertoireRdv->getHeureFin(crt_r));
        t += wxString::FromUTF8("h");
        t += wxString::FromUTF8("\n");
      }
    }
    crt_r = repertoireRdv->getSuivant(crt_r);
  }
  txt->SetLabel(t);
}

void cadre::OnSupprimerRdv(wxCommandEvent& e){

  enum{ID_CHOIX,ID_BOUTON};

  wxArrayString listeRDV;

  chainonRdv* crt = repertoireRdv->getTete();
  while(crt){
    listeRDV.Add(repertoireRdv->getLibelle(crt));
    crt = repertoireRdv->getSuivant(crt);
  }

  CadreSupprimerRdv = new cadre("Supprimer rendez-vous");
  CadreSupprimerRdv -> Show(true);
  auto panneau = new wxPanel{CadreSupprimerRdv, wxID_ANY};

  c_choix_rdv = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,listeRDV, ID_CHOIX);
  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto sizer = new wxBoxSizer{wxVERTICAL};

  sizer->Add(c_choix_rdv,1,wxALIGN_CENTER | wxALL, 10);
  sizer->Add(bouton,1,wxALIGN_CENTER | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  CadreSupprimerRdv->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnValiderSupprimerRdv, this);
}

void cadre::OnValiderSupprimerRdv(wxCommandEvent& e){

  if(c_choix_rdv->GetSelection() == wxNOT_FOUND){
    CadreModifierRdv->Close(true);
    return;
  }
  int index;
  string libelle;
  index = c_choix_rdv->GetSelection();
  libelle = c_choix_rdv->GetString(index);
  repertoireRdv->supprimer(libelle);
  CadreSupprimerRdv->Close(true);
}


void cadre::OnDetailsPersonne(wxCommandEvent& e){

  enum{ID_CHOIX};

  wxArrayString repertoire;

  chainonPersonne* crt = repertoirePersonne->getTete();

  while(crt){
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }

  CadreDetailsPersonne = new cadre("Afficher details de");
  CadreDetailsPersonne -> Show(true);
  auto panneau = new wxPanel{CadreDetailsPersonne, wxID_ANY};
  c_choix_personne = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);
  txt = new wxStaticText{panneau,wxID_STATIC,""};
  auto sizer = new wxBoxSizer{wxVERTICAL};

  sizer->Add(c_choix_personne,1,wxALIGN_CENTER | wxALL, 10);
  sizer->Add(txt,1,wxALIGN_CENTER | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  CadreDetailsPersonne->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  c_choix_personne->Bind(wxEVT_CHOICE, &cadre::OnSelectionDetailsPersonne, this);
}

void cadre::OnSelectionDetailsPersonne(wxCommandEvent& e){

  wxString t;
  int sel = c_choix_personne->GetSelection();
  chainonPersonne* crt_p = repertoirePersonne->getTete();
  int i = 0;
  while(i != sel){
    crt_p = repertoirePersonne->getSuivant(crt_p);
    i++;
  }

  string nom = repertoirePersonne->getNom(crt_p);
  string prenom = repertoirePersonne->getPrenom(crt_p);

  t += nom;
  t += wxString::FromUTF8("\xC2\xA0 \xC2\xA0");
  t += prenom;
  t += wxString::FromUTF8("\n");
  t += repertoirePersonne->getNumero(crt_p);
  t += wxString::FromUTF8("\n");
  t += repertoirePersonne->getEmail(crt_p);
  t += wxString::FromUTF8("\n");

  chainonRdv* crt_r = repertoireRdv->getTete();
  while(crt_r){
    vector<vector<string>> rep = repertoireRdv->getParticipants(crt_r);
    for(unsigned i = 0; i < rep.size(); i++){
      if((rep[i][0]==nom) && (rep[i][1]==prenom)){
        t += repertoireRdv->getLibelle(crt_r);
        t += wxString::FromUTF8("\xC2\xA0 le \xC2\xA0");
        t += wxString::Format(wxT("%i"),repertoireRdv->getJour(crt_r));
        t += wxString::FromUTF8("/");
        t += wxString::Format(wxT("%i"),repertoireRdv->getMois(crt_r));
        t += wxString::FromUTF8("/");
        t += wxString::Format(wxT("%i"),repertoireRdv->getAnnee(crt_r));
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::FromUTF8("de");
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::Format(wxT("%i"),repertoireRdv->getHeureDebut(crt_r));
        t += wxString::FromUTF8("h");
        t += wxString::FromUTF8("\xC2\xA0");
        t += wxString::FromUTF8("a");
        t += wxString::Format(wxT("%i"),repertoireRdv->getHeureFin(crt_r));
        t += wxString::FromUTF8("h");
        t += wxString::FromUTF8("\n");
      }
    }
    crt_r = repertoireRdv->getSuivant(crt_r);
  }
  txt->SetLabel(t);
}

void cadre::OnPersonneEstLibre(wxCommandEvent& e){

  enum{ID_CHOIX,ID_BOUTON};

  wxArrayString repertoire;

  chainonPersonne* crt = repertoirePersonne->getTete();

  while(crt){
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }

  CadrePersonneEstLibre = new cadre("Afficher details de");
  CadrePersonneEstLibre -> Show(true);
  auto panneau = new wxPanel{CadrePersonneEstLibre, wxID_ANY};
  c_choix_personne = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);
  txt = new wxStaticText{panneau,wxID_STATIC,""};

  auto heureD = new wxStaticText{panneau, wxID_STATIC,("Heure de debut")};
  auto heureF = new wxStaticText{panneau, wxID_STATIC,("Heure de fin")};
  auto jourD = new wxStaticText{panneau, wxID_STATIC,("Jour debut")};
  auto jourF = new wxStaticText{panneau, wxID_STATIC,("Jour fin")};
  auto moisD = new wxStaticText{panneau, wxID_STATIC,("Mois debut")};
  auto moisF = new wxStaticText{panneau, wxID_STATIC,("Mois fin")};
  auto anneeD = new wxStaticText{panneau, wxID_STATIC,("annee debut")};
  auto anneeF = new wxStaticText{panneau, wxID_STATIC,("annee fin")};

  c_jourD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_jourF = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_moisD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_moisF = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_anneeD = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_anneeF = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureDebut = new wxTextCtrl(panneau, wxID_STATIC,"");
  c_heureFin = new wxTextCtrl(panneau, wxID_STATIC,"");

  auto bouton = new wxButton(panneau, ID_BOUTON, "Valider");

  auto sizer1 = new wxBoxSizer{wxHORIZONTAL};
  sizer1->Add(jourD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer1->AddStretchSpacer(1);
  sizer1->Add(c_jourD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer2 = new wxBoxSizer{wxHORIZONTAL};
  sizer2->Add(jourF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer2->AddStretchSpacer(1);
  sizer2->Add(c_jourF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer3 = new wxBoxSizer{wxHORIZONTAL};
  sizer3->Add(moisD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer3->AddStretchSpacer(1);
  sizer3->Add(c_moisD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer4 = new wxBoxSizer{wxHORIZONTAL};
  sizer4->Add(moisF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer4->AddStretchSpacer(1);
  sizer4->Add(c_moisF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer5 = new wxBoxSizer{wxHORIZONTAL};
  sizer5->Add(anneeD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer5->AddStretchSpacer(1);
  sizer5->Add(c_anneeD,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer6 = new wxBoxSizer{wxHORIZONTAL};
  sizer6->Add(anneeF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer6->AddStretchSpacer(1);
  sizer6->Add(c_anneeF,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer7 = new wxBoxSizer{wxHORIZONTAL};
  sizer7->Add(heureD,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer7->AddStretchSpacer(1);
  sizer7->Add(c_heureDebut,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer8 = new wxBoxSizer{wxHORIZONTAL};
  sizer8->Add(heureF,1,wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 10);
  sizer8->AddStretchSpacer(1);
  sizer8->Add(c_heureFin,1,wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALIGN_RIGHT | wxALL, 10);

  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(c_choix_personne,1,wxALIGN_CENTER | wxALL, 10);
  sizer->Add(sizer7,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer5,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer8,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer6,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(bouton,0,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(txt,0,wxALIGN_LEFT | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  CadrePersonneEstLibre->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnSelectionPersonneEstLibre, this);
}

void cadre::OnSelectionPersonneEstLibre(wxCommandEvent& e){

  bool Estlibre;

  wxString t;
  int sel = c_choix_personne->GetSelection();
  chainonPersonne* crt_p = repertoirePersonne->getTete();
  int i = 0;
  while(i != sel){
    crt_p = repertoirePersonne->getSuivant(crt_p);
    i++;
  }

  string nom = repertoirePersonne->getNom(crt_p);
  string prenom = repertoirePersonne->getPrenom(crt_p);

  Estlibre = repertoireRdv->estLibre(nom,prenom,wxAtoi(c_jourD->GetLabel()),wxAtoi(c_moisD->GetLabel()),wxAtoi(c_anneeD->GetLabel()),wxAtoi(c_heureDebut->GetLabel()),wxAtoi(c_jourF->GetLabel()),wxAtoi(c_moisF->GetLabel()),wxAtoi(c_anneeF->GetLabel()),wxAtoi(c_heureFin->GetLabel()));

  if(Estlibre)
    txt->SetLabel("Cette personne est libre");
  else
    txt->SetLabel("Cette personne n'est pas libre");

void cadre::OnDetailRdv(wxCommandEvent& e)
{
  enum{ID_CHOIX};

  wxArrayString repertoire;
  CadreDetailRdv = new cadre("Afficher detail rendez-vous");
  CadreDetailRdv -> Show(true);
  auto panneau = new wxPanel{CadreDetailRdv, wxID_ANY};
  chainonRdv* crt = repertoireRdv->getTete();

  while(crt){
    repertoire.Add( repertoireRdv->getLibelle(crt) );
    crt = repertoireRdv->getSuivant(crt);
  }
  c_choix_rdv = new wxChoice(panneau,1,wxDefaultPosition,wxDefaultSize,repertoire, ID_CHOIX);

  txt = new wxStaticText{panneau,wxID_STATIC,""};
  auto sizer = new wxBoxSizer{wxVERTICAL};

  sizer->Add(c_choix_rdv,1,wxALIGN_CENTER | wxALL, 10);
  sizer->Add(txt,1,wxALIGN_CENTER | wxALL, 10);

  panneau->SetSizerAndFit(sizer);
  CadreDetailRdv->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  c_choix_rdv->Bind(wxEVT_CHOICE, &cadre::OnSelectionDetailRdv, this);

}

void cadre::OnSelectionDetailRdv(wxCommandEvent& e)
{
  wxString t;
  int sel = c_choix_rdv->GetSelection();
  chainonRdv* crt_r = repertoireRdv->getTete();
  int i = 0;
  while(i != sel){
    crt_r = repertoireRdv->getSuivant(crt_r);
    i++;
  }

  t += repertoireRdv->getLibelle(crt_r);
  t += wxString::FromUTF8("\xC2\xA0 le \xC2\xA0");
  t += wxString::Format(wxT("%i"),repertoireRdv->getJour(crt_r));
  t += wxString::FromUTF8("/");
  t += wxString::Format(wxT("%i"),repertoireRdv->getMois(crt_r));
  t += wxString::FromUTF8("/");
  t += wxString::Format(wxT("%i"),repertoireRdv->getAnnee(crt_r));
  t += wxString::FromUTF8("\xC2\xA0");
  t += wxString::FromUTF8("de");
  t += wxString::FromUTF8("\xC2\xA0");
  t += wxString::Format(wxT("%i"),repertoireRdv->getHeureDebut(crt_r));
  t += wxString::FromUTF8("h");
  t += wxString::FromUTF8("\xC2\xA0");
  t += wxString::FromUTF8("a");
  t += wxString::Format(wxT("%i"),repertoireRdv->getHeureFin(crt_r));
  t += wxString::FromUTF8("h");
  t += wxString::FromUTF8("\nParticipants :\n");

  vector<vector<string>> rep = repertoireRdv->getParticipants(crt_r);

  for(unsigned j=0; j<rep.size(); j++)
  {
    chainonPersonne* crt_p = repertoirePersonne->getTete();
    while(crt_p)
    {
      string nom = repertoirePersonne->getNom(crt_p);
      string prenom = repertoirePersonne->getPrenom(crt_p);
      if( (rep[j][0]==nom) & (rep[j][1]==prenom) )
      {
        t += nom + " " + prenom + " ; " + repertoirePersonne->getNumero(crt_p) + " ; " + repertoirePersonne->getEmail(crt_p) + "\n";
      }

      crt_p = repertoirePersonne->getSuivant(crt_p);
    }
  }

  txt->SetLabel(t);
}

void cadre::OnDocumentation(wxCommandEvent& e)
{
  wxString url = wxGetCwd();
  url += "/html/annotated.html";
  wxLaunchDefaultBrowser(url, 0);
}

void cadre::OnAbout(wxCommandEvent& e)
{
  auto CadreAbout = new cadre("LA propos");
  CadreAbout -> Show(true);
  auto panneau = new wxPanel{CadreAbout, wxID_ANY};

  wxString t;
  t += "Ce programme a ete realise dans le cadre du projet de structures de donnees de deuxieme annee de licence informatique.\n\n";
  t += "Les professeurs referents :\n- CORDIER Frederic\n- MAILLOT Yvan\n\n";
  t += "Les eleves createurs du projet :\n- AGUDO-PEREZ Olivier\n- GHERARDI Sylvain\n- HUOT Gael\n- CHOLE Nicolas\n";

  auto txt = new wxStaticText{panneau,wxID_STATIC,t};
  auto sizer = new wxBoxSizer{wxVERTICAL};

  sizer->Add(txt,1, wxEXPAND | wxALL,10);
  panneau->SetSizerAndFit(sizer);

  CadreAbout->SetSize(panneau->GetSize());
  CadreAbout->SetMinSize({300,50});
}
