#include "chainonpersonne.h"
#include <string>
using namespace std;

chainonPersonne::chainonPersonne(string nom, string prenom, string numero, string email):c_nom{nom}, c_prenom{prenom}, c_numero{numero}, c_email{email}
{
}

chainonPersonne::~chainonPersonne()
{
  delete c_suivant;
  delete this;
}
