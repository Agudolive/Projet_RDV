#include "lcrdv.h"
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

void LCRdv::afficher()
{
  chainonRdv* crt = l_tete;
  while(crt != nullptr)
  {
    cout << crt->cr_libelle << endl;
    crt = crt->cr_suivant;
  }
}
