#ifndef CHAINONPERSONNE_H
#define CHAINONPERSONNE_H


class chainonPersonne
{
public:
    chainonPersonne(string nom, string prenom, string numero, string email);

private:

    string c_nom;
    string c_prenom;
    string c_numero;
    string c_email;
    chainonPersonne* c_suivant;
};

#endif // CHAINONPERSONNE_H
