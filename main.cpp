#include "lcpersonne.h"
#include "lcrdv.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    //création d'un répertoire de personnes
    LCPersonne repertoirePersonne;
    cout << "répertoire personnes :" << endl;
    repertoirePersonne.ajouter("Zer","A","0","@");
    repertoirePersonne.ajouter("Zer","B","0","@");
    repertoirePersonne.ajouter("Zer","C","0","@");
    repertoirePersonne.ajouter("Lefebvre","Kyllian", "06.92.38.77.78", "kyllianlefebvre@fakeemail.tld");
    repertoirePersonne.ajouter("Texier","Lilian", "06.88.19.80.00", "liliantexier@fakeemail.tld");
    repertoirePersonne.ajouter("Evrard","Juliette", "06.67.34.92.88", "julietteevrard@fakeemail.tld");
    repertoirePersonne.ajouter("Grenier","Juliette", "06.34.10.68.70", "clemencegrenier@fakeemail.tld");
    repertoirePersonne.ajouter("Simon","Mathieu", "06.33.15.83.95", "mathieusimon@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Florentin", "06.79.66.76.53", "clementmathieu@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Clément", "06.08.32.08.45", "florentinrichard@fakeemail.tld");
    repertoirePersonne.ajouter("Ruiz","Théo", "06.36.60.14.14", "theoruiz@fakeemail.tld");

    repertoirePersonne.ajouter("Rui","Théo", "06.36.60.14.14", "theoruiz@fakeemail.tld");
    repertoirePersonne.ajouter("Rui","Adegrth", "06.36.60.14.14", "theoruiz@fakeemail.tld");
    repertoirePersonne.ajouter("Rui","Zazethrjukhéo", "06.36.60.14.14", "theoruiz@fakeemail.tld");

    repertoirePersonne.ajouter("Ferre","Mathis", "06.52.35.59.69", "mathisferre@fakeemail.tld");
    repertoirePersonne.ajouter("Dumas","Quentin", "06.71.23.98.10", "quentindumas@fakeemail.tld");
    repertoirePersonne.ajouter("Vaillant","Tristan","0","@");
