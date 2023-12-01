#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "eliminator.h"
#include <ctime>
#include <sstream>

using namespace std;

//##############################################################################################################

void creationGrille(grille &grilleCrea, int &nbTours, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN)
{
    int i;
    int j;
    char choixRempli = ' ';

    cout << "Veuillez saisir le nombre de tours : " << endl;
    cin >> nbTours;

    cout <<"Les couleurs seront V (vert), R (rouge), B (bleu), J (jaune) et N (noir)." << endl;
    cout << "Veuillez saisir les elements de la grille 8x8 ( # : mur, E : vide, D : \"doughnut\",   A : finir de remplir la grille avec des #) : " << endl;

    //initialisation du "tour" de la grille
    for (i=0 ; i<=9 ; i++)
    {
        grilleCrea[0][i] = '#';
    }

    for (i=0 ; i<=9 ; i++)
    {
        grilleCrea[9][i] = '#';
    }

    for (i=0 ; i<=9 ; i++)
    {
        grilleCrea[i][0] = '#';
    }

    for (i=0 ; i<=9 ; i++)
    {
        grilleCrea[i][9] = '#';
    }

    //initialisation du "centre" de la grille

    for (i=1 ; i<=8 ; i++)
    {
        for (j=1 ; j<=8 ; j++)
        {
            grilleCrea[i][j] = ' ';
        }
    }



    //remplissage de la grille par l'utilisateur
    for (i=1 ; i<=8 ; i++)
    {
        for (j=1 ; j<=8 ; j++)
        {
            if (choixRempli != 'A')
            {
                cin >> choixRempli ;
                switch (choixRempli)
                {
                    case '#':
                        grilleCrea[i][j] = choixRempli;
                        break;

                    case 'E':
                        grilleCrea[i][j] = ' ';
                        break;

                    case 'A':
                        while (i<=8)
                        {
                            while (j<=8)
                            {
                                grilleCrea[i][j] = '#';
                                j++;
                            }
                            j = 1;
                            i++;

                        }
                        break;

                    case 'V':
                        grilleCrea[i][j] = 'V';
                        break;

                    case 'R':
                        grilleCrea[i][j] = 'R';
                        break;

                    case 'B':
                       	grilleCrea[i][j] = 'B';
                        break;

                    case 'J':
                       	grilleCrea[i][j] = 'J';
                        break;

                    case 'N':
                        grilleCrea[i][j] = 'N';
                        break;

                    case 'D':
                        grilleCrea[i][j] = 'D';
                        break;


                    default:
                        cout << "Ceci n'est pas un choix valide" << endl;
                        break;
                }
            }
        }
    }

}

//##############################################################################################################

void afficherGrille(grille grilleAffiche)
{
    int i;
    int j;


    for (i=0 ; i<=9 ; i++)
        {
            for (j=0 ; j<=9 ; j++)
            {
                cout <<grilleAffiche[i][j] << " ";
            }
            cout << endl;
        }
}

//##############################################################################################################

