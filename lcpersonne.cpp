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
    nouveauChainon->c_suivant = l_tete;
    l_tete = nouveauChainon;
  }
  else
  {
    chainonPersonne* crt = l_tete;
    while(crt != precedent)
      crt = crt->c_suivant;
    nouveauChainon->c_suivant = precedent->c_suivant;
    precedent->c_suivant = nouveauChainon;
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
    crtNom = crt->c_nom;
    crtPrenom = crt->c_prenom;
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
    crt = crt->c_suivant;

    if(crt == nullptr)
      return precedent;
  }
}

void LCPersonne::afficher()
{
  chainonPersonne* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->c_nom << " ; " << crt->c_prenom << " ; " << crt->c_numero << " ; " << crt->c_email << endl;
    crt = crt->c_suivant;
  }
}

void LCPersonne::supprimer(string nom, string prenom)
{
  chainonPersonne* crt = l_tete;
  if(nom == crt->c_nom & prenom == crt->c_prenom)
  {
    l_tete = crt->c_suivant;
    //delete
  }
  else
  {
    while(crt->c_suivant->c_nom != nom & crt->c_suivant->c_prenom != prenom)
    {
      crt = crt->c_suivant;
    }
    crt->c_suivant = crt->c_suivant->c_suivant;
  }
}
