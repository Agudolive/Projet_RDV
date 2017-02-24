#ifndef LCRDV_H
#define LCRDV_H
#include "chainonrdv.h"
#include <string>
using namespace std;

class chainonRdv;

class LCRdv
{
public:
    LCRdv();
    ~LCRdv();
    void ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<string> participants);
    void supprimer(string libelle);
    void afficher();

private:
    chainonRdv* l_tete;
};

#endif // LCRDV_H
