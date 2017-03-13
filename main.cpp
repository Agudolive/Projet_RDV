#include <string>
#include "lcpersonne.h"
#include "chainonpersonne.h"
#include "lcrdv.h"
#include "chainonrdv.h"
#include "fromJson.h"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    //création d'un répertoire de personnes


    fromJson js;
    LCPersonne repertoirePersonne = js.getRepertoire();
    LCRdv repertoireRdv = js.getRdv();

    repertoirePersonne.afficher();
}