void deplacement (grille grilleJeu, grille grilleBase, int* nbTours, int nbToursTot, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN)
{
	char choix_direction;
	bool possible = false;
	bool fintour = false;
	int i,j;

	while (possible == false)
	{
		fintour = false;
		cout << "Quelle direction ? (H : haut, B : bas, G : gauche, D : droite, R : reset de la grille) : " << endl;
		cin >> choix_direction;

		while(fintour == false)
		{
			switch(choix_direction)
				{
					case 'H' :
						for (i=1 ; i<=8 ; i++)
						{
			    	        for (j=1 ; j<=8 ; j++)
				   	        {
			    	            if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D' || grilleJeu[i][j] == 'r' || grilleJeu[i][j] == 'v' || grilleJeu[i][j] == 'j' || grilleJeu[i][j] == 'b' || grilleJeu[i][j] == 'n' || grilleJeu[i][j] == 'd')
			    	            {	
			    	            	while(testdirection(grilleJeu, i, j, choix_direction) == true)
			    	            	{
										grilleJeu[i-1][j] = grilleJeu[i][j];
										grilleJeu[i][j] = ' ';
										possible = true;
										i--;
									}
								}
			    	            verif_elimination(grilleJeu, nbBoulesV, nbBoulesR, nbBoulesB, nbBoulesJ, nbBoulesN);   
			    	        }
						}
						elimination(grilleJeu);
						for (i=1 ; i<=8 ; i++)
						{
			    	        for (j=1 ; j<=8 ; j++)
				   	        {
				   	        	
				   	        	if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D')
				   	        	{
				   	        		if(testdirection(grilleJeu,i,j,choix_direction) == true)
					   	        	{
					   	        		fintour = false;
					   	        		break;
					   	        	}
					   	        	else
					   	        	{
					   	        		fintour = true;
					   	        	} 
					   	        }
					   	        else
					   	        {
					   	        	fintour = true;
					   	        }
				   	        }
				   	    }
						break;
	
					case 'B' :
						for (i=8 ; i>=1 ; i--)
						{
			    	        for (j=1 ; j<=8 ; j++)
			    	        {
			    	            if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D' || grilleJeu[i][j] == 'r' || grilleJeu[i][j] == 'v' || grilleJeu[i][j] == 'j' || grilleJeu[i][j] == 'b' || grilleJeu[i][j] == 'n' || grilleJeu[i][j] == 'd')
			    	            {
			    	            	while(testdirection(grilleJeu, i, j, choix_direction) == true)
			    	            	{
										grilleJeu[i+1][j] = grilleJeu[i][j];
										grilleJeu[i][j] = ' ';
										possible = true;
										i++;
									}
								}
								verif_elimination(grilleJeu, nbBoulesV, nbBoulesR, nbBoulesB, nbBoulesJ, nbBoulesN);
			    	        }
						}
						elimination(grilleJeu);
						for (i=1 ; i<=8 ; i++)
						{
			    	        for (j=1 ; j<=8 ; j++)
				   	        {
				   	        	
				   	        	if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D')
				   	        	{
				   	        		if(testdirection(grilleJeu,i,j,choix_direction) == true)
					   	        	{
					   	        		fintour = false;
					   	        		break;
					   	        	}
					   	        	else
					   	        	{
					   	        		fintour = true;
					   	        	} 
					   	        }
					   	        else
					   	        {
					   	        	fintour = true;
					   	        }
				   	        }
				   	    }
						break;
	
					case 'G' :
						for (i=1 ; i<=8 ; i++)
						{
		    	        	for (j=1 ; j<=8 ; j++)
		    	        	{
		    	        		if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D' || grilleJeu[i][j] == 'r' || grilleJeu[i][j] == 'v' || grilleJeu[i][j] == 'j' || grilleJeu[i][j] == 'b' || grilleJeu[i][j] == 'n' || grilleJeu[i][j] == 'd')
			    	           	{
			    	            	while(testdirection(grilleJeu, i, j, choix_direction) == true)
			    	           		{
										grilleJeu[i][j-1] = grilleJeu[i][j];
										grilleJeu[i][j] = ' ';
										possible = true;
										j--;
									}
								}
								verif_elimination(grilleJeu, nbBoulesV, nbBoulesR, nbBoulesB, nbBoulesJ, nbBoulesN);
								
		        	    	}
						}
						
						elimination(grilleJeu);
						for (i=1 ; i<=8 ; i++)
						{
			    	        for (j=1 ; j<=8 ; j++)
				   	        {
				   	        	
				   	        	if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D')
				   	        	{
				   	        		if(testdirection(grilleJeu,i,j,choix_direction) == true)
					   	        	{
					   	        		fintour = false;
					   	        		break;
					   	        	}
					   	        	else
					   	        	{
					   	        		fintour = true;
					   	        	} 
					   	        }
					   	        else
					   	        {
					   	        	fintour = true;
					   	        }
				   	        }
				   	    }
							break;
	
					case 'D' :
						for (i=1 ; i<=8 ; i++)
						{
			        	    for (j=8 ; j>=1 ; j--)
			        	    {
			        	        if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D' || grilleJeu[i][j] == 'r' || grilleJeu[i][j] == 'v' || grilleJeu[i][j] == 'j' || grilleJeu[i][j] == 'b' || grilleJeu[i][j] == 'n' || grilleJeu[i][j] == 'd')
			        	        {
			    	            	while(testdirection(grilleJeu, i, j, choix_direction)== true)
			    	            	{
										grilleJeu[i][j+1] = grilleJeu[i][j];
										grilleJeu[i][j] = ' ';
										possible = true;
										j++;
									}
								}
								verif_elimination(grilleJeu, nbBoulesV, nbBoulesR, nbBoulesB, nbBoulesJ, nbBoulesN);
			        	    }
						}
						elimination(grilleJeu);
						elimination(grilleJeu);
						for (i=1 ; i<=8 ; i++)
						{
			    	        for (j=1 ; j<=8 ; j++)
				   	        {
				   	        	
				   	        	if (grilleJeu[i][j] == 'R' || grilleJeu[i][j] == 'V' || grilleJeu[i][j] == 'J' || grilleJeu[i][j] == 'B' || grilleJeu[i][j] == 'N' || grilleJeu[i][j] == 'D')
				   	        	{
				   	        		if(testdirection(grilleJeu,i,j,choix_direction) == true)
					   	        	{
					   	        		fintour = false;
					   	        		break;
					   	        	}
					   	        	else
					   	        	{
					   	        		fintour = true;
					   	        	} 
					   	        }
					   	        else
					   	        {
					   	        	fintour = true;
					   	        }
				   	        }
				   	    }
						break;

					case 'R' :
						for (i=0 ; i<=9 ; i++)
					    {
					    	for(j=0; j<=9;j++)
					    	{
					    		grilleJeu[i][j] = grilleBase[i][j];
					    	}
					    }
					    possible = true;
					    *nbTours = nbToursTot+1;
					    fintour = true;
					    break;
	
					default :
						cout << "choix non valide" << endl;
						fintour = true;
						break;
				}			
		}
		cout <<endl;
		afficherGrille(grilleJeu);
	}

}

