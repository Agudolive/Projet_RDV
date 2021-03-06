#include <string>
#include <iostream>
#include <vector>
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
    while ((i < crtNom.length()) & (i < nouveauNom.length()))
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

    if(nouveauNom.length()<crtNom.length())
    {
      if(i==nouveauNom.length())
      {
        return precedent;
      }
    }

    if(nouveauNom == crt->cp_nom)
    {

      i = 0;
      while ((i < crt->cp_prenom.length()) & (i < nouveauPrenom.length()))
      {
        nouveauChar = tolower(nouveauPrenom.at(i));
        crtChar = tolower(crt->cp_prenom.at(i));

        if(nouveauChar < crtChar)
        {
          if(crt != l_tete)
            return precedent;

          else if (crt == l_tete)
            return nullptr;
        }
        else if(nouveauChar > crtChar)
          break;
        else
          i++;
      }
    }

    precedent = crt;
    crt = crt->cp_suivant;

    if(crt == nullptr)
      return precedent;
  }
  return nullptr;
}


/**
  supprime une personne de la liste si celle-ci n'a pas rendez-vous
  @param[in] nom, prenom - des string contenant le nom de la personne à retirer de la liste
  @param[in] listeRdv - la liste de rendez-vous dans laquelle cherche
  @return - vrai si la personne n'a pas de rdv, faux sinon
*/
bool LCPersonne::supprimer(string nom, string prenom, LCRdv* listeRdv)
{
  chainonPersonne* crt = l_tete;

  if(!listeRdv->avoirRdv(nom, prenom))
  {
    if( (nom == crt->cp_nom) & (prenom == crt->cp_prenom) )
    {
      l_tete = crt->cp_suivant;
      delete crt;
    }
    else
    {
      while( !( (crt->cp_suivant->cp_nom == nom) & (crt->cp_suivant->cp_prenom == prenom) ) )
      {
        crt = crt->cp_suivant;
      }
      chainonPersonne* tmp = crt->cp_suivant;
      crt->cp_suivant = crt->cp_suivant->cp_suivant;
      delete tmp;
    }
  }
  else
  {
    return 0;
  }
  return 1;
}

/**
  modifie le numero d'une personne
  @param[in] nom, prenom - des string contenant le nom de la personne à retirer de la liste
  @param[in] numero - un string contenant le nouveau numero
*/
void LCPersonne::modifierNumero(string nom, string prenom, string numero)
{
  chainonPersonne* crt = l_tete;

  while( ( (crt->cp_nom!=nom) & (crt->cp_prenom!=prenom) ) & (crt != nullptr) )
    crt = crt->cp_suivant;

  if( (crt->cp_nom == nom) & (crt->cp_prenom==prenom) )
  {
    crt->cp_numero = numero;
  }
}

/**
  modifie l'adresse email d'une personne
  @param[in] nom, prenom - des string contenant le nom de la personne à retirer de la liste
  @param[in] numero - un string contenant la nouvelle adresse
*/
void LCPersonne::modifierEmail(string nom, string prenom, string email)
{
  chainonPersonne* crt = l_tete;

  while( ( (crt->cp_nom!=nom) & (crt->cp_prenom!=prenom) ) & (crt != nullptr) )
    crt = crt->cp_suivant;

  if( (crt->cp_nom == nom) & (crt->cp_prenom==prenom) )
  {
    crt->cp_email = email;
  }
}

/**
Retourne l'adresse de la tete de la liste rendez-vous
@return - l'adresse du chainon de tete
*/
chainonPersonne* LCPersonne::getTete(){
  return l_tete;
}

/**
Retourne l'adresse email d'une personne
@param[in] crt - l'adresse du chainon contenant l'information
@return - un string contnant l'adresse email
*/
string LCPersonne::getEmail(chainonPersonne* crt){
  return crt->cp_email;
}

/**
Retourne le nom d'une personne
@param[in] crt - l'adresse du chainon courant
@return - un string contenant le nom
*/
string LCPersonne::getNom(chainonPersonne* crt){
  return crt->cp_nom;
}

/**
Retourne le prenom d'une personne
@param[in] crt - l'adresse du chainon courant
@return - un string contenant le prenom
*/
string LCPersonne::getPrenom(chainonPersonne* crt){
  return crt->cp_prenom;
}

/**
Retourne le numero d'une personne
@param[in] crt - l'adresse du chainon courant
@return - un string contenant le numero
*/
string LCPersonne::getNumero(chainonPersonne* crt){
  return crt->cp_numero;
}

/**
Retourne l'adresse de la personne suivante dans la liste
@param[in] crt - l'adresse du chainon courant
@return - l'adresse du chainon suivant
*/
chainonPersonne* LCPersonne::getSuivant(chainonPersonne* crt){
  return crt->cp_suivant;
}
