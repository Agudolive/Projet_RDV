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

        tmp["email"]    =   repertoirePersonne.getEmail(*cp);
        tmp["nom"]      =   repertoirePersonne.getNom(*cp);
        tmp["prenom"]   =   repertoirePersonne.getNumero(*cp);
        tmp["numero"]   =   repertoirePersonne.getEmail(*cp);

        array.push_back(tmp);
        cp = repertoirePersonne.getSuivant(cp);

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

        tmp["email"]    =   repertoire.getEmail(*cp);
        tmp["nom"]      =   repertoire.getNom(*cp);
        tmp["prenom"]   =   repertoire.getNumero(*cp);
        tmp["numero"]   =   repertoire.getEmail(*cp);

        array.push_back(tmp);
        cp = repertoire.getSuivant(cp);

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

        tmp["libelle"]      =   repertoireRdv.getLibelle(*cr);
        tmp["jour"]         =   repertoireRdv.getJour(*cr);
        tmp["mois"]         =   repertoireRdv.getMois(*cr);
        tmp["annee"]        =   repertoireRdv.getAnnee(*cr);
        tmp["heureDebut"]   =   repertoireRdv.getHeureDebut(*cr);
        tmp["heureFin"]     =   repertoireRdv.getHeureFin(*cr);

        for ( int i = 0; i < repertoireRdv.getParticipants(*cr).size(); i++ )
            participants.push_back(repertoireRdv.getParticipants(*cr)[i]);

        tmp["participants"] =   participants;

        array.push_back(tmp);
        cr = repertoireRdv.getSuivant(*cr);
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

        tmp["libelle"]      =   repertoire.getLibelle(*cr);
        tmp["jour"]         =   repertoire.getJour(*cr);
        tmp["mois"]         =   repertoire.getMois(*cr);
        tmp["annee"]        =   repertoire.getAnnee(*cr);
        tmp["heureDebut"]   =   repertoire.getHeureDebut(*cr);
        tmp["heureFin"]     =   repertoire.getHeureFin(*cr);

        for ( int i = 0; i < repertoire.getParticipants(*cr).size(); i++ )
            participants.push_back(repertoire.getParticipants(*cr)[i]);

        tmp["participants"] =   participants;

        array.push_back(tmp);
        cr = repertoire.getSuivant(*cr);
    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
}