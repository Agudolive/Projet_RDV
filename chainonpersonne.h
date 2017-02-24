#ifndef CHAINONPERSONNE_H
#define CHAINONPERSONNE_H
#include <string>
using namespace std;

class chainonPersonne
{
friend class LCPersonne;

private:

    chainonPersonne(string nom, string prenom, string numero, string email);
    ~chainonPersonne();
    string c_nom;
    string c_prenom;
    string c_numero;
    string c_email;
    chainonPersonne* c_suivant;
};

#endif // CHAINONPERSONNE_H