//##############################################################################################################

bool testdirection(grille grilleJeu, int i, int j, char chxDirection)
{
	bool estpossible = false;

	switch(chxDirection)
	{
		case 'H' :

	    	if (grilleJeu[i-1][j] == ' ')
	        {
				estpossible = true;
	            return estpossible;
	      	}

	        return estpossible;
			break;

		case 'B' :
			if (grilleJeu[i+1][j] == ' ')
	        {
	        	estpossible = true;
	            return estpossible;
	        }
	        return estpossible;
			break;

		case 'G' :
			if (grilleJeu[i][j-1] == ' ')
	        {
	        	estpossible = true;
	        	return estpossible;
	        }
	        return estpossible;
			break;

		case 'D' :
	    	if (grilleJeu[i][j+1] == ' ')
	        {
	        	estpossible = true;
	            return estpossible;
	        }
	        return estpossible;
			break;

		default :
			return estpossible;
	}
}

//##############################################################################################################

void verif_elimination(grille grilleJeu, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN)
{
	int i,j;



        for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'V'|| grilleJeu[i][j] == 'v')
				{
					if(grilleJeu[i-1][j] == 'V' || grilleJeu[i-1][j] == 'v')
					{
						grilleJeu[i-1][j] = 'v';
					}
					if(grilleJeu[i][j-1] == 'V' || grilleJeu[i][j-1] == 'v')
					{
						grilleJeu[i][j-1] = 'v';
					}
					if(grilleJeu[i][j+1] == 'V' || grilleJeu[i][j+1] == 'v')
					{
						grilleJeu[i][j+1] = 'v';
					}
					if(grilleJeu[i+1][j] == 'V' || grilleJeu[i+1][j] == 'v')
					{
						grilleJeu[i+1][j] = 'v';
					}
				}
			}
		}

		for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'R'|| grilleJeu[i][j] == 'r')
				{
					if(grilleJeu[i-1][j] == 'R' || grilleJeu[i-1][j] == 'r')
					{
						grilleJeu[i-1][j] = 'r';
					}
					if(grilleJeu[i][j-1] == 'R' || grilleJeu[i][j-1] == 'r')
					{
						grilleJeu[i][j-1] = 'r';
					}
					if(grilleJeu[i][j+1] == 'R' || grilleJeu[i][j+1] == 'r')
					{
						grilleJeu[i][j+1] = 'r';
					}
					if(grilleJeu[i+1][j] == 'R' || grilleJeu[i+1][j] == 'r')
					{
						grilleJeu[i+1][j] = 'r';
					}

				}
			}
		}

		for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'B'|| grilleJeu[i][j] == 'b')
				{
					if(grilleJeu[i-1][j] == 'B' || grilleJeu[i-1][j] == 'b')
					{
						grilleJeu[i-1][j] = 'b';
					}
					if(grilleJeu[i][j-1] == 'B' || grilleJeu[i][j-1] == 'b')
					{
						grilleJeu[i][j-1] = 'b';
					}
					if(grilleJeu[i][j+1] == 'B' || grilleJeu[i][j+1] == 'b')
					{
						grilleJeu[i][j+1] = 'b';
					}
					if(grilleJeu[i+1][j] == 'B' || grilleJeu[i+1][j] == 'b')
					{
						grilleJeu[i+1][j] = 'b';
					}
				}
			}
		}

		for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'J'|| grilleJeu[i][j] == 'j')
				{
					if(grilleJeu[i-1][j] == 'J' || grilleJeu[i-1][j] == 'j')
					{
						grilleJeu[i-1][j] = 'j';
					}
					if(grilleJeu[i][j-1] == 'J' || grilleJeu[i][j-1] == 'j')
					{
						grilleJeu[i][j-1] = 'j';
					}
					if(grilleJeu[i][j+1] == 'J' || grilleJeu[i][j+1] == 'j')
					{
						grilleJeu[i][j+1] = 'j';
					}
					if(grilleJeu[i+1][j] == 'J' || grilleJeu[i+1][j] == 'j')
					{
						grilleJeu[i+1][j] = 'j';
					}
				}
			}
		}
		for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
			    if(grilleJeu[i][j] == 'N'|| grilleJeu[i][j] == 'n')
				{
				    if(grilleJeu[i-1][j] == 'N' || grilleJeu[i-1][j] == 'n')
                    {
                        grilleJeu[i-1][j] = 'n';
                    }
                    if(grilleJeu[i][j-1] == 'N' || grilleJeu[i][j-1] == 'n')
                    {
                        grilleJeu[i][j-1] = 'n';
                    }
                    if(grilleJeu[i][j+1] == 'N' || grilleJeu[i][j+1] == 'n')
                    {
                        grilleJeu[i][j+1] = 'n';
                    }
                    if(grilleJeu[i+1][j] == 'N' || grilleJeu[i+1][j] == 'n')
                    {
                        grilleJeu[i+1][j] = 'n';
                    }
				}
			}
		}

}