repertoirePersonne.ajouter("Daniel","Alicia","0","@");
repertoirePersonne.ajouter("Chambon","Mohamed","0","@");
repertoirePersonne.ajouter("Benard","Charlotte","0","@");
repertoirePersonne.ajouter("Jacquemin","Davy","0","@");
repertoirePersonne.ajouter("Caron","Tom","0","@");
repertoirePersonne.ajouter("Descamps","Mathilde","0","@");
repertoirePersonne.ajouter("Carre","Valentine","0","@");
repertoirePersonne.ajouter("Chartier","Erwan","0","@");
repertoirePersonne.ajouter("Morin","Corentin","0","@");
repertoirePersonne.ajouter("Devaux","Élisa","0","@");
repertoirePersonne.ajouter("Vasseur","Killian","0","@");
repertoirePersonne.ajouter("Maillet","Françoise","0","@");
repertoirePersonne.ajouter("Marchand","Alexia","0","@");
repertoirePersonne.ajouter("Bernard","Cédric","0","@");
repertoirePersonne.ajouter("Leblond","Mathis","0","@");
repertoirePersonne.ajouter("Colin","Florentin","0","@");
repertoirePersonne.ajouter("Carpentier","Charlotte","0","@");
repertoirePersonne.ajouter("Carpentier","Davy","0","@");
repertoirePersonne.ajouter("Guillot","Clément","0","@");
repertoirePersonne.ajouter("Millot","Florentin","0","@");
repertoirePersonne.ajouter("Fortin","Élise","0","@");
repertoirePersonne.ajouter("Lecocq","Titouan","0","@");
repertoirePersonne.ajouter("Mercier","Nina","0","@");
repertoirePersonne.ajouter("Marin","Timothée","0","@");
repertoirePersonne.ajouter("Clerc","Hugo","0","@");
repertoirePersonne.ajouter("Barbier","Gaspard","0","@");
repertoirePersonne.ajouter("Rault","Clotilde","0","@");
repertoirePersonne.ajouter("Riviere","Yohan","0","@");
repertoirePersonne.ajouter("Morel","Dorian","0","@");
repertoirePersonne.ajouter("Delattre","Dorian","0","@");
repertoirePersonne.ajouter("Lebrun","Arthur","0","@");
repertoirePersonne.ajouter("Dias","Adrian","0","@");
repertoirePersonne.ajouter("Renault","Titouan","0","@");
repertoirePersonne.ajouter("Andrieu","Margaux","0","@");
repertoirePersonne.ajouter("Jacob","Lutécia","0","@");
repertoirePersonne.ajouter("Dupuis","Élisa","0","@");
repertoirePersonne.ajouter("Fleury","Amélie","0","@");
repertoirePersonne.ajouter("Jacquemin","Jordan","0","@");
repertoirePersonne.ajouter("Bertrand","Evan","0","@");
repertoirePersonne.ajouter("Dumas","Maéva","0","@");
repertoirePersonne.ajouter("Durant","Maéva","0","@");
repertoirePersonne.ajouter("Prevost","Maïwenn","0","@");
repertoirePersonne.ajouter("Merlin","Titouan","0","@");
repertoirePersonne.ajouter("Munoz","Chaïma","0","@");
repertoirePersonne.ajouter("Breton","Jordan","0","@");
repertoirePersonne.ajouter("Mahe","Émilie","0","@");
repertoirePersonne.ajouter("Lemoine","Élise","0","@");
repertoirePersonne.ajouter("Granger","Lorenzo","0","@");
repertoirePersonne.ajouter("Guignard","Éloïse","0","@");
repertoirePersonne.ajouter("Coulon","Florian","0","@");
repertoirePersonne.ajouter("Le roy","Cédric","0","@");
repertoirePersonne.ajouter("Louis","Renaud","0","@");
repertoirePersonne.ajouter("Noel","Fabrice","0","@");
repertoirePersonne.ajouter("Perrot","Marwane","0","@");
repertoirePersonne.ajouter("Maurice","Quentin","0","@");
repertoirePersonne.ajouter("Leclerc","Davy","0","@");
repertoirePersonne.ajouter("Millot","Noah","0","@");
repertoirePersonne.ajouter("Fischer","Théo","0","@");
repertoirePersonne.ajouter("Sanchez","Nolan","0","@");
repertoirePersonne.ajouter("Andrieu","Jade","0","@");
repertoirePersonne.ajouter("Coste","Luna","0","@");
repertoirePersonne.ajouter("Boulay","Adam","0","@");
repertoirePersonne.ajouter("Normand","Rose","0","@");
repertoirePersonne.ajouter("Leon","Gabin","0","@");
repertoirePersonne.ajouter("Pichon","Samuel","0","@");
repertoirePersonne.ajouter("Marchand","Kevin","0","@");
repertoirePersonne.ajouter("Diaz","Mélanie","0","@");
repertoirePersonne.ajouter("Ferre","Marine","0","@");
repertoirePersonne.ajouter("Adam","Valentin","0","@");
repertoirePersonne.ajouter("Dupont","Yasmine","0","@");
repertoirePersonne.ajouter("Gregoire","Baptiste","0","@");
repertoirePersonne.ajouter("Ribeiro","Agathe","0","@");
repertoirePersonne.ajouter("Bouquet","Catherine","0","@");
repertoirePersonne.ajouter("Dujardin","Simon","0","@");
repertoirePersonne.ajouter("Rossignol","Lola","0","@");
repertoirePersonne.ajouter("Faure","Jérémy","0","@");
repertoirePersonne.ajouter("Ferrer","Zoé","0","@");
repertoirePersonne.ajouter("Castel","Cloé","0","@");
repertoirePersonne.ajouter("Barre","Grégory","0","@");
repertoirePersonne.ajouter("Guillet","Léonard","0","@");
repertoirePersonne.ajouter("Ferry","Lana","0","@");
repertoirePersonne.ajouter("Dos santos","Pierre","0","@");
repertoirePersonne.ajouter("Flament","Ambre","0","@");
repertoirePersonne.ajouter("Girault","Maïwenn","0","@");
repertoirePersonne.ajouter("Serre","Anthony","0","@");
repertoirePersonne.ajouter("Brunet","Maelys","0","@");
repertoirePersonne.ajouter("Bazin","Anaëlle","0","@");
repertoirePersonne.ajouter("Deschamps","Charlotte","0","@");
repertoirePersonne.ajouter("Lombard","Lauriane","0","@");
repertoirePersonne.ajouter("Girard","Katell","0","@");
repertoirePersonne.ajouter("Alves","Lilian","0","@");
repertoirePersonne.ajouter("Riou","Emma","0","@");
repertoirePersonne.ajouter("Hamel","Thomas","0","@");
repertoirePersonne.ajouter("Boyer","Nolan","0","@");
repertoirePersonne.ajouter("Schneider","Carla","0","@");
repertoirePersonne.ajouter("Muller","Lucie","0","@");
repertoirePersonne.ajouter("Pereira","Françoise","0","@");
repertoirePersonne.ajouter("Brunel","Kyllian","0","@");
repertoirePersonne.ajouter("Lafon","Rémi","0","@");



    repertoirePersonne.afficher();
    //repertoirePersonne.supprimer("Dumas", "Quentin");
    //repertoirePersonne.supprimer("Ruiz", "Florentin");
    //repertoirePersonne.supprimer("Texier", "Lilian");
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
    repertoireRdv.ajouter("rdv3", 1, 1, 1, 1, 1, p2);


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

    repertoirePersonne.supprimer("Lefebvre", "Kyllian", &repertoireRdv);
    repertoirePersonne.supprimer("Grenier", "Juliette", &repertoireRdv);
    repertoirePersonne.supprimer("Ruiz", "Théo", &repertoireRdv);

    cout << "___________________________________________" << endl << endl;

    repertoirePersonne.afficherPersonne("Lefebvre", "Kyllian");
    repertoirePersonne.modifierNumero("Lefebvre", "Kyllian", "00.00.00.00.00");
    repertoirePersonne.modifierEmail("Lefebvre", "Kyllian", "aaaaaaabbbbbbbb@ccccccccc.eee");
    repertoirePersonne.afficherPersonne("Lefebvre", "Kyllian");

}
