#include <iostream>
#include <string>
#include "eliminator.h"

using namespace std;

int main()
{
	int retour = 0;
	int choix;
	char choixClass;
	while(retour != 1)
	{
		if (retour == 3)
		{
			retour = jouerChargeclssmnt();
		}
		else
		{
			cout << endl << "          ***Eliminator***          " << endl;
		
			cout << endl <<"#Menu Principal#" << endl << endl;
			cout << "1. Jouer" << endl;
			cout << "2. Jouer avec un fichier de grilles" << endl;
			cout << "3. Afficher les scores" << endl;
			cout << "4. Faire jouer l'ordinateur (en dev)" << endl;
			cout << "5. Quitter" << endl;
			cout << endl << "Votre choix : ";
			cin >> choix;
			
			switch(choix) 
			{
				case 1 : 
					retour = jouer();
					break;
				
				case 2 : 
					cout << endl << "Jouer avec les grilles du jeu (les scores ne sont valables que sur celles-ci) ? (o/n)";
					cin >> choixClass;
					switch(choixClass)
					{
						case 'o' : 
							retour = jouerChargeclssmnt();
							break;
							
						case 'n' :
							retour = jouerCharge();
							break;
							
						default : 
							cout << "Choix non valide";
							break;
					}
					break;
					
				case 3 : 
					afficherscores();
					break;
					
				case 4 :
					
					break;
					
				case 5 : 
					retour = 1;
					cout << endl << endl;
					break;
					
				default : 
					cout << "Choix non valide";
					break;
			}
		}
	}	
    return 0;
}
