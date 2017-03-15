//
// Created by root on 12/03/17.
//

#include <fstream>
#include "fromJson.h"
#include "json.hpp"
#include "chainonpersonne.h"

fromJson::fromJson(LCPersonne &lcp, LCRdv &lcr) : fj_repertoirePersonne{lcp}, fj_repertoireRdv{lcr}
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

    LCPersonne   fj_repertoirePersonne;
    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( unsigned i = 0; i < data.size(); i++ )
    {
        fj_repertoirePersonne.ajouter(
                data[i]["nom"],
                data[i]["prenom"],
                data[i]["numero"],
                data[i]["email"]

        );
    }

    return fj_repertoirePersonne;

}

// Sauvegarde la liste de personnes dans le fichier repertoire.json
void fromJson::saveRepertoire() {
    ofstream output_json("/root/Documents/Projet_RDV/repertoire.json");

    chainonPersonne *crt = fj_repertoirePersonne.getTete();

    json array;

    while (crt)
    {
        json tmp;

        tmp["email"]    =   fj_repertoirePersonne.getEmail(crt);
        tmp["nom"]      =   fj_repertoirePersonne.getNom(crt);
        tmp["prenom"]   =   fj_repertoirePersonne.getPrenom(crt);
        tmp["numero"]   =   fj_repertoirePersonne.getNumero(crt);

        array.push_back(tmp);
        crt = fj_repertoirePersonne.getSuivant(crt);

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
/*
// Retourne la liste de rendez vous contenue dans le fichier rdv.json
LCRdv fromJson::getRdv()
{
    ifstream input_json("/root/Documents/Projet_RDV/rdv.json");

    LCRdv   fj_repertoireRdv;
    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( unsigned i = 0; i < data.size(); i++ )
    {
        vector<vector<string>> participants = data[i]["participants"];


        fj_repertoireRdv.ajouter(
                data[i]["libelle"],
                data[i]["jour"],
                data[i]["mois"],
                data[i]["annee"],
                data[i]["heureDebut"],
                data[i]["heureFin"],
                participants
        );
    }

    return fj_repertoireRdv;
}


// Sauvegarde la liste de rendez vous dans le fichier rdv.json
void fromJson::saveRdv() {
    ofstream output_json("/root/Documents/Projet_RDV/rdv.json");

    chainonRdv *crt = fj_repertoireRdv.l_tete;

    json array;

    while ( crt != nullptr )
    {
        json tmp;
        json participants;

        tmp["libelle"]      =   fj_repertoireRdv.getLibelle(crt);
        tmp["jour"]         =   fj_repertoireRdv.getJour(crt);
        tmp["mois"]         =   fj_repertoireRdv.getMois(crt);
        tmp["annee"]        =   fj_repertoireRdv.getAnnee(crt);
        tmp["heureDebut"]   =   fj_repertoireRdv.getHeureDebut(crt);
        tmp["heureFin"]     =   fj_repertoireRdv.getHeureFin(crt);

        for ( int i = 0; i < fj_repertoireRdv.getParticipants(crt).size(); i++ )
            participants.push_back(fj_repertoireRdv.getParticipants(crt)[i]);

        tmp["participants"] =   participants;

        array.push_back(tmp);
        crt = fj_repertoireRdv.getSuivant(crt);
    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
}
*/
