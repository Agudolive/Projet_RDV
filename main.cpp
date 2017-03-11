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
    repertoirePersonne.ajouter("Lefebvre","Kyllian", "06.92.38.77.78", "kyllianlefebvre@fakeemail.tld");
    repertoirePersonne.ajouter("Texier","Lilian", "06.88.19.80.00", "liliantexier@fakeemail.tld");
    repertoirePersonne.ajouter("Evrard","Juliette", "06.67.34.92.88", "julietteevrard@fakeemail.tld");
    repertoirePersonne.ajouter("Grenier","Juliette", "06.34.10.68.70", "clemencegrenier@fakeemail.tld");
    repertoirePersonne.ajouter("Simon","Mathieu", "06.33.15.83.95", "mathieusimon@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Clément", "06.79.66.76.53", "clementmathieu@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Florentin", "06.08.32.08.45", "florentinrichard@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Théo", "06.36.60.14.14", "theoruiz@fakeemail.tld");
    repertoirePersonne.ajouter("Ferre","Mathis", "06.52.35.59.69", "mathisferre@fakeemail.tld");
    repertoirePersonne.ajouter("Dumas","Quentin", "06.71.23.98.10", "quentindumas@fakeemail.tld");
    repertoirePersonne.afficher();
    cout << "___________________________________________" << endl << endl;

    //création d'un vecteur string de participants a passer au constructeur
    //liste rendez vous qui appelle lui meme le constructeur d'un nouveau chainon
    vector<vector<string>> p1;
    p1.resize(2, vector<string>(2));
    p1[0][0]="Lefebvre";
    p1[0][1]="Kyllian";
    p1[1][0]="Ruiz";
    p1[1][1]="Clément";

    vector<vector<string>> p2;
    p2.resize(3, vector<string>(2));
    p2[0][0]="Ruiz";
    p2[0][1]="Clément";
    p2[1][0]="Ruiz";
    p2[1][1]="Florentin";
    p2[2][0]="Dumas";
    p2[2][1]="Quentin";

    //liste de rendez vous contenant 2 rendez vous
    LCRdv repertoireRdv;
    repertoireRdv.ajouter("rdv1", 28, 1, 2016, 15, 16, p1);
    repertoireRdv.ajouter("rdv2", 2, 3, 2017, 11, 12, p2);


    //affichage de la liste de rdv
    cout << "répertoire rdv :" << endl;
    repertoireRdv.afficherListeRdv();
    cout << endl << "___________________________________________" << endl << endl;

    //affichage de chaque rdv
    repertoireRdv.afficher("rdv1", &repertoirePersonne);
    cout << endl;

    repertoireRdv.afficher("rdv2", &repertoirePersonne);
    cout << endl << "___________________________________________" << endl << endl;


    //afficher tous les rdv entre 2 dates     int jour1, int mois1, int annee1, int jour2, int mois2, int annee2
    repertoireRdv.afficherEntreDates(6,12,2016,11,9,2018);
    cout << endl;
    repertoireRdv.afficherEntreDates(11,1,2016,27,9,2017);
    cout << endl << "___________________________________________" << endl << endl;

    //affachier tous les rendez-vous d'une personne
    cout << "rendez-vous de Ruiz CLément :" << endl;
    repertoireRdv.afficherPourPersonne("Ruiz", "Clément", &repertoirePersonne);
    cout << endl;
    cout << "rendez-vous de Dumas Quentin :" << endl;
    repertoireRdv.afficherPourPersonne("Dumas", "Quentin", &repertoirePersonne);
    cout << "___________________________________________" << endl << endl;

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
                vector<vector<string>> personnes;
                personnes.resize(4, vector<string>(2));
                personnes[0][0]="Evrard";
                personnes[0][1]="Juliette",
                personnes[1][0]="Grenier";
                personnes[1][1]="Juliette",
                personnes[2][0]="Simon";
                personnes[2][1]="Mathieu",
                personnes[3][0]="Ferre";
                personnes[3][1]="Mathis",
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

    repertoireRdv.afficher("rdv1", &repertoirePersonne);
    cout << endl;

    repertoireRdv.afficher("rdv2", &repertoirePersonne);
    cout << "___________________________________________" << endl << endl;



}
