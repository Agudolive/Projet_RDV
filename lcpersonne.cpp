#include <string>
#include <iostream>
#include "lcpersonne.h"

using namespace std;

LCPersonne::LCPersonne():l_tete{nullptr}
{
}

LCPersonne::~LCPersonne()
{
}

void LCPersonne::ajouter(string nom, string prenom, string numero, string email)
{
  chainonPersonne* nouveauChainon = new chainonPersonne(nom, prenom, numero, email);
  chainonPersonne* precedent = trier(nom, prenom);

  if(precedent == nullptr)
  {
    nouveauChainon->cp_suivant = l_tete;
    l_tete = nouveauChainon;
  }
  else
  {
    chainonPersonne* crt = l_tete;
    while(crt != precedent)
      crt = crt->cp_suivant;
    nouveauChainon->cp_suivant = precedent->cp_suivant;
    precedent->cp_suivant = nouveauChainon;
  }
}

chainonPersonne* LCPersonne::trier(string& nouveauNom, string& nouveauPrenom) const
{
  unsigned i;
  chainonPersonne* crt = l_tete;
  chainonPersonne* precedent = l_tete;
  if(crt == nullptr)
    return nullptr;

  string crtNom, crtPrenom;
  char nouveauChar, crtChar;

  while( crt != nullptr)
  {
    crtNom = crt->cp_nom;
    crtPrenom = crt->cp_prenom;
    i = 0;
    while (i < crtNom.length() & i < nouveauNom.length())
    {
      nouveauChar = tolower(nouveauNom.at(i));
      crtChar = tolower(crtNom.at(i));

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
    crt = crt->cp_suivant;

    if(crt == nullptr)
      return precedent;
  }
}

void LCPersonne::afficher()
{
  chainonPersonne* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->cp_nom << " ; " << crt->cp_prenom << " ; " << crt->cp_numero << " ; " << crt->cp_email << endl;
    crt = crt->cp_suivant;
  }
}

void LCPersonne::supprimer(string nom, string prenom)
{
  chainonPersonne* crt = l_tete;
  if(nom == crt->cp_nom & prenom == crt->cp_prenom)
  {
    l_tete = crt->cp_suivant;
    //delete
  }
  else
  {
    while(crt->cp_suivant->cp_nom != nom & crt->cp_suivant->cp_prenom != prenom)
    {
      crt = crt->cp_suivant;
    }
    crt->cp_suivant = crt->cp_suivant->cp_suivant;
  }
}
