#include <string>
#include "lcpersonne.h"
#include "chainonpersonne.h"
#include "lcrdv.h"
#include "chainonrdv.h"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    //création d'un répertoire de personnes
    LCPersonne repertoirePersonne;
    repertoirePersonne.ajouter("agudo","hassane", "0687654565", "eifnopien@zefhzeuf.fr");
    repertoirePersonne.ajouter("gherardi","aliot", "0389769809", "eifazefazeaefhz@euf.fr");
    repertoirePersonne.ajouter("carasco","sylvain", "0987675643", "eifnopien@zefhzeuf.fr");
    repertoirePersonne.ajouter("hindie","olivier", "0789765487", "eifazefazeae@fhzeuf.fr");
    repertoirePersonne.afficher();
    cout << endl;


    //création d'un vecteur string de participants a passer au constructeur
    //liste rendez vous qui appelle lui meme le constructeur d'un nouveau chainon
    vector<string> p1(2);
    p1[0]="agudo";
    p1[1]="hindie";

    vector<string> p2(3);
    p2[0]="gherardi";
    p2[1]="carasco";
    p2[2]="hindie";

    //liste de rendez vous contenant 2 rendez vous
    LCRdv repertoireRdv;
    repertoireRdv.ajouter("rdv1", 1, 1, 1, 1, 2, p1);
    repertoireRdv.ajouter("rdv2", 2, 2, 2, 2, 3, p2);

    repertoireRdv.afficher("rdv1", &repertoirePersonne);
    cout << endl;

    repertoireRdv.afficher("rdv2", &repertoirePersonne);
    cout << endl;
}
