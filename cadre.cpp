#include "cadre.h"

#include "lcpersonne.h"
#include "lcrdv.h"
#include "fromJson.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

cadre::cadre() : wxFrame{nullptr, wxID_ANY, "NomFrame", wxDefaultPosition}
{

}

cadre::cadre(string& c_nomFrame) : wxFrame{nullptr, wxID_ANY, c_nomFrame, wxDefaultPosition}
{

}

void cadre::OnCadrePrincipal(){

  enum
  {
    ID_LOAD, ID_NEW_PERSONNE, ID_EDIT_PERSONNE, ID_DELETE_PERSONNE,
    ID_NEW_RDV, ID_EDIT_RDV, ID_DELETE_RDV, ID_DOC, ID_A_PROPOS,
    ID_LISTE_PERSONNES, ID_LISTE_RDV, ID_RDV_DE, ID_RDV_ENTRE,
    ID_DETAIL_RDV, ID_DETAIL_PERSONNE
  };

  auto  CadreMenuPrincipal = new cadre{"Menu Principal"};

  //initialisation des repertoires
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  //creation de la fenête vide
  SetClientSize(wxSize{960,540});

  //creation d'un panneau
  auto panneau = new wxPanel{CadreMenuPrincipal, wxID_ANY};
  panneau->SetSize(GetClientSize());

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

  //liaisons
  Bind(wxEVT_MENU, &cadre::OnCharger, CadreMenuPrincipal, ID_LOAD);
  Bind(wxEVT_MENU, &cadre::OnSave, CadreMenuPrincipal, wxID_SAVE);
  Bind(wxEVT_MENU, &cadre::OnExit, CadreMenuPrincipal, wxID_EXIT);
  Bind(wxEVT_MENU, &cadre::OnAfficherPersonnes, CadreMenuPrincipal, ID_LISTE_PERSONNES);
  Bind(wxEVT_MENU, &cadre::OnAjouterPersonne, CadreMenuPrincipal, ID_NEW_PERSONNE);

}

void cadre::OnCharger(wxCommandEvent& e)
{
  delete repertoirePersonne;
  delete repertoireRdv;

  //appel lors du chargement json
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  fromJson json_load = fromJson{repertoirePersonne, repertoireRdv};


  json_load.getRepertoire();
  json_load.getRdv();
}

void cadre::OnSave(wxCommandEvent& e)
{
  //appel de la sauvegarde json
  fromJson json_save = fromJson{repertoirePersonne, repertoireRdv};

  json_save.saveRepertoire();
  json_save.saveRdv();
}

void cadre::OnExit(wxCommandEvent& e)
{
  Close();
}

void cadre::OnAfficherPersonnes(wxCommandEvent& e)
{
  auto f = new wxFrame{nullptr, ID_POPUP, "Liste des contacts", wxDefaultPosition};
  f -> Show(true);
  auto panneau = new wxPanel{f, wxID_ANY};

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
  f->SetSize(panneau->GetSize());
  f->SetMinSize({300,50});
}

void cadre::OnAjouterPersonne(wxCommandEvent& e){

  enum{
    ID_BOUTON_AJOUTER_PERSONNE, ID_CHAMP1_AJOUTER_PERSONNE, ID_CHAMP2_AJOUTER_PERSONNE, ID_CHAMP3_AJOUTER_PERSONNE,
    ID_CHAMP4_AJOUTER_PERSONNE
  };

  auto  CadreAjouterPersonne = new cadre{"Ajouter une personne"};


  CadreAjouterPersonne -> Show(true);
  auto panneau = new wxPanel{f, wxID_ANY};
  // panneau->SetSize({6000,3000});

  auto txt1 = new wxStaticText{panneau, wxID_STATIC,("Nom : ")};
  auto txt2 = new wxStaticText{panneau, wxID_STATIC,("Prenom : ")};
  auto txt3 = new wxStaticText{panneau, wxID_STATIC,("Numero : ")};
  auto txt4 = new wxStaticText{panneau, wxID_STATIC,("Email : ")};

  c_champNom = new wxTextCtrl(panneau, ID_CHAMP1_AJOUTER_PERSONNE,"");
  c_champPrenom = new wxTextCtrl(panneau, ID_CHAMP2_AJOUTER_PERSONNE,"");
  c_champNumero = new wxTextCtrl(panneau, ID_CHAMP3_AJOUTER_PERSONNE,"");
  c_champEmail = new wxTextCtrl(panneau, ID_CHAMP4_AJOUTER_PERSONNE,"");

  auto bouton = new wxButton(panneau, ID_BOUTON_AJOUTER_PERSONNE, "Valider");

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
  f->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  Bind(wxEVT_BUTTON, &cadre::OnBoutonAjouterPersonne, CadreAjouterPersonne, ID_BOUTON_AJOUTER_PERSONNE);
}

void cadre::OnBoutonAjouterPersonne(wxCommandEvent& e){

  cout << "test" << endl;
  repertoirePersonne->ajouter(std::string(c_champNom->GetValue()), std::string(c_champPrenom->GetValue()), std::string(c_champNumero->GetValue()), std::string(c_champEmail->GetValue()));

}
