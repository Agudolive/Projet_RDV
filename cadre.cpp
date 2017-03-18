#include "cadre.h"

#include "lcpersonne.h"
#include "lcrdv.h"
#include "fromJson.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

cadre::cadre() : wxFrame{nullptr, wxID_ANY, "Gestion de rendez-vous", wxDefaultPosition}
{
  enum
  {
    ID_LOAD, ID_NEW_PERSONNE, ID_EDIT_PERSONNE, ID_DELETE_PERSONNE,
    ID_NEW_RDV, ID_EDIT_RDV, ID_DELETE_RDV, ID_DOC, ID_A_PROPOS,
    ID_LISTE_PERSONNES, ID_LISTE_RDV, ID_RDV_DE, ID_RDV_ENTRE,
    ID_DETAIL_RDV, ID_DETAIL_PERSONNE
  };

  // auto  CadreMenuPrithisncipal = new cadre("Menu Principal");

  //initialisation des repertoires
  repertoirePersonne = new LCPersonne{};
  repertoireRdv = new LCRdv{};

  //creation de la fenête vide
  SetClientSize(wxSize{960,540});
  auto panneau = new wxPanel{this, wxID_ANY};
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
  Bind(wxEVT_MENU, &cadre::OnCharger, this, ID_LOAD);
  Bind(wxEVT_MENU, &cadre::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &cadre::OnExit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &cadre::OnAfficherPersonnes, this, ID_LISTE_PERSONNES);
  Bind(wxEVT_MENU, &cadre::OnAfficherRdvs, this, ID_LISTE_RDV);
  Bind(wxEVT_MENU, &cadre::OnAjouterPersonne, this, ID_NEW_PERSONNE);
  Bind(wxEVT_MENU, &cadre::OnAjouterRdv, this, ID_NEW_RDV);
  Bind(wxEVT_MENU, &cadre::OnAfficherEntreDates, this, ID_RDV_ENTRE);
}

cadre::cadre(string c_nomFrame) : wxFrame{nullptr, wxID_ANY, c_nomFrame, wxDefaultPosition}{

}

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

void cadre::OnAjouterPersonne(wxCommandEvent& e){

  enum{
    ID_BOUTON_AJOUTER_PERSONNE
  };

  auto CadreAjouterPersonne = new cadre{"Ajouter une personne"};
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
  CadreAjouterPersonne->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnBoutonAjouterPersonne, this);
}

void cadre::OnBoutonAjouterPersonne(wxCommandEvent& e){

  repertoirePersonne->ajouter(std::string(c_champNom->GetValue()), std::string(c_champPrenom->GetValue()), std::string(c_champNumero->GetValue()), std::string(c_champEmail->GetValue()));

}



void cadre::OnAjouterRdv(wxCommandEvent& e)
{
  enum{
    ID_BOUTON_AJOUTER_RDV, ID_LISTE_PERSONNES
  };

  auto CadreAjouterRdv = new cadre{"Ajouter un rendez-vous"};
  CadreAjouterRdv -> Show(true);
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

  auto bouton = new wxButton(panneau, ID_BOUTON_AJOUTER_RDV, "Ajouter");

  wxArrayString repertoire;
  chainonPersonne* crt = repertoirePersonne->getTete();
  while(crt)
  {
    repertoire.Add(repertoirePersonne->getNom(crt) + " " + repertoirePersonne->getPrenom(crt));
    crt = repertoirePersonne->getSuivant(crt);
  }
  auto liste = new wxListBox(panneau, ID_LISTE_PERSONNES, wxDefaultPosition, wxDefaultSize, &repertoire, 0, wxDefaultValidator, wxListBoxNameStr);



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



  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(sizer1,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer2,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer3,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer4,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer5,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(sizer6,1,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(bouton,0,wxALIGN_LEFT | wxALL, 10);
  sizer->Add(liste,1,wxALIGN_LEFT | wxALL, 10);


  panneau->SetSizerAndFit(sizer);
  CadreAjouterRdv->SetSize(panneau->GetSize());
  SetMinSize(GetSize());

  bouton->Bind(wxEVT_BUTTON, &cadre::OnBoutonAjouterRdv, this);

}

void cadre::OnBoutonAjouterRdv(wxCommandEvent& e)
{
  vector<vector<string>>test(0);
  repertoireRdv->ajouter(std::string(c_libelle->GetValue()), wxAtoi(c_jour->GetValue()), wxAtoi(c_mois->GetValue()), wxAtoi(c_annee->GetValue()), wxAtoi(c_heureDebut->GetValue()), wxAtoi(c_heureFin->GetValue()), test);
}



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
}
