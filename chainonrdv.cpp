#include "chainonrdv.h"
#include <string>
using namespace std;

chainonRdv::chainonRdv(string libelle, int jour, int mois, int annee,
                      int heureDebut, int heureFin, vector<string> participants)
                      :cr_libelle{libelle}, cr_jour{jour}, cr_mois{mois},
                      cr_annee{annee}, cr_heureDebut{heureDebut},
                      cr_heureFin{heureFin}, cr_participants{participants}
{}

chainonRdv::~chainonRdv()
{}
