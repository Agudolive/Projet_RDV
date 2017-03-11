#include "lcrdv.h"
#include "lcpersonne.h"
#include <string>
#include <iostream>
using namespace std;

LCRdv::LCRdv():l_tete{nullptr}
{
}

LCRdv::~LCRdv()
{
  //appel du destructeur de chaque chainonRdv contenu dans la liste
  chainonRdv* suivant = l_tete;

  while(suivant != nullptr)
  {
    suivant = l_tete->cr_suivant;
    l_tete->~chainonRdv();
    l_tete = suivant;
  }
}

void LCRdv::ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<vector<string>> participants)
{
  chainonRdv* nouveauChainon = new chainonRdv(libelle, jour, mois, annee, heureDebut, heureFin, participants);
  chainonRdv* precedent = trier(libelle);

  if(precedent == nullptr)
  {
    nouveauChainon->cr_suivant = l_tete;
    l_tete = nouveauChainon;
  }
  else
  {
    chainonRdv* crt = l_tete;
    while(crt != precedent)
      crt = crt->cr_suivant;
    nouveauChainon->cr_suivant = precedent->cr_suivant;
    precedent->cr_suivant = nouveauChainon;
  }
}

chainonRdv* LCRdv::trier(string& nouveauLibelle) const
{
  unsigned i;
  chainonRdv* crt = l_tete;
  chainonRdv* precedent = l_tete;
  if(crt == nullptr)
    return nullptr;

  string crtLibelle;
  char nouveauChar, crtChar;

  while( crt != nullptr)
  {
    crtLibelle = crt->cr_libelle;
    i = 0;
    while (i < crtLibelle.length() & i < nouveauLibelle.length())
    {
      nouveauChar = tolower(nouveauLibelle.at(i));
      crtChar = tolower(crtLibelle.at(i));

      if(nouveauChar < crtChar)
      {
        if(crt != l_tete)
          return precedent;

        else if (crt == l_tete)
          return nullptr;
      }
      else if(nouveauChar > crtChar)
        break;

      else if(nouveauChar == crtChar)
        i++;
    }
    precedent = crt;
    crt = crt->cr_suivant;

    if(crt == nullptr)
      return precedent;
  }
}

void LCRdv::supprimer(string libelle)
{
  chainonRdv* crt = l_tete;
  if(libelle == crt->cr_libelle)
  {
    l_tete = crt->cr_suivant;
    //delete
  }
  else
  {
    while(crt->cr_suivant->cr_libelle != libelle)
    {
      crt = crt->cr_suivant;
    }
    crt->cr_suivant = crt->cr_suivant->cr_suivant;
  }
}

void LCRdv::afficher(string libelle, LCPersonne* listePersonnes)
{
  chainonRdv* crt = l_tete;

  while( (libelle != crt->cr_libelle) &  (crt != nullptr) )
  {
    crt = crt->cr_suivant;
  }

  if(crt != nullptr)
  {
    cout << libelle << " :" << endl;
    cout << "Le " << crt->cr_jour << "/" << crt->cr_mois << "/" << crt->cr_annee << " de " << crt->cr_heureDebut << "h à " << crt->cr_heureFin << "h" << endl;
    for(int i=0; i<crt->cr_participants.size(); i++)
      listePersonnes->afficherPersonne(crt->cr_participants[i][0], crt->cr_participants[i][1]);
  }
}

void LCRdv::afficherListeRdv()
{
  chainonRdv* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->cr_libelle << " ; ";
    crt = crt->cr_suivant;
  }
}

void LCRdv::modifierDate(string libelle, int jour, int mois, int annee)
{
  chainonRdv* crt = l_tete;

  while( (crt->cr_libelle != libelle) & (crt != nullptr) )
    crt = crt->cr_suivant;

  if(crt->cr_libelle == libelle)
  {
    crt->cr_jour = jour;
    crt->cr_mois = mois;
    crt->cr_annee = annee;
  }
}

void LCRdv::modifierHeure(string libelle, int heureDebut, int heureFin)
{
  chainonRdv* crt = l_tete;

  while( (crt->cr_libelle != libelle) & (crt != nullptr) )
    crt = crt->cr_suivant;

  if(crt->cr_libelle == libelle)
  {
    crt->cr_heureDebut = heureDebut;
    crt->cr_heureFin = heureFin;
  }
}

void LCRdv::modifierListePersonnes(string libelle, vector<vector<string>> participants)
{
  chainonRdv* crt = l_tete;

  while( (crt->cr_libelle != libelle) & (crt != nullptr) )
    crt = crt->cr_suivant;

  if(crt->cr_libelle == libelle)
  {
    crt->cr_participants = participants;
  }
}

void LCRdv::afficherEntreDates(int jour1, int mois1, int annee1, int jour2, int mois2, int annee2)
{
  chainonRdv* crt = l_tete;

  cout << "Entre le " << jour1 << "/" << mois1 << "/" << annee1 << " et le " << jour2 << "/" << mois2 << "/" << annee2 << endl;

  while( crt != nullptr )
  {

    bool inferieur = false;
    bool superieur = false;

    //test si la date de rdv est supérieure a la borne inférieur
    if(crt->cr_annee > annee1)
      superieur = true;
    else if(crt->cr_annee == annee1)
    {
      if(crt->cr_mois > mois1)
        superieur = true;
      else if(crt->cr_mois == mois1)
        if(crt->cr_jour >= jour1)
          superieur = true;
    }

    //test si la date de rdv est inférieur a la borne superieure
    if(crt->cr_annee < annee2)
      inferieur = true;
    else if(crt->cr_annee == annee2)
    {
      if(crt->cr_mois < mois2)
        inferieur = true;
      else if(crt->cr_mois == mois2)
        if(crt->cr_jour <= jour2)
          inferieur = true;
    }

    //si la date de rdv est comprise entre les deux bornes, on l'afficher
    if(inferieur & superieur)
      cout << crt->cr_libelle << " ;";

    crt = crt->cr_suivant;
  }
}
