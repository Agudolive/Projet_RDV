#include "lcrdv.h"
#include "lcpersonne.h"
#include <string>
#include <iostream>
#include <vector>
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
    delete l_tete;
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

  if(crt == nullptr) //si liste vide return null
    return nullptr;

  string crtLibelle;
  char nouveauChar, crtChar;

  while( crt != nullptr) //parcourt de toute la liste de rdv
  {
    crtLibelle = crt->cr_libelle;
    i = 0;
    while ((i < crtLibelle.length()) & (i < nouveauLibelle.length())) //boucle sur tous les caractères du libelle avec le moins de lettres
    {
      nouveauChar = tolower(nouveauLibelle.at(i));
      crtChar = tolower(crtLibelle.at(i));

      if(nouveauChar < crtChar) //si le nouveau caractère est plus petit que le caractère courant de la liste, on retourne le chainon precedent
      {
        if(crt != l_tete) //cas en milleur de liste
          return precedent;

        else if (crt == l_tete) //cas en tete de liste
          return nullptr;
      }
      else if(nouveauChar > crtChar) //si le nouveau caractère est plus grand que le caractère courant de la liste, on passe un rdv suivant
        break;

      else if(nouveauChar == crtChar) //si on a le même caracère, on passe au caractère suivant
        i++;
    }

    if(nouveauLibelle.length()<crtLibelle.length()) //test si la taille du nouveau libelle est plus petite que celle du libelle de la liste
    {
      if(i==nouveauLibelle.length()) //si on a comparé toutes les lettres et qu'elles sont toutes egales alors on a trouvé l'emplacement du nouveau rdv
      {
        return precedent;
      }
    }

    precedent = crt; //sauvegarde du rdv precedent
    crt = crt->cr_suivant; //incrementation pour parcourt de la liste de rdv

    if(crt == nullptr) //si on arrive en bout de liste, on peut ajouter le rdv ici
      return precedent;
  }
  return nullptr;
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
    delete crt;
  }
  else
  {
    while(crt->cr_suivant->cr_libelle != libelle)
    {
      crt = crt->cr_suivant;
    }
    crt = crt->cr_suivant;
    crt->cr_suivant = crt->cr_suivant->cr_suivant;
    delete crt;
  }
}

