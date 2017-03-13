#ifndef CHAINONRDV_H
#define CHAINONRDV_H
#include <string>
#include <vector>
using namespace std;

class chainonRdv
{

friend class LCRdv;
friend class fromJson;

private:

    chainonRdv(string libelle, int jour, int mois, int annee, int heureDebut, int heureFin, vector<string> participants);
    ~chainonRdv();
    string cr_libelle;
    int cr_jour;
    int cr_mois;
    int cr_annee;
    int cr_heureDebut;
    int cr_heureFin;
    vector<string> cr_participants;
    chainonRdv* cr_suivant;
};

#endif // CHAINONRDV_H
