#include "chainonpersonne.h"
#include <string>
using namespace std;

/**
  Construit un objet chainonPersonne
  @param[in] nom, prenom, numero, email - des string
*/
chainonPersonne::chainonPersonne(string nom, string prenom, string numero, string email):cp_nom{nom}, cp_prenom{prenom}, cp_numero{numero}, cp_email{email}
{}

/**
  Construit un objet chainonPersonne par defaut
*/
chainonPersonne::~chainonPersonne()
{}