void elimination(grille grilleJeu)
{
	int i,j;
	for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'v' || grilleJeu[i][j] == 'r' || grilleJeu[i][j] == 'b' || grilleJeu[i][j] == 'j' || grilleJeu[i][j] == 'n')
				{
				   grilleJeu[i][j] = ' ';
				}
            }
		}
}


int victoire (grille grilleJeu)
{
	int i,j;
	int nbBoulesB = 0;
	int nbBoulesV = 0;
	int nbBoulesJ = 0;
	int nbBoulesN = 0;
	int nbBoulesR = 0;
	int etatJeu;
	
	for(i = 1 ; i <= 8 ; i++)
		{
			for(j= 1 ; j <= 8 ; j++)
			{
				if(grilleJeu[i][j] == 'V')
				{
				   nbBoulesV++;
				}
				if(grilleJeu[i][j] == 'R')
				{
				   nbBoulesR++;
				}
				if(grilleJeu[i][j] == 'B')
				{
				   nbBoulesB++;
				}
				if(grilleJeu[i][j] == 'J')
				{
				   nbBoulesJ++;
				}
				if(grilleJeu[i][j] == 'N')
				{
				   nbBoulesN++;
				}
            }
		}
		
	if(nbBoulesB == 0 && nbBoulesJ == 0 && nbBoulesN == 0 && nbBoulesR == 0 && nbBoulesV == 0)
	{
		etatJeu = 0;
		return etatJeu;
	}
	else
	{
		if(nbBoulesB == 1 || nbBoulesJ == 1 || nbBoulesN == 1 || nbBoulesR == 1 || nbBoulesV == 1)
		{
			etatJeu = 1;
			return etatJeu;
		}
		else
		{
			etatJeu = 2;
			return etatJeu;
		}	
	}
}

