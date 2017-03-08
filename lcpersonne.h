#ifndef LCPERSONNE_H
#define LCPERSONNE_H
#include "chainonpersonne.h"
#include <string>
using namespace std;

class chainonPersonne;

class LCPersonne
{
public:
    LCPersonne();
    ~LCPersonne();
    void ajouter(string nom, string prenom, string numero, string email);
    void afficher();
    void afficherPersonne(string nom);
    void supprimer(string nom, string prenom);

    //a faire
    void modifier(string nom, string prenom);
    bool estLibre(string nom, string prenom);

private:
    chainonPersonne* l_tete;
    chainonPersonne* trier(string& nouveauNom, string& nouveauPrenom) const;
};

#endif // LCPERSONNE_H
