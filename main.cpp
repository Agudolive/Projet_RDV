#include <string>
#include "lcpersonne.h"
#include "chainonpersonne.h"

using namespace std;

int main()
{
    LCPersonne test;
    test.ajouter("hzerezr","utikyuki", "666666666", "eifnopien@zefhzeuf.fr");
    test.ajouter("gzerbzetrb","trynry", "666aezf666", "eifazefazeaefhzeuf.fr");
    test.ajouter("azrtgzrt","azezrea", "666666666", "eifnopien@zefhzeuf.fr");
    test.ajouter("czergzerg","xvsdfv", "666aezf666", "eifazefazeaefhzeuf.fr");
    test.supprimer("azrtgzrt","azezrea");
    test.afficher();

    return 0;
}
