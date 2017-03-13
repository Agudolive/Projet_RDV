#include "affichage.h"

using namespace std;

affichage::affichage(){}

affichage::affichage(interface* d_interface) : a_interface{d_interface}{
}


void affichage::demarrer(){

  cout << "# Bienvenue dans votre assistant virtuel de rendez-vous #" << endl;
  menuPrincipale();

}

void affichage::menuPrincipale(){

  int i;
  cout << endl;
  cout << "Que voulez vous faire : " << endl;
  cout << endl;
  cout << "1) Personnes" << endl;
  cout << endl;
  cout << "2) Rendez-vous" << endl;
  cout << endl;
  cout << "3) Importer fichier JSON" << endl;
  cout << endl;
  cout << "4) Autre" << endl;
  cout << endl;
  cout << "5) Quitter" << endl;
  cout << endl;
  cin >> i;

  if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5)
    menuPrincipale();

  switch (i) {
    case 1:
      menuPersonne();
      break;
    case 2:
      menuRDV();
      break;
    case 3:
      break;
    case 4:
      menuAutre();
      break;
    case 5:
      std::_Exit;
      break;
  }
}

void affichage::menuPersonne(){

  int i;
  cout << endl;
  cout << "Que voulez vous faire : " << endl;
  cout << endl;
  cout << "1) Ajouter une personne" << endl;
  cout << endl;
  cout << "2) Supprimer une personne" << endl;
  cout << endl;
  cout << "3) Modifier une personne" << endl;
  cout << endl;
  cout << "4) Retour" << endl;
  cout << endl;
  cin >> i;

  if(i != 1 && i != 2 && i != 3 && i != 4)
    menuPersonne();

  switch (i) {
    case 1:
        a_interface->ajouterPersonne();
      break;
    case 2:
        a_interface->supprimerPersonne();
      break;
    case 3:
        //faire sous menu
        //a_interface->modifierPersonne();
      break;
    case 4:
      menuPrincipale();
      break;
  }
}

void affichage::menuRDV(){

  int i;
  cout << endl;
  cout << "Que voulez vous faire : " << endl;
  cout << endl;
  cout << "1) Ajouter un rendez-vous" << endl;
  cout << endl;
  cout << "2) Supprimer un rendez-vous" << endl;
  cout << endl;
  cout << "3) Modifier un rendez-vous" << endl;
  cout << endl;
  cout << "4) Retour" << endl;
  cout << endl;
  cin >> i;

  if(i != 1 && i != 2 && i != 3 && i != 4)
    menuRDV();

  switch (i) {
    case 1:
      a_interface->ajouterRdv();
      break;
    case 2:
      a_interface->supprimerRdv();
      break;
    case 3:
      //faire un sous menu
      //a_interface->modifierRdv();
      break;
    case 4:
      menuPrincipale();
      break;
  }
}

void affichage::menuAutre(){
}
