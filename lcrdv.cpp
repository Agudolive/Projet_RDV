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
  //delete l_tete;
  //delete this;
}

void LCRdv::ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<string> participants)
{
  chainonRdv* nouveauChainon = new chainonRdv(libelle, jour, mois, annee, heureDebut, heureFin, participants);

  nouveauChainon->cr_suivant = l_tete;
  l_tete = nouveauChainon;
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
    for(int i=0; i<crt->cr_participants.size(); i++)
      listePersonnes->afficherPersonne(crt->cr_participants[i]);
  }

}
