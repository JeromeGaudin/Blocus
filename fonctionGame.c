/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <math.h>
#include "fonctionGame.h"

#define CASE 50						/*taille d'une case*/
#define TRAIT 6						/*epaisseur d'un trait*/
#define SPRITE 40					/*taille d'un coté d'un sprite*/
#define COULEURGRILLE 0,0,0			/*couleur des trait de la grille (r,v,b)*/

/*-------------------------------------Graphique-----------------------------*/
void afficher_grille(int xGrille, int yGrille, int nbCase) {
	int i, j;

	for(i=0; i<=nbCase*CASE; i+=CASE) {
		for(j=0; j<=nbCase*CASE; j+=CASE) {
			RemplirRectangle(xGrille, yGrille+j, CASE*nbCase, TRAIT);
			RemplirRectangle(xGrille+i, yGrille, TRAIT, CASE*nbCase);
			if(i==nbCase*CASE && j==nbCase*CASE) {
				RemplirRectangle(xGrille+i, yGrille+j, TRAIT, TRAIT);
			}
		}
	} 
}

void afficher_le_sprite(int xGrille, int yGrille, int i, int j, char numSprite) {
	int espace, x, y;
	/*calcule pour centrer l'image dans la case*/
	espace = (CASE - TRAIT - SPRITE)/2 + TRAIT;

	x = espace + xGrille + CASE*j;
	y = espace + yGrille + CASE*i;
	AfficherSprite(numSprite, x, y);
}

void effacer_le_sprite(int xGrille, int yGrille, int i, int j) {
	int x, y;
	/*calcule l'espace que prennait le sprite*/
	int espace = (CASE - TRAIT - SPRITE)/2 + TRAIT;

	/*calcule les coordonnées de la case a effacer*/
	x = espace + xGrille + CASE*j;
	y = espace + yGrille + CASE*i;

	CopierZone(1,0,x,y,SPRITE,SPRITE, x, y);
}

void effacer_texte(int x, int y, char* s, int taille) {
	int longueur, hauteurSup, hauteurInf;

	hauteurSup = TailleSupPolice(taille);
	hauteurInf = TailleInfPolice(taille);
	longueur = TailleChaineEcran(s, taille);
	CopierZone(1,0,x,y-hauteurSup, longueur, hauteurSup+hauteurInf, x, y-hauteurSup);
}
/*-------------------------------------Logique-------------------------------*/
void emplacement_grille(int* x, int* y, int lFenetre, int hFenetre, int nbCase) {
	*x = (lFenetre - (nbCase*CASE + TRAIT))/2;
	*y = (hFenetre - (nbCase*CASE + TRAIT))/2;
}

int ** creer_tableau(int n) {
	int i;
	 int **t = NULL;
 	
	t=(int**)malloc(n*sizeof(int*));

	for(i=0;i<n;i++) {
		t[i]=(int*) calloc(n, sizeof(int));
	}
	/*test si l'allocation de mémoire c'est bien passé*/
	if(t!=NULL) {
		for(i=0;i<n;i++){
			if(t[i]==NULL) {
				effacer_tableau(t, i);
				return NULL;
			}
		}
	}

	return t;
}

void effacer_tableau(int ** t, int n) {
	int i;

	for(i=0; i<n; i++) {
		free(t[i]);
	}
	free(t);
}

int quelle_case(int*i, int*j, int nbCase, int xGrille,int  yGrille) {
	int x, y;
	
	while(!SourisCliquee()) {
	}
	x=_X;
	y=_Y;

	x -=  xGrille;
	y -=  yGrille;
	if(x < 0 || y < 0 || x > nbCase*CASE || y > nbCase*CASE) {
		return EXIT_FAILURE;/* la souris n'est pas dans la grille */
	}
	*i = y/CASE;
	*j = x/CASE;
	return EXIT_SUCCESS;
}

void trouver_numero(int* i, int* j, int ** tab, int taille, int nombre) {
	int k, l;
	for(k=0; k<taille; k++) {
		for(l=0; l<taille; l++) {
			if(tab[l][k]==nombre) {
				*i = l;
				*j = k;
			}
		}
	}
}

int placer_pion(int x, int y, int i, int j, int ** tab, int taille, char numSprite) {
	int ancienI=-1, ancienJ=-1, t1, t2;
	
	trouver_numero(&ancienI, &ancienJ, tab, taille, numSprite);
	
	if(ancienI!=-1) {
	t1 =(int) abs((double)ancienI - i);
	t2 =(int) abs((double)ancienJ - j);
	} else {
	t1 = 0;
	t2 = 0;
	}
	if(t1 > 1 || t2 > 1 || tab[i][j]!=0) {
		return EXIT_FAILURE;/*L'utilisateur veut déplacer le pion de deux cases ou sur une case occupée*/
	}
	if(ancienI!=-1) {
		tab[ancienI][ancienJ] = 0;
		effacer_le_sprite(x, y, ancienI, ancienJ);
	}
	tab[i][j] = numSprite;
	afficher_le_sprite(x, y, i, j, numSprite);	
	return EXIT_SUCCESS;
}

int placer_croix(int x, int y, int i, int j, int ** tab, int numSprite) {
	if(tab[i][j]!=0) {
		return EXIT_FAILURE;/*La case est occupée*/
	}
	tab[i][j] = numSprite;
	afficher_le_sprite(x, y, i, j, numSprite);
	return EXIT_SUCCESS;
}

int perdu(int ** tab, int n, int player) {
	int i, j, a, b, flag=0;
	trouver_numero(&i, &j, tab, n, player);
	for(a=-1; a<=1 && flag==0; a++) {
		for(b=-1; b<=1 && flag==0; b++) {
			if(i+a>=0 && j+b>=0 && i+a<n && j+b<n && tab[i+a][j+b]==0) {
				flag = 1;
			}
		}
	}
	if(flag) {
		return EXIT_SUCCESS;/*joueur n'a toujours pas perdu*/
	} else {
		return player;/*le joueur a perdu*/
	}
}	
