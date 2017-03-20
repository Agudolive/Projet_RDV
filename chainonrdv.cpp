#include "chainonrdv.h"
#include <string>
using namespace std;

/**
  Construit un objet chainonRdv
  @param[in] libelle - string contenant le libelle du rendez-vous
  @param[in] jour, mois, annee, heureDebut, heureFin - des entiers
  @param[in] participants - un vecteur à deux dimensions contenant les noms et prenoms des participants
*/
chainonRdv::chainonRdv(string libelle, int jour, int mois, int annee,
                      int heureDebut, int heureFin, vector<vector<string>> participants)
                      :cr_libelle{libelle}, cr_jour{jour}, cr_mois{mois},
                      cr_annee{annee}, cr_heureDebut{heureDebut},
                      cr_heureFin{heureFin}, cr_participants{participants}
{}

/**
  Construit un objet chainonRdv par defaut   
*/
chainonRdv::~chainonRdv()
{}
