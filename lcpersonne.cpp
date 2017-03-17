#include <string>
#include <iostream>
#include "lcpersonne.h"
#include "lcrdv.h"

using namespace std;

/**
  Construit un objet liste chainée
*/
LCPersonne::LCPersonne():l_tete{nullptr}
{}

/**
  Détruit un objet liste chainée
*/
LCPersonne::~LCPersonne()
{
  //appel du destructeur de chaque chainonPersonne contenu dans la liste
  chainonPersonne* suivant = l_tete;

  while(suivant != nullptr)
  {
    suivant = l_tete->cp_suivant;
    delete l_tete;
    l_tete = suivant;
  }

}

/**
  Ajoute une instance de l'objet chainonPersonne à la liste chainée
  @param[in] nom, prenom, numero, email - des string contenant les informations de la personne
*/
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

/**
  Trouve la position à laquelle ajouter un nouveau chainon dans la liste de personnes
  @param[in] nouveauNom, nouveauPrenom - le nom de la personne à ajouter
  @return precedant - un pointeur sur le chainon précédant celui devant être ajouté
*/
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
//A AJOUTER
    if(nouveauNom.length()<crtNom.length())
    {
      if(i==nouveauNom.length())
      {
        return precedent;
      }
    }
//A AJOUTER
    precedent = crt;
    crt = crt->cp_suivant;

    if(crt == nullptr)
      return precedent;
  }
}

/**
  Affiche une liste de toutes les instance de la classe chainonPersonne avec les paramètres associés
*/
void LCPersonne::afficher()
{
  chainonPersonne* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->cp_nom << " ; " << crt->cp_prenom << " ; " << crt->cp_numero << " ; " << crt->cp_email << endl;
    crt = crt->cp_suivant;
  }
}

/**
  Recherche un personne et affiche ses informations
  @param[in] nom, prenom - des string contenant le nom de la personne
*/
void LCPersonne::afficherPersonne(string nom, string prenom)
{
  chainonPersonne* crt = l_tete;
  while( !((crt->cp_nom == nom) & (crt->cp_prenom == prenom)) & (crt->cp_suivant != nullptr) )
  {
    crt = crt->cp_suivant;
  }

  if( (crt->cp_nom == nom) & (crt->cp_prenom == prenom) )
    cout << crt->cp_nom << " ; " << crt->cp_prenom << " ; " << crt->cp_numero << " ; " << crt->cp_email << endl;
}

/**
  supprime un chainon de la liste
  @param[in] nom, prenom - des string contenant le nom de la personne à retirer de la liste
*/
void LCPersonne::supprimer(string nom, string prenom, LCRdv* listeRdv)
{
  chainonPersonne* crt = l_tete;

  if(!listeRdv->avoirRdv(nom, prenom))
  {
    if(nom == crt->cp_nom & prenom == crt->cp_prenom)
    {
      l_tete = crt->cp_suivant;
      delete crt;
    }
    else
    {
      while( !(crt->cp_suivant->cp_nom == nom & crt->cp_suivant->cp_prenom == prenom) )
      {
        crt = crt->cp_suivant;
      }
      chainonPersonne* tmp = crt->cp_suivant;
      crt->cp_suivant = crt->cp_suivant->cp_suivant;
      delete tmp;;
    }
  }
  else
  {
    cout << "La personne a un rdv en cours, impossible de supprimer" << endl;
  }
}

void LCPersonne::modifierNumero(string nom, string prenom, string numero)
{
  chainonPersonne* crt = l_tete;

  while( (crt->cp_nom!=nom & crt->cp_prenom!=prenom) & crt != nullptr )
    crt = crt->cp_suivant;

  if(crt->cp_nom == nom & crt->cp_prenom==prenom)
  {
    crt->cp_numero = numero;
  }
}

void LCPersonne::modifierEmail(string nom, string prenom, string email)
{
  chainonPersonne* crt = l_tete;

  while( (crt->cp_nom!=nom & crt->cp_prenom!=prenom) & crt != nullptr )
    crt = crt->cp_suivant;

  if(crt->cp_nom == nom & crt->cp_prenom==prenom)
  {
    crt->cp_email = email;
  }
}
