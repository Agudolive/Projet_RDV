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
    cout << "répertoire personnes :" << endl;
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
    repertoireRdv.ajouter("rdv1", 28, 1, 2016, 15, 16, p1);
    repertoireRdv.ajouter("rdv2", 3, 2, 2017, 11, 12, p2);

    //affichage de la liste de rdv
    cout << "répertoire rdv :" << endl;
    repertoireRdv.afficherListeRdv();
    cout << endl << endl;

    //affichage de chaque rdv
    repertoireRdv.afficher("rdv1", &repertoirePersonne);
    cout << endl;

    repertoireRdv.afficher("rdv2", &repertoirePersonne);
    cout << endl;

    //afficher tous les rdv entre 2 dates     int jour1, int mois1, int annee1, int jour2, int mois2, int annee2
    repertoireRdv.afficherEntreDates(1, 3, 2014, 29, 6, 2018);
    cout << endl;

    //modification d'un rendez-vous
    bool b = false;
    while(b)
    {
        string rdv;
        cout << "Quel Rdv modifier ?" << endl;
        cin >> rdv;

        int choix;
        cout << "Que voulez-vous modifier ?" << endl;
        cout << "1) Date" << endl;
        cout << "2) Heure" << endl;
        cout << "3) Liste personnes" << endl;
        cout << "4) Quitter" << endl;
        cin >> choix;

        switch (choix)
        {
            case 1:
                int jour, mois, annee;
                cout << "jour : ";
                cin >> jour;
                cout << "mois : ";
                cin >> mois;
                cout << "annee : ";
                cin >> annee;
                repertoireRdv.modifierDate(rdv, jour, mois, annee);
                break;
            case 2:
                int heureDebut, heureFin;
                cout << "heure debut : ";
                cin >> heureDebut;
                cout << "heure fin : ";
                cin >> heureFin;
                repertoireRdv.modifierHeure(rdv, heureDebut, heureFin);
                break;
            case 3:
            {
                vector<string> personnes(4);
                personnes[0]="gherardi";
                personnes[1]="carasco";
                personnes[2]="hindie";
                personnes[3]= "agudo";
                repertoireRdv.modifierListePersonnes(rdv, personnes);
                break;
            }
            case 4:
                b = false;
                break;
            default:
                break;
        }
    }
/*
    repertoireRdv.afficher("rdv1", &repertoirePersonne);
    cout << endl;

    repertoireRdv.afficher("rdv2", &repertoirePersonne);
    cout << endl;
*/

}
