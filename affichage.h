#ifndef AFFICHAGE_H
    #include <iostream>
#define AFFICHAGE_H

using namespace std;

class interface;

class affichage
{
public:
    affichage();
    affichage(interface* d_interface);
    void demarrer();
    void menuPrincipale();
    void menuPersonne();
    void menuRDV();
    void menuAutre();

private:

    interface* a_interface;

};

#endif
