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
    void afficherListeRdv();
    
    void modifierDate(string libelle, int jour, int mois, int annee);
    void modifierHeure(string libelle, int heureDebut, int HeureFin);
    void modifierListePersonnes(string libelle, vector<string> participants);

    //a faire
    void afficherEntreDates(/*date+heure debut*/ /*date+heure fin*/); //afficher rdv entre 2 dates
    void afficherPourPersonne(string nom); //afficher tous rdv d'une personne

private:
    chainonRdv* l_tete;
    chainonRdv* trier(string& nouveauLibelle) const;
};

#endif // LCRDV_H