//##############################################################################################################

int jouer()
{
	int i,j;
    grille grilleJeu;
    grille grilleBase;
    int nbTours;
    int nbToursTot;
    int nbBoulesV = 0;
    int nbBoulesR = 0;
    int nbBoulesB = 0;
    int nbBoulesJ = 0;
    int nbBoulesN = 0;
    int gagne;
    bool finjeu = false;
    char choixJoueur;
    char choixSauv;
    string nomGrille;

	while (finjeu == false)
	{
	    creationGrille(grilleJeu, nbTours, &nbBoulesV, &nbBoulesR, &nbBoulesB, &nbBoulesJ, &nbBoulesN);
    	nbToursTot = nbTours;
    	afficherGrille(grilleJeu);
    	choixJoueur = ' ';
    	for (i=0 ; i<=9 ; i++)
    	{
    		for(j=0; j<=9;j++)
    		{
    			grilleBase[i][j] = grilleJeu[i][j];
    		}
    	}
    	cout << "Sauvegarder la grille ? (o/n) : ";
    	cin >> choixSauv;
    	if (choixSauv == 'o')
    	{
    		cout << endl << "Quel nom de grille ? : ";
    		cin >> nomGrille;
    		sauvegarde(grilleJeu, nomGrille, nbTours);
    		
    	}
		while (nbTours != 0)
		{
			cout << endl << endl <<"Il vous reste : " << nbTours << " tours." <<endl << endl;
			
			deplacement(grilleJeu, grilleBase, &nbTours, nbToursTot, &nbBoulesV, &nbBoulesR, &nbBoulesB, &nbBoulesJ, &nbBoulesN);
			afficherGrille(grilleJeu);
			nbTours --;
			gagne = victoire(grilleJeu);
			if (gagne == 0)
			{
				cout << endl << endl <<"Bravo, vous avez gagne !!" << endl <<endl;
				break;
			}
			else
			{
				if(gagne == 1)
				{
					nbTours = 0;
				}
			}
			if(nbTours == 0)
			{
				cout << endl << endl << "Vous avez perdu." << endl << endl;
			}
				
		
		}
	
		while(choixJoueur != 'o' && choixJoueur != 'n')
		{	
			cout << "Rejouer ? (o/n) : ";
			cin >> choixJoueur;
			cout << endl;
			switch(choixJoueur)
			{
				case 'o': 
					finjeu = false;
					break;
				
				case 'n':
					return 0;
					break;
				
				default :
					cout << "Choix non valide.";
					break;
			}
		}
	}
}

