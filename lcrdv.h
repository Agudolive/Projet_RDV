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
    void afficherEntreDates(int jour1, int mois1, int annee1, int jour2, int mois2, int annee2);
    void afficherPourPersonne(string nom, string prenom, LCPersonne* listePersonnes);

    void modifierDate(string libelle, int jour, int mois, int annee);
    void modifierHeure(string libelle, int heureDebut, int HeureFin);
    void modifierListePersonnes(string libelle, vector<vector<string>> participants);
    bool estLibre(string nom, string prenom, int jour1, int mois1, int annee1, int heure1, int jour2, int mois2, int annee2, int heure2);

    bool avoirRdv(string nom, string prenom);

    string getLibelle();
    int getJour();
    int getMois();
    int getAnnee();
    int getHeureDebut();
    int getHeureFin();
    vector<vector<string>> getParticipants(chainonRdv &crt, vector<string> &participants);


private:
    chainonRdv* l_tete;
    chainonRdv* trier(string& nouveauLibelle) const;
};

#endif // LCRDV_H
