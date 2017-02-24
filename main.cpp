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
    /*LCPersonne test;
    test.ajouter("hzerezr","utikyuki", "666666666", "eifnopien@zefhzeuf.fr");
    test.ajouter("gzerbzetrb","trynry", "666aezf666", "eifazefazeaefhzeuf.fr");
    test.ajouter("azrtgzrt","azezrea", "666666666", "eifnopien@zefhzeuf.fr");
    test.ajouter("czergzerg","xvsdfv", "666aezf666", "eifazefazeaefhzeuf.fr");
    test.supprimer("azrtgzrt","azezrea");
    test.afficher();*/

    vector<string> p1(1);
    p1[0]="Aa";
    vector<string> p2(1);
    p2[0]="Ba";
    vector<string> p3(1);
    p3[0]="Ca";

    LCRdv test;
    test.ajouter("azert", 1, 1, 1, 1, 2, p1);
    test.ajouter("yuiop", 2, 2, 2, 2, 3, p2);
    test.ajouter("qsdfg", 3, 3, 3, 3, 4, p3);

    test.supprimer("qsdfg");

    test.afficher();

}