//##############################################################################################################

void sauvegarde(grille grilleJeu, string nomGrille, int nbTours)
{
	int i,j;
	string const fichier("fichierGrilles");
	ofstream fluxFich(fichier.c_str(), ios::app);
	
	if(fluxFich)
	{
		fluxFich << nomGrille <<" " << nbTours;
		for(i=1 ; i <= 8 ; i++)
		{
			for(j=1 ; j <= 8 ; j++)
			{
				fluxFich << grilleJeu[i][j];
			}
		}
	}
	else
	{
		cout << "Problème lors de l'ouverture du fichier fichierGrilles." << endl;
	}
}

//##############################################################################################################

void chargementfichier(grille grilleJeu, int &nbTours, int* position)
{
	string const fichier("fichierGrilles");
	int i,j;
	ifstream fluxFich(fichier.c_str());
	string nomGrille;
	
	
	if(fluxFich)
	{
		fluxFich.seekg(*position,ios::beg);
		fluxFich >> nomGrille;
		fluxFich >> nbTours;
		for (i = 1; i<=8 ; i++)
		{
			for(j = 1 ; j<=8 ; j++)
			{
				fluxFich.get(grilleJeu[i][j]);
			}
		}
		cout << nomGrille << endl;
		cout << endl << "La grille se joue en : " << nbTours << " tours." << endl << endl;
		*position = fluxFich.tellg();
	}
	else
	{
		cout << "Problème lors de la lecture du fichier fichierGrilles." << endl;
	}
}

//##############################################################################################################

int jouerCharge()
{
	int i,j;
    grille grilleJeu;
    grille grilleBase;
    int nbTours;
    int nbToursTot;
    int nbBoulesV = 0;
    int nbBoulesR = 0;
    int nbBoulesB = 0;
    int nbBoulesJ = 0;
    int nbBoulesN = 0;
    int gagne;
    bool finjeu = false;
    char choixJoueur;
    string nomGrille;
    int position = 0;

	while (finjeu == false)
		{
	    	for (i=0 ; i<=9 ; i++)
	    {
    	    grilleJeu[0][i] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[9][i] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[i][0] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[i][9] = '#';
    	}
	
    	//initialisation du "centre" de la grille
	
    	for (i=1 ; i<=8 ; i++)
    	{
    	    for (j=1 ; j<=8 ; j++)
    	    {
    	        grilleJeu[i][j] = ' ';
    	    }
    	}
		
		choixJoueur = ' ';
	    chargementfichier(grilleJeu, nbTours, &position);
    	nbToursTot = nbTours;
    	afficherGrille(grilleJeu);
    	for (i=0 ; i<=9 ; i++)
    	{
    		for(j=0; j<=9;j++)
    		{
    			grilleBase[i][j] = grilleJeu[i][j];
    		}
    	}
		while (nbTours != 0)
		{
			cout << endl << endl <<"Il vous reste : " << nbTours << " tours." <<endl << endl;
			
			deplacement(grilleJeu, grilleBase, &nbTours, nbToursTot, &nbBoulesV, &nbBoulesR, &nbBoulesB, &nbBoulesJ, &nbBoulesN);
			nbTours --;
			gagne = victoire(grilleJeu);
			if (gagne == 0)
			{
				cout << endl << endl <<"Bravo, vous avez gagne !!" << endl <<endl;
				break;
			}
			else
			{
				if(gagne == 1)
				{
					nbTours = 0;
				}
			}
			if(nbTours == 0)
			{
				cout << endl << endl << "Vous avez perdu." << endl << endl;
			}
				
		
		}
	
		while(choixJoueur != 'o' && choixJoueur != 'n')
		{	
			cout << "Rejouer ? (o/n) : ";
			cin >> choixJoueur;
			cout << endl;
			switch(choixJoueur)
			{
				case 'o': 
					finjeu = false; 
					break;
				
				case 'n':
					return 0;
					break;
				
				default :
					cout << "Choix non valide.";
					break;
			}
		}
	}
}

