/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>
#include "game.h"
#include "fonctionGame.h"



#define XTOUR 20		/*Point X est affiché le tour du joueur*/
#define YTOUR 40		/*Point Y est affiché le tour du joueur*/
#define TAILLETOUR 2	/*taille de la police pour le tour*/
#define XMESSAGE 20		/*Point X est affiché le texte*/
#define YMESSAGE 80		/*Point Y est affiché le texte*/
#define TAILLEMESSAGE 2	/*taille de la police pour le texte*/

/*-------------------------------------GAME----------------------------------*/

int un_joueur(int nbCase,int x,int y,int pionO,int pionB,int croixO,int croixB,int xTour) {
	int i, j, pion=pionO, croix=croixO, fin=0, t;
	int ** tab = creer_tableau(nbCase);
	char* pionMessage = "Le pion peut se deplacer que dans case libre autour de lui";
	char* croixMessage = "La croix peut etre mise que sur une case libre";
	
	if(tab==NULL)
		return -1;
	EcrireTexte(xTour, YTOUR, "orange", TAILLETOUR);
	do {								/*tour où on place juste les pions*/
		while(quelle_case(&i, &j, nbCase, x, y));
	}while(placer_pion(x, y, i, j, tab, nbCase, pion));
	pion=pionB;
	while(placer_pion(x, y, rand()%nbCase, rand()%nbCase, tab, nbCase, pion));
	pion=pionO;
	while(1) {							/*tour pour un joueur (IA ou l'utilisateur)*/
		fin = perdu(tab, nbCase, pion);
		if(fin!=0) {
			return fin;
		}
		if(pion==pionO) {				/*déplacer le pion*/
			for(t=-1; t!=0;) {
				while(quelle_case(&i, &j, nbCase, x, y));
				t = placer_pion(x, y, i, j, tab, nbCase, pion);
				effacer_texte(XMESSAGE, YMESSAGE, pionMessage, TAILLEMESSAGE);
				if(t)
					EcrireTexte(XMESSAGE, YMESSAGE, pionMessage, TAILLEMESSAGE);
			}	
		} else {
			while(placer_pion(x,y, rand()%nbCase,rand()%nbCase, tab, nbCase,pion));
		}
		if(pion==pionO) {				/*placer la croix*/
			for(t=-1; t!=0;) {
				while(quelle_case(&i, &j, nbCase, x, y));
				t = placer_croix(x, y, i, j, tab, croix);
				effacer_texte(XMESSAGE, YMESSAGE, croixMessage, TAILLEMESSAGE);
				if(t)
					EcrireTexte(XMESSAGE, YMESSAGE, croixMessage, TAILLEMESSAGE);
			}
		} else {
			while(placer_croix(x, y, rand()%nbCase, rand()%nbCase, tab, croix));
		}
		pion=(pion==pionO)? pionB: pionO;
		croix=(croix==croixO)? croixB: croixO;
	}
}

int deux_joueurs(int nbCase,int x,int y,int pionO,int pionB,int croixO,int croixB,
				 int xTour) {
	int a, i, j, pion=pionO, croix=croixO, fin=0, t;
	int ** tab = creer_tableau(nbCase);
	char* pionMessage = "Le pion peut se deplacer que dans case libre autour de lui";
	char* croixMessage = "La croix peut etre mise que sur une case libre";
	char* tourMessage = "orange";

	if(tab==NULL)
		return -1;
	for(a=0; a<2; a++) {			/*tour où on place juste les pions*/
		EcrireTexte(xTour, YTOUR, tourMessage, TAILLETOUR);
		do {
			while(quelle_case(&i, &j, nbCase, x, y));
		}while(placer_pion(x, y, i, j, tab, nbCase, pion));
		effacer_texte(xTour, YTOUR, tourMessage, TAILLEMESSAGE);
		pion=pionB;
		tourMessage="bleu";
	}
	pion=pionO;
	tourMessage="orange";
	while(1) {						/*tour pour un joueur*/
		EcrireTexte(xTour, YTOUR, tourMessage, TAILLETOUR);
		fin = perdu(tab, nbCase, pion);
		if(fin!=0) {
			return fin;
		}
		for(t=-1; t!=0;) {			/*déplacer le pion*/
			while(quelle_case(&i, &j, nbCase, x, y));
			t = placer_pion(x, y, i, j, tab, nbCase, pion);
			effacer_texte(XMESSAGE, YMESSAGE, pionMessage, TAILLEMESSAGE);
			if(t)
				EcrireTexte(XMESSAGE, YMESSAGE, pionMessage, TAILLEMESSAGE);	
		}
		for(t=-1; t!=0;) {			/*placer la croix*/
			while(quelle_case(&i, &j, nbCase, x, y));
			t = placer_croix(x, y, i, j, tab, croix);
			effacer_texte(XMESSAGE, YMESSAGE, croixMessage, TAILLEMESSAGE);
			if(t)
				EcrireTexte(XMESSAGE, YMESSAGE, croixMessage, TAILLEMESSAGE);
		}
		pion=(pion==pionO)? pionB: pionO;
		croix=(croix==croixO)? croixB: croixO;
		effacer_texte(xTour, YTOUR, tourMessage, TAILLEMESSAGE);
		tourMessage=(*tourMessage=='o')? "bleu":"orange";
	}
}
int game(int lFenetre, int hFenetre, int nbCase,int nbJoueur) {
	int x, y, pionO, pionB, croixO, croixB, t, xTaille;
	char* tourMessage = "C'est au tour du pion ";
	srand(time(NULL));
	
	/*Calcule x et y pour bien centrer la grille*/
	emplacement_grille(&x, &y, lFenetre, hFenetre, nbCase);


	pionO  = ChargerSprite("./img/pionOrange.png");
	pionB = ChargerSprite("./img/pionBleu.png");
	croixO = ChargerSprite("./img/croix_orange.png");
	croixB = ChargerSprite("./img/croix_bleu.png");
	/*teste si les sprites sont chargés*/
	if(pionO<=0 || pionB<=0 || croixB<=0 || croixO<=0) {
		return EXIT_FAILURE;
	}
	ChoisirEcran(1);
	ChargerImage("./img/background.jpg",0,0,0,0,1000,600);
	ChoisirEcran(0);

	ChargerImageFond("./img/background.jpg");
	afficher_grille(x, y, nbCase);

	EcrireTexte(XTOUR, YTOUR, tourMessage, TAILLETOUR);
	xTaille = TailleChaineEcran(tourMessage, TAILLEMESSAGE) + XTOUR;

	if(nbJoueur==1) { 
		t = un_joueur(nbCase,x,y,pionO,pionB,croixO,croixB,xTaille);
		if (t==pionB)
			return 4;
		else if (t==pionO)
			return 5;
	} else if(nbJoueur==2) { 
		t = deux_joueurs(nbCase,x,y,pionO,pionB,croixO,croixB,xTaille);
		if (t==pionB)
			return 3;
		else if (t==pionO)
			return 2;
	}
	return t; /*si t=-1 le retourner (le malloc a échoué)*/
	
	LibererSprite(pionO);
	LibererSprite(pionB);
	LibererSprite(croixO);
	LibererSprite(croixB);
	
	return EXIT_SUCCESS;	
}
