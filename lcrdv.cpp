#include "lcrdv.h"
#include "lcpersonne.h"
#include <string>
#include <iostream>
using namespace std;

/**
  Construit un objet liste chainée
*/
LCRdv::LCRdv():l_tete{nullptr}
{}

/**
  Détruit un objet liste chainée
*/
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

/**
  Ajoute une instance de l'objet chainonRdv à la liste chainée
  @param[in] libelle - le nom du rendez-vous
  @param[in] jour, mois, annee, heureDebut, heureFin - des entiers représentant la date et l'heure du rendez-vous
  @param[in] participants - vecteur a 2 dimensions contenant le nom et prénom des participants
*/
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

/**
  Trouve la position à laquelle ajouter un nouveau chainon dans la liste de rendez-vous
  @param[in] nouveauLibelle - le libellé du rendez-vous à ajouter
  @return precedant - un pointeur sur le chainon précédant celui devant être ajouté
*/
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

/**
  Supprime un chainon de la liste
  @param[in] libelle - le libellé du rendez-vous à supprimer
*/
void LCRdv::supprimer(string libelle)
{
  chainonRdv* crt = l_tete;
  if(libelle == crt->cr_libelle)
  {
    l_tete = crt->cr_suivant;
    crt->~chainonRdv();
  }
  else
  {
    while(crt->cr_suivant->cr_libelle != libelle)
    {
      crt = crt->cr_suivant;
    }
    crt->cr_suivant = crt->cr_suivant->cr_suivant;

    /* à trouver : comment appeler destructeur pour le chainonRdv
    crt->cr_suivant->cr_suivant = nullptr;
    crt->cr_suivant->~chainonRdv();
    */
  }
}

/**
  Affiche pour un rendez-vous les paramètres et les informations des personnes présentes
  @param[in] libelle - le libellé du rendez-vous en question
  @param[in] listePersonnes - le répertoires des personnes enregistrées dans l'application
*/
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

/**
  Affiche une liste de tous les rendez-vous présents dans la liste chainée
*/
void LCRdv::afficherListeRdv()
{
  chainonRdv* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->cr_libelle << " ; ";
    crt = crt->cr_suivant;
  }
}

/**
  Affiche tous les rendez-vous compris entre deux dates
  @param[in] jour1, mois1, annee1 - des entiers représentant la borne inférieure de la date
  @param[in] jour2, mois2, annee2 - des entiers représentant la borne supérieure de la date
*/
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
    cout << crt->cr_libelle << " ; ";

    crt = crt->cr_suivant;
  }
}

/**
  Affiche tous les rendez-vous d'une personne
  @param[in] nom, prenom - des string de la personne
  @param[in] listePersonnes - le répertoires des personnes enregistrées dans l'application
*/
void LCRdv::afficherPourPersonne(string nom, string prenom, LCPersonne* listePersonnes)
{
  chainonRdv* crt = l_tete;

  while( crt != nullptr )
  {
    for(int i=0; i<crt->cr_participants.size(); i++)
    if( (crt->cr_participants[i][0]==nom) & (crt->cr_participants[i][1]==prenom) )
    afficher(crt->cr_libelle, listePersonnes);

    crt = crt->cr_suivant;
  }
}

/**
  Modifier la date d'un rendez-vous
  @param[in] libelle - le libellé du rendez-vous à modifier
  @param[in] jour, mois, annee - les nouvelles valeurs à ajouter au rendez-vous
*/
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

/**
Modifier l'heure d'un rendez-vous
@param[in] libelle - le libellé du rendez-vous à modifier
@param[in] heureDebut, heureFin - les nouvelles valeurs à ajouter au rendez-vous
*/
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

/**
Modifier la liste de participants d'un rendez-vous
@param[in] libelle - le libellé du rendez-vous à modifier
@param[in] participants - la nouvelle liste de participants à ajouter au rendez-vous
*/
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
