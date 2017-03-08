#ifndef LCRDV_H
#define LCRDV_H
#include "chainonrdv.h"
#include <string>
using namespace std;

class LCPersonne;

class LCRdv
{
public:
    LCRdv();
    ~LCRdv();
    void ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<string> participants);
    void supprimer(string libelle);
    void afficher(string libelle, LCPersonne* listePersonnes);

    //a faire
    void modifier(string libelle);
    

private:
    chainonRdv* l_tete;
};

#endif // LCRDV_H
