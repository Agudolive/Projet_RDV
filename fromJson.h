#ifndef PROJET_RDV_FROMJSON_H
#define PROJET_RDV_FROMJSON_H
#include "json.hpp"
#include "lcpersonne.h"
#include "lcrdv.h"

using json = nlohmann::json;
using namespace std;

class fromJson {
public:

    fromJson(LCPersonne *lcp, LCRdv *lcr);
    fromJson();

	void getRdv();
    void        getRdv(LCRdv &repertoire);
    void        saveRdv();
	void        saveRdv(LCRdv *repertoire);

    void getRepertoire();
    void        getRepertoire(LCPersonne &repertoire);
    void        saveRepertoire();
    void        saveRepertoire(LCPersonne &repertoire);


private:

    LCPersonne*  fj_repertoirePersonne;
    LCRdv*       fj_repertoireRdv;


};


#endif //PROJET_RDV_FROMJSON_H
