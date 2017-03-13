#ifndef LCRDV_H
#define LCRDV_H
#include "chainonrdv.h"
#include <string>
using namespace std;

class LCPersonne;

class LCRdv
{
friend class fromJson;
public:
    LCRdv();
    ~LCRdv();
    void ajouter(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<string> participants);
    void supprimer(string libelle);
    void afficher(string libelle, LCPersonne* listePersonnes);

    //a faire
    //tri rdv par ordre alphabétique
    void modifier(string libelle); //modifier, date, heure et liste personne
    void afficherEntreDates(/*date+heure debut*/ /*date+heure fin*/); //afficher rdv entre 2 dates
    void afficherPourPersonne(string nom); //afficher tous rdv d'une personne

private:
    chainonRdv* l_tete;
};

#endif // LCRDV_H