//##############################################################################################################

void chargementfichierclssmnt(grille grilleJeu, int &nbTours, int* position)
{
	string const fichier("fichierGrillesclssmnt");
	int i,j;
	ifstream fluxFich(fichier.c_str());
	string nomGrille;
	
	
	if(fluxFich)
	{
		fluxFich.seekg(*position,ios::beg);
		fluxFich >> nomGrille;
		fluxFich >> nbTours;
		for (i = 1; i<=8 ; i++)
		{
			for(j = 1 ; j<=8 ; j++)
			{
				fluxFich.get(grilleJeu[i][j]);
			}
		}
		cout << nomGrille << endl;
		cout << endl << "La grille se joue en : " << nbTours << " tours." << endl << endl;
		*position = fluxFich.tellg();
	}
	else
	{
		cout << "Problème lors de la lecture du fichier fichierGrillesclssmnt." << endl;
	}
}

//##############################################################################################################

int jouerChargeclssmnt()
{
	int i,j;
    grille grilleJeu;
    grille grilleBase;
    int nbTours;
    int nbToursTot;
    int nbBoulesV = 0;
    int nbBoulesR = 0;
    int nbBoulesB = 0;
    int nbBoulesJ = 0;
    int nbBoulesN = 0;
    int gagne;
    bool finjeu = false;
    char choixJoueur;
    string nomGrille;
    int position = 0;
	int nbGrille = 0;
	double tempsTotal = 0;
	double tempsMax = 3600;
	time_t tempsInit;
	time_t tempsFin;
	int grilleJoue = 0;
	int nbGrillesTot = 14;
	bool reussite = false;
	
	
	while (finjeu == false)
		{
	    	for (i=0 ; i<=9 ; i++)
	    {
    	    grilleJeu[0][i] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[9][i] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[i][0] = '#';
    	}
	
    	for (i=0 ; i<=9 ; i++)
    	{
    	    grilleJeu[i][9] = '#';
    	}
	
    	//initialisation du "centre" de la grille
	
    	for (i=1 ; i<=8 ; i++)
    	{
    	    for (j=1 ; j<=8 ; j++)
    	    {
    	        grilleJeu[i][j] = ' ';
    	    }
    	}
		
		choixJoueur = ' ';
	    chargementfichierclssmnt(grilleJeu, nbTours, &position);
    	nbToursTot = nbTours;
    	afficherGrille(grilleJeu);
    	for (i=0 ; i<=9 ; i++)
    	{
    		for(j=0; j<=9;j++)
    		{
    			grilleBase[i][j] = grilleJeu[i][j];
    		}
    	}
    	tempsInit = time(NULL);
		while (nbTours != 0)
		{
			cout << endl << endl <<"Il vous reste : " << nbTours << " tours." <<endl << endl;
			
			deplacement(grilleJeu, grilleBase, &nbTours, nbToursTot, &nbBoulesV, &nbBoulesR, &nbBoulesB, &nbBoulesJ, &nbBoulesN);
			nbTours --;
			gagne = victoire(grilleJeu);
			if (gagne == 0)
			{
				tempsFin = time(NULL);
				cout << endl << endl <<"Bravo, vous avez gagne !!" << endl <<endl;
				tempsTotal += (tempsMax - difftime(tempsFin,tempsInit));
				cout <<"Vous avez mis : " << difftime(tempsFin,tempsInit) << " secondes pour résoudre cette grille."<< endl;
				nbGrille++;
				reussite = true;
				break;
			}
			else
			{
				if(gagne == 1)
				{
					nbTours = 0;
					reussite = false;
				}
			}
			if(nbTours == 0)
			{
				cout << endl << endl << "Vous avez perdu." << endl << endl;
			}
				
		
		}
		if(grilleJoue != nbGrillesTot )
		{
		
			if (reussite == true)
			{
				while(choixJoueur != 'o' && choixJoueur != 'n')
				{
					cout << "Continuer ? (o/n) : ";
					cin >> choixJoueur;
					cout << endl;
					switch(choixJoueur)
					{
						case 'o': 
							finjeu = false; 
							break;
						
						case 'n':
							cout << "Votre score : " << (nbGrille*tempsTotal) << " Points." << endl;
							setscore(tempsTotal,nbGrille);
							return 0;
							break;
						
						default :
							cout << "Choix non valide.";
							break;
					}
				}
			}
			else
			{	
				while(choixJoueur != 'o' && choixJoueur != 'n')
				{
					cout << "Rejouer ? (o/n) : ";
					cin >> choixJoueur;
					cout << endl;
					switch(choixJoueur)
					{
						case 'o': 
							finjeu = false; 
							return 3;
							break;
						
						case 'n':
							cout << "Votre score : " << (nbGrille*tempsTotal) << " Points." << endl;
							setscore(tempsTotal,nbGrille);
							return 0;
							break;
						
						default :
							cout << "Choix non valide.";
							break;
					}
				}
			}
		}
		else
		{
			cout <<endl <<  "###Bravo !!!###"<<endl <<"Vous avez fini les grilles avec scores." << endl;
			cout << "Votre score : " << (nbGrille*tempsTotal) << " Points." << endl;
			setscore(tempsTotal,nbGrille);
			return 0;
		}
	}
}

