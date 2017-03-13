#ifndef LCPERSONNE_H
#define LCPERSONNE_H
#include "chainonpersonne.h"
#include <string>
using namespace std;

class chainonPersonne;

class LCPersonne
{
friend class fromJson;
public:
    LCPersonne();
    ~LCPersonne();
    void ajouter(string nom, string prenom, string numero, string email);
    void afficher();
    void afficherPersonne(string nom);
    void supprimer(string nom, string prenom);

    //a faire
    //si un personne a un rdv, on ne peut pas la supprimer, affiher message erreur
    void modifier(string nom, string prenom); //tout modifier sauf nom/prenom
    bool estLibre(string nom, string prenom /*date+heure debut*/ /*date+heure fin*/); //personne est-elle libre entre 2 dates

private:
    chainonPersonne* l_tete;
    chainonPersonne* trier(string& nouveauNom, string& nouveauPrenom) const;
};

#endif // LCPERSONNE_H