/**
  Créer une liste de tous les rendez-vous compris entre deux dates
  @param[in] jour1, mois1, annee1 - des entiers représentant la borne inférieure de la date
  @param[in] jour2, mois2, annee2 - des entiers représentant la borne supérieure de la date
  @return liste - vecteur contenant les libellés des rdv en question
*/
vector<string> LCRdv::afficherEntreDates(int jour1, int mois1, int annee1, int jour2, int mois2, int annee2)
{
  vector<string> liste(0);
  chainonRdv* crt = l_tete;

  while( crt != nullptr ) //parcourt de toute la liste de rdv
  {

    bool inferieur = false;
    bool superieur = false;

    //test si la date de rdv est supérieure a la borne inférieur
    if(crt->cr_annee > annee1) //si l'annee de rdv est strictement superieure a la borne inferieure on valide la condition
      superieur = true;
    else if(crt->cr_annee == annee1) //sinon, si il s'agit de la meme année
    {
      if(crt->cr_mois > mois1) //si le mois de rdv est strictement superieur a la borne inferieure on valide la condition
        superieur = true;
      else if(crt->cr_mois == mois1) //sinon, si il s'agit du meme mois
        if(crt->cr_jour >= jour1) //si le jour de rdv est superieur ou egal a la borne inferieure on valide la condition
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

    if(inferieur & superieur)  //si les deux conditions sont remplies, on ajoute le libelle du rdv dans le vecteur
      liste.push_back(crt->cr_libelle);

    crt = crt->cr_suivant;
  }
  return liste;
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

/**
Vérifie si une personne a un rendez-vous dans tout le repertoire
@param[in] nom, prenom - les identifiants de la personne
@return rdv - vrai si la personne a un rdv, faux sinon
*/
bool LCRdv::avoirRdv(string nom, string prenom)
{
  chainonRdv* crt = l_tete;
  bool rdv = false;

  while(crt)
  {
    for(unsigned i=0; i<crt->cr_participants.size(); i++)
    {
      if( (crt->cr_participants[i][0]==nom) & (crt->cr_participants[i][1]==prenom) )
        rdv = true;
    }
    crt = crt->cr_suivant;
  }
  return rdv;
}

/**
Vérifie si une personne est libre entre deux dates données
@param[in] nom, prenom - les identifiants de la personne
@param[in] jour1, mois1, annee1, heure1 - le début de la période
@param[in] jour2, mois2, annee2, heure2 - la fin de la période
@return - vrai si la personne est libre, faux sinon
*/
bool LCRdv::estLibre(string nom, string prenom, int jour1, int mois1, int annee1, int heure1, int jour2, int mois2, int annee2, int heure2){

  chainonRdv* crt = l_tete;

  while(crt != nullptr){
    for(unsigned i=0; i < crt->cr_participants.size(); i++){
      if((crt->cr_participants[i][0] == nom) && (crt->cr_participants[i][1] == prenom)){

        bool inferieur = false;
        bool superieur = false;

        if(crt->cr_annee > annee1)
          superieur = true;
        else if(crt->cr_annee == annee1){
          if(crt->cr_mois > mois1)
            superieur = true;
          else if(crt->cr_mois == mois1){
            if(crt->cr_jour > jour1)
              superieur = true;
            else if(crt->cr_jour == jour1){
              superieur = true;
              if(crt->cr_heureDebut >= heure1)
                superieur = true;
            }
          }
        }

        //test si la date de rdv est inférieur a la borne superieure
        if(crt->cr_annee < annee2)
        inferieur = true;
        else if(crt->cr_annee == annee2){
          if(crt->cr_mois < mois2)
            inferieur = true;
          else if (crt->cr_mois == mois2){
            if(crt->cr_jour <= jour2)
              inferieur = true;
            else if (crt->cr_jour == jour2){
              inferieur = true;
              if(crt->cr_heureFin <= heure2)
                inferieur = true;
            }
          }
        }

        if(inferieur & superieur){
          return 0;
        }
      }
    }
    crt = crt->cr_suivant;
  }
  return 1;
}

/**
Retourne le libellé du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un string contenant la valeur
*/
string LCRdv::getLibelle(chainonRdv *crt)
{
  return crt->cr_libelle;
}

/**
Retourne le jour du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un int contenant la valeur
*/
int LCRdv::getJour(chainonRdv *crt)
{
  return crt->cr_jour;
}

/**
Retourne le mois du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un int contenant la valeur
*/
int LCRdv::getMois(chainonRdv *crt)
{
  return crt->cr_mois;
}

/**
Retourne l'annee du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un int contenant la valeur
*/
int LCRdv::getAnnee(chainonRdv *crt)
{
  return crt->cr_annee;
}

/**
Retourne l'heure de début du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un int contenant la valeur
*/
int LCRdv::getHeureDebut(chainonRdv *crt)
{
  return crt->cr_heureDebut;
}

/**
Retourne l'heure de fin du rendez-vous
@param[in] crt - l'adresse du chainon contenant l'information
@return - un int contenant la valeur
*/
int LCRdv::getHeureFin(chainonRdv *crt)
{
  return crt->cr_heureFin;
}

/**
Retourne le chainon suivant de la liste rendez-vous
@param[in] crt - l'adresse du chainon courant
@return - l'adresse du chainon suivant
*/
chainonRdv * LCRdv::getSuivant(chainonRdv *crt)
{
  return crt->cr_suivant;
}

/**
Retourne l'adresse de la tete de la liste rendez-vous
@param[in] crt - l'adresse du chainon courant
@return - l'adresse du chainon de tete
*/
chainonRdv *LCRdv::getTete()
{
  return l_tete;
}

/**
Retourne la liste de tous les participants d'un rendez-vous
@param[in] crt - l'adresse du chainon courant
@return - vecteur a deux dimensions contenant tous les participants
*/
vector<vector<string>> LCRdv::getParticipants(chainonRdv *crt) {
    return crt->cr_participants;
}
