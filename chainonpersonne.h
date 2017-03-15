#ifndef CHAINONPERSONNE_H
#define CHAINONPERSONNE_H
#include <string>
using namespace std;

class chainonPersonne
{
friend class LCPersonne;

public:

private:

    chainonPersonne(string nom, string prenom, string numero, string email);
    ~chainonPersonne();
    string cp_nom;
    string cp_prenom;
    string cp_numero;
    string cp_email;
    chainonPersonne* cp_suivant;
};

#endif // CHAINONPERSONNE_H
