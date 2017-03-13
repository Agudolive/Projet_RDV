#ifndef LCPERSONNE_H
#define LCPERSONNE_H
#include "chainonpersonne.h"
#include <string>
using namespace std;

class LCRdv;

class LCPersonne
{
public:
    LCPersonne();
    ~LCPersonne();
    void ajouter(string nom, string prenom, string numero, string email);
    void afficher();
    void afficherPersonne(string nom, string prenom);
    void supprimer(string nom, string prenom, LCRdv* listeRdv);

    void modifierNumero(string nom, string prenom, string numero);
    void modifierEmail(string nom, string prenom, string email);

    //a faire
    bool estLibre(string nom, string prenom /*date+heure debut*/ /*date+heure fin*/); //personne est-elle libre entre 2 dates

private:
    chainonPersonne* l_tete;
    chainonPersonne* trier(string& nouveauNom, string& nouveauPrenom) const;
};

#endif // LCPERSONNE_H
