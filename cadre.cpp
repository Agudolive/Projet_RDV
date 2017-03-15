#include "cadre.h"

#include "lcpersonne.h"
#include "lcrdv.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum
{
  ID_LOAD, ID_NEW_PERSONNE, ID_EDIT_PERSONNE, ID_DELETE_PERSONNE,
  ID_NEW_RDV, ID_EDIT_RDV, ID_DELETE_RDV, ID_DOC, ID_A_PROPOS,
  ID_LISTE_PERSONNES, ID_LISTE_RDV, ID_RDV_DE, ID_RDV_ENTRE,
  ID_DETAIL_RDV, ID_DETAIL_PERSONNE, ID_POPUP
};

cadre::cadre() : wxFrame{nullptr, wxID_ANY, "Carnet de rendez-vous", wxDefaultPosition}
{
  //initialisation des repertoires
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  //création de la fenête vide
  SetClientSize(wxSize{960,540});

  //création d'un panneau
  auto panneau = new wxPanel{this, wxID_ANY};
  panneau->SetSize(GetClientSize());

  //création des menus
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

  //création de la barre de menus
  auto menubar = new wxMenuBar;
  menubar -> Append(menufichier, "Fichier");
  menubar -> Append(menuediter, "Editer");
  menubar -> Append(menuafficher, "Afficher");
  menubar -> Append(menuaide, "Aide");
  SetMenuBar(menubar);

  //liaisons
  Bind(wxEVT_MENU, &cadre::OnCharger, this, ID_LOAD);
  Bind(wxEVT_MENU, &cadre::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &cadre::OnExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &cadre::OnAfficherPersonnes, this, ID_LISTE_PERSONNES);

}

void cadre::OnCharger(wxCommandEvent& e)
{
  //provisoire, sera remplacé par l'import json
  cout << repertoirePersonne->getTete() << endl;

  repertoirePersonne->ajouter("Lefebvre","Kyllian", "06.92.38.77.78", "kyllianlefebvre@fakeemail.tld");
  repertoirePersonne->ajouter("Texier","Lilian", "06.88.19.80.00", "liliantexier@fakeemail.tld");
  repertoirePersonne->ajouter("Evrard","Juliette", "06.67.34.92.88", "julietteevrard@fakeemail.tld");
  repertoirePersonne->ajouter("Grenier","Juliette", "06.34.10.68.70", "clemencegrenier@fakeemail.tld");
  repertoirePersonne->ajouter("Simon","Mathieu", "06.33.15.83.95", "mathieusimon@fakeemail.tld");
  repertoirePersonne->ajouter("Ruiz","Clément", "06.79.66.76.53", "clementmathieu@fakeemail.tld");
  repertoirePersonne->ajouter("Ruiz","Florentin", "06.08.32.08.45", "florentinrichard@fakeemail.tld");
  repertoirePersonne->ajouter("Ruiz","Théo", "06.36.60.14.14", "theoruiz@fakeemail.tld");
  repertoirePersonne->ajouter("Ferre","Mathis", "06.52.35.59.69", "mathisferre@fakeemail.tld");
  repertoirePersonne->ajouter("Dumas","Quentin", "06.71.23.98.10", "quentindumas@fakeemail.tld");

  vector<vector<string>> p1;
  p1.resize(2, vector<string>(2));
  p1[0][0]="Lefebvre";
  p1[0][1]="Kyllian";
  p1[1][0]="Ruiz";
  p1[1][1]="Clément";

  vector<vector<string>> p2;
  p2.resize(3, vector<string>(2));
  p2[0][0]="Ruiz";
  p2[0][1]="Clément";
  p2[1][0]="Ruiz";
  p2[1][1]="Florentin";
  p2[2][0]="Dumas";
  p2[2][1]="Quentin";


  repertoireRdv->ajouter("rdv1", 28, 1, 2016, 15, 16, p1);
  repertoireRdv->ajouter("rdv2", 2, 3, 2017, 11, 12, p2);

}

void cadre::OnSave(wxCommandEvent& e)
{
  //appel de la sauvegarde json
}

void cadre::OnExit(wxCommandEvent& e)
{
  Close();
}

void cadre::OnAfficherPersonnes(wxCommandEvent& e)
{
  auto f = new wxFrame{nullptr, ID_POPUP, "Liste personnes", wxDefaultPosition, wxSize{640, 360}};
  f -> Show(true);
  chainonPersonne* crt = repertoirePersonne->getTete();
  auto sizer = new wxBoxSizer{wxVERTICAL};
  while(crt){
    wxString t;
    t += repertoirePersonne->getNom(crt);
    t += "\n";
    auto txt = new wxStaticText{f, wxID_STATIC, t};
    sizer->Add(txt,0,wxALIGN_LEFT | wxALL,10);
    crt = repertoirePersonne->getSuivant(crt);
  }
}
