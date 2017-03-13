//
// Created by root on 12/03/17.
//

#include <fstream>
#include "fromJson.h"
#include "json.hpp"
#include "chainonpersonne.h"

fromJson::fromJson(LCPersonne &lcp, LCRdv &lcr) : repertoirePersonne{lcp}, repertoireRdv{lcr}
    { }

fromJson::fromJson()
    { }

/*
 * -------------------
 * ---- PERSONNES ----
 * -------------------
 */

// Retourne la liste de personnes contenue dans le fichier repertoire.json
LCPersonne fromJson::getRepertoire()
{
    ifstream input_json("/root/Documents/Projet_RDV/repertoire.json");

    LCPersonne   repertoirePersonne;
    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( int i = 0; i < data.size(); i++ )
    {
        repertoirePersonne.ajouter(
                data[i]["nom"],
                data[i]["prenom"],
                data[i]["numero"],
                data[i]["email"]

        );
    }

    return repertoirePersonne;

}


// Retourne la liste de personnes contenue dans le fichier repertoire.json
// et la place dans la liste de personnes repertoire passé en paramètre
void fromJson::getRepertoire(LCPersonne &repertoire)
{
    ifstream input_json("/root/Documents/Projet_RDV/repertoire.json");

    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( int i = 0; i < data.size(); i++ )
    {
        repertoire.ajouter(
                data[i]["nom"],
                data[i]["prenom"],
                data[i]["numero"],
                data[i]["email"]

        );
    }
}

// Sauvegarde la liste de personnes dans le fichier repertoire.json
void fromJson::saveRepertoire() {
    ofstream output_json("/root/Documents/Projet_RDV/repertoire.json");

    chainonPersonne *cp = repertoirePersonne.l_tete;

    json array;

    while ( cp != nullptr )
    {
        json tmp;

        tmp["email"]    =   cp->cp_email;
        tmp["nom"]      =   cp->cp_nom;
        tmp["prenom"]   =   cp->cp_prenom;
        tmp["numero"]   =   cp->cp_numero;

        array.push_back(tmp);
        cp = cp->cp_suivant;

    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }

}

// Sauvegarde la liste de personnes passée en paramètre dans repertoire.json
void fromJson::saveRepertoire(LCPersonne &repertoire) {
    ofstream output_json("/root/Documents/Projet_RDV/repertoire.json");

    chainonPersonne *cp = repertoire.l_tete;

    json array;

    while ( cp != nullptr )
    {
        json tmp;

        tmp["email"]    =   cp->cp_email;
        tmp["nom"]      =   cp->cp_nom;
        tmp["prenom"]   =   cp->cp_prenom;
        tmp["numero"]   =   cp->cp_numero;

        array.push_back(tmp);
        cp = cp->cp_suivant;

    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }

}

/*
 * -------------------
 * --- RENDEZ VOUS ---
 * -------------------
 */

// Retourne la liste de rendez vous contenue dans le fichier rdv.json
LCRdv fromJson::getRdv()
{
    ifstream input_json("/root/Documents/Projet_RDV/rdv.json");

    LCRdv   repertoireRdv;
    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( int i = 0; i < data.size(); i++ )
    {
        vector<string> participants = data[i]["participants"];


        repertoireRdv.ajouter(
                data[i]["libelle"],
                data[i]["jour"],
                data[i]["mois"],
                data[i]["annee"],
                data[i]["heureDebut"],
                data[i]["heureFin"],
                participants
        );
    }

    return repertoireRdv;
}

// Retourne la liste de rendez vous contenue dans le fichier rdv.json
// et la place dans la liste de rendez vous repertoire passé en paramètre
void fromJson::getRdv(LCRdv &repertoire)
{
    ifstream input_json("/root/Documents/Projet_RDV/rdv.json");

    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( int i = 0; i < data.size(); i++ )
    {
        vector<string> participants = data[i]["participants"];


        repertoire.ajouter(
                data[i]["libelle"],
                data[i]["jour"],
                data[i]["mois"],
                data[i]["annee"],
                data[i]["heureDebut"],
                data[i]["heureFin"],
                participants
        );
    }
}


// Sauvegarde la liste de rendez vous dans le fichier rdv.json
void fromJson::saveRdv() {
    ofstream output_json("/root/Documents/Projet_RDV/rdv.json");

    chainonRdv *cr = repertoireRdv.l_tete;

    json array;

    while ( cr != nullptr )
    {
        json tmp;
        json participants;

        tmp["libelle"]      =   cr->cr_libelle;
        tmp["jour"]         =   cr->cr_jour;
        tmp["mois"]         =   cr->cr_mois;
        tmp["annee"]        =   cr->cr_annee;
        tmp["heureDebut"]   =   cr->cr_heureDebut;
        tmp["heureFin"]     =   cr->cr_heureFin;

        for ( int i = 0; i < cr->cr_participants.size(); i++ )
            participants.push_back(cr->cr_participants[i]);

        tmp["participants"] =   participants;

        array.push_back(tmp);
        cr = cr->cr_suivant;
    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
}

// Sauvegarde la liste de rendez vous passée en paramètre dans rdv.json
void fromJson::saveRdv(LCRdv &repertoire) {
    ofstream output_json("/root/Documents/Projet_RDV/rdv.json");

    chainonRdv *cr = repertoire.l_tete;

    json array;

    while ( cr != nullptr )
    {
        json tmp;
        json participants;

        tmp["libelle"]      =   cr->cr_libelle;
        tmp["jour"]         =   cr->cr_jour;
        tmp["mois"]         =   cr->cr_mois;
        tmp["annee"]        =   cr->cr_annee;
        tmp["heureDebut"]   =   cr->cr_heureDebut;
        tmp["heureFin"]     =   cr->cr_heureFin;

        for ( int i = 0; i < cr->cr_participants.size(); i++ )
            participants.push_back(cr->cr_participants[i]);

        tmp["participants"] =   participants;

        array.push_back(tmp);
        cr = cr->cr_suivant;
    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
}