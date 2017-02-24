#include "chainonpersonne.h"
#include <string>
using namespace std;

chainonPersonne::chainonPersonne(string nom, string prenom, string numero, string email):cp_nom{nom}, cp_prenom{prenom}, cp_numero{numero}, cp_email{email}
{
}

chainonPersonne::~chainonPersonne()
{
  delete cp_suivant;
  delete this;
}