//##############################################################################################################

void setscore(double tempsTotal, int nbGrilles)
{
	double score;
	double scoreTemp;
	string strscoreTemp;
	int i;
	int taille;
	int position;
	string strscore;
	ostringstream strscores;
	string nomTemp;
	string nomFin, scoreFin, nomFinTemp;
	string const fichier("fichierScores");
	ifstream fluxFichR(fichier.c_str());
	string fichierTemp;
	string insertFich;
	string nomJoueur;
	bool scored = false;
	
	
	score = tempsTotal*nbGrilles;
	strscores << score;
	strscore = strscores.str();
	cout << "Veuillez entre votre nom : ";
	cin >> nomJoueur;
	insertFich = ' ';
	insertFich += nomJoueur;
	insertFich.push_back(' ');
	insertFich += strscore;
	
	
	fluxFichR.seekg(0,ios::end);
	taille = fluxFichR.tellg();

	fluxFichR.clear();
	fluxFichR.seekg(0,ios::beg);
	
	for(i = 0 ; i <= taille ; i++)
	{	
		if(scored  == false)
		{
			position = fluxFichR.tellg();
			
			fluxFichR >> nomTemp;
			fluxFichR >> scoreTemp;
			strscoreTemp.push_back(scoreTemp);
			
			if(score > scoreTemp)
			{
				fluxFichR.seekg(0,ios::beg);
				getline(fluxFichR, fichierTemp);
				
				fichierTemp.insert(position, insertFich);
				
				ofstream fluxFichW(fichier.c_str());
				
				fluxFichW.seekp(0,ios::beg);
				fluxFichW << fichierTemp;
				cout << endl <<"Bravo ! Votre score figure parmi le top 10." << endl << endl;
				fluxFichW.close();
				scored = true;
			}
		}
	
	}
	
}

//##############################################################################################################

void afficherscores()
{
	string const fichier("fichierScores");
	ifstream fluxFich(fichier.c_str());
	string temp;
	
	cout << "### Meilleurs Scores : ###" << endl << endl;
	fluxFich >> temp;
	cout << "1. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "2. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "3. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "4. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "5. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "6. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "7. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "8. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "9. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;
	fluxFich >> temp;
	cout << "10. " << temp << " ";
	fluxFich >> temp;
	cout << temp << " Points" << endl;

}
