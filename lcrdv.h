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
    void ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<vector<string>> participants);
    void supprimer(string libelle);
    void afficher(string libelle, LCPersonne* listePersonnes);
    void afficherListeRdv();

    void modifierDate(string libelle, int jour, int mois, int annee);
    void modifierHeure(string libelle, int heureDebut, int HeureFin);
    void modifierListePersonnes(string libelle, vector<vector<string>> participants);

    void afficherEntreDates(int jour1, int mois1, int annee1, int jour2, int mois2, int annee2);


    //a faire
    void afficherPourPersonne(string nom); //afficher tous rdv d'une personne

private:
    chainonRdv* l_tete;
    chainonRdv* trier(string& nouveauLibelle) const;
};

#endif // LCRDV_H
