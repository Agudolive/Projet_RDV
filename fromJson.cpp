//
// Created by root on 12/03/17.
//

#include <fstream>
#include "fromJson.h"
#include "json.hpp"
#include "chainonpersonne.h"

/**
  Construit un objet json pour sauvegarder/charger des données
  @param[in] lcp, lcr - les répertoires de rendez-vous et de personnes a remplir ou sauvegarder
*/
fromJson::fromJson(LCPersonne *lcp, LCRdv *lcr) : fj_repertoirePersonne{lcp}, fj_repertoireRdv{lcr}
{ }

/**
  Constructeur par defaut de l'objet
*/
fromJson::fromJson()
{ }


/**
  Retourne la liste de personnes contenue dans le fichier repertoire.json
  @param[out] fj_repertoirePersonne - le répertoire de personnes rempli
*/
void fromJson::getRepertoire()
{
    ifstream input_json("repertoire.json");

    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( unsigned i = 0; i < data.size(); i++ )
    {
        //cout << data[i]["email"] << endl;

        fj_repertoirePersonne->ajouter(
                data[i]["nom"],
                data[i]["prenom"],
                data[i]["numero"],
                data[i]["email"]

        );
    }

}

/**
  Sauvegarde la liste de personnes dans le fichier repertoire.json
  @param[in] fj_repertoirePersonne - le répertoire de personnes à sauvegarder
*/
void fromJson::saveRepertoire() {
    ofstream output_json("repertoire.json");

    chainonPersonne *crt = fj_repertoirePersonne->getTete();

    json array;

    while (crt)
    {
        json tmp;
        //cout << fj_repertoirePersonne->getEmail(crt) << endl;

        tmp["email"]    =   fj_repertoirePersonne->getEmail(crt);
        tmp["nom"]      =   fj_repertoirePersonne->getNom(crt);
        tmp["prenom"]   =   fj_repertoirePersonne->getPrenom(crt);
        tmp["numero"]   =   fj_repertoirePersonne->getNumero(crt);

        array.push_back(tmp);
        crt = fj_repertoirePersonne->getSuivant(crt);

    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
    else
    {
        cout << "Erreur save" << endl;
    }

}

/**
  Retourne la liste de rendez vous contenue dans le fichier rdv.json
  @param[in] fj_repertoireRdv - le répertoire de rendez-vous rempli
*/
void fromJson::getRdv()
{
    ifstream input_json("rdv.json");

    json    data;

    if (input_json.is_open())
    {
        input_json >> data;
        input_json.close();
    }

    for ( unsigned i = 0; i < data.size(); i++ )
    {
        vector<vector<string>> participants;

		for ( unsigned j = 0; j < data[i]["participants"].size(); j++ )
		{
			vector<string> tmp_participants;

			tmp_participants.push_back(data[i]["participants"][j][0]);
			tmp_participants.push_back(data[i]["participants"][j][1]);

			participants.push_back(tmp_participants);
		}

        //cout << data[i]["libelle"] << endl;

        fj_repertoireRdv->ajouter(
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

/**
  Sauvegarde la liste de rendez vous dans le fichier rdv.json
  @param[in] fj_repertoireRdv - le répertoire de rendez-vous à sauvegarder
*/
//
void fromJson::saveRdv() {
    ofstream output_json("rdv.json");

    chainonRdv *crt = fj_repertoireRdv->getTete();

    json array;

    while ( crt != nullptr )
    {
        json tmp;
        json participants;

        tmp["libelle"]      =   fj_repertoireRdv->getLibelle(crt);
        tmp["jour"]         =   fj_repertoireRdv->getJour(crt);
        tmp["mois"]         =   fj_repertoireRdv->getMois(crt);
        tmp["annee"]        =   fj_repertoireRdv->getAnnee(crt);
        tmp["heureDebut"]   =   fj_repertoireRdv->getHeureDebut(crt);
        tmp["heureFin"]     =   fj_repertoireRdv->getHeureFin(crt);

        for ( unsigned i = 0; i < fj_repertoireRdv->getParticipants(crt).size(); i++ )
		{
			json tmp_participants;

			tmp_participants.push_back(fj_repertoireRdv->getParticipants(crt)[i][0]);
			tmp_participants.push_back(fj_repertoireRdv->getParticipants(crt)[i][1]);
            participants.push_back(tmp_participants);
		}


        tmp["participants"]	=	participants;

        array.push_back(tmp);
        crt = fj_repertoireRdv->getSuivant(crt);
    }

    if ( output_json.is_open() )
    {
        output_json << array;
        output_json.close();
    }
}
