/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "menu.h"
#include "game.h"

#define LF 1000 			/*Longueur de la fenêtre*/
#define HF 600			/*hauteur de la fenêtre*/
#define DECAL 50		/*décalage entre un bouton et un autre objet*/

/*caractéristique des boutons "1 Joueur" et "2 Joueurs"*/
/*(longueur, hauteur, point X où il est placé, point Y où il est placé)*/
#define LBOUTON	199		 
#define HBOUTON 75		
#define XBOUTON1 DECAL
#define XBOUTON2 (LF - LBOUTON - DECAL)
#define YBOUTON (HF - HBOUTON - DECAL)

/*caractéristique des boutons avec numéro*/
/*(longueur, hauteur, point X où il est placé, point Y où il est placé)*/
#define	LNUMBOUTON 100	
#define	HNUMBOUTON 100	
#define XNUMBOUTON ((LF - LNUMBOUTON)/2)	
#define YNUMBOUTON (YBOUTON - HNUMBOUTON - DECAL)

/*caractéristique des boutons flèches*/
/*longueur d'un coté du bouton, point X où il est placé, point Y où il est placé*/
/*(les boutons sont carré)*/
#define COTEFLECHE 100
#define XDROITE (XNUMBOUTON + LNUMBOUTON + DECAL)		
#define YDROITE YNUMBOUTON	
#define XGAUCHE (XNUMBOUTON - COTEFLECHE - DECAL)
#define YGAUCHE YNUMBOUTON	
	
#define TITRETEXTE 2 					/*taille de police du titre*/
#define YTITRE 150						/*Point Y ou le titre est placé */
#define TEXTE 2							/*taille du texte*/
#define YTEXTE (YNUMBOUTON - DECAL/2)	/*Point Y ou le texte est placé */

/*position du texte de la fin de partie*/
#define YFIN (HF/2)
#define TAILLEFIN 2

/*position du texte si il y a une erreur*/
#define XERREUR 100
#define YERREUR 100
#define TAILLEERREUR 2

/*hauteur et longueur des boutons quitter et menu*/
#define LQUITTER 175
#define HQUITTER 75
#define LMENU 150
#define HMENU 75

void afficher_bouton(bouton b) {
	AfficherSprite(b.numSprite, b.x, b.y);
}

int presser_bouton(bouton* b) {
	int afficher=0;
	
	SourisPosition();
	while(_X>b->x && _Y>b->y && _X<b->x+b->longueur && _Y<b->y+b->largeur && !SourisCliquee()) {
		SourisPosition();
		AfficherSprite(b->numSpritePresse, b->x, b->y);
		if(SourisCliquee()) {
			return EXIT_SUCCESS;
		}
		afficher=1;
	}
	if(afficher==1) {
		AfficherSprite(b->numSprite, b->x, b->y);
	}
	return EXIT_FAILURE;
}

int ecran_perdu(int val, bouton menu, bouton quitter) {
	char* gagnerO = "Le joueur orange a gagne !",*gagnerB = "Le joueur bleu a gagne !";
	char* gagnerIA = "Vous avez gagne !";
	char* perduIA = "Vous avez perdu contre un IA qui se deplace aleatoirement !";
	int tailleChaine, t1=1, t2=1;
	
	ChargerImageFond("./img/background.jpg");

	if(val==2) {
		tailleChaine = TailleChaineEcran(gagnerB, TAILLEFIN);
		EcrireTexte((LF - tailleChaine)/2, YFIN, gagnerB, TAILLEFIN);
	} else if(val==3) {
		tailleChaine = TailleChaineEcran(gagnerO, TAILLEFIN);
		EcrireTexte((LF - tailleChaine)/2, YFIN, gagnerO, TAILLEFIN);
	} else if(val==4) {
		tailleChaine = TailleChaineEcran(gagnerIA, TAILLEFIN);
		EcrireTexte((LF - tailleChaine)/2, YFIN, gagnerIA, TAILLEFIN);
	} else if(val==5) {
		tailleChaine = TailleChaineEcran(perduIA, TAILLEFIN);
		EcrireTexte((LF - tailleChaine)/2, YFIN, perduIA, TAILLEFIN);
	}
	afficher_bouton(quitter);
	afficher_bouton(menu);

	while(t1 && t2) {
		t1 = presser_bouton(&quitter); 
		t2 = presser_bouton(&menu);
	}
	if(t2==0)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

void ecran_menu(bouton joueur1, bouton joueurs2, bouton gauche, bouton droite, 
			   	int spriteNum) {
	char* blocus = "Blocus", * choixCase = "Choisisez la taille de la grille";
	int xTexte;

	ChargerImageFond("./img/background.jpg");
	afficher_bouton(joueur1);
	afficher_bouton(joueurs2);
	afficher_bouton(droite);
	afficher_bouton(gauche);
	AfficherSprite(spriteNum, XNUMBOUTON, YNUMBOUTON);

	xTexte = (LF - TailleChaineEcran(blocus, TITRETEXTE))/2;
	EcrireTexte(xTexte, YTITRE, blocus, TITRETEXTE);
	xTexte = (LF - TailleChaineEcran(choixCase, TEXTE))/2;
	EcrireTexte(xTexte, YTEXTE, choixCase, TEXTE);
}

void erreur(int p) {
	couleur rouge = CouleurParComposante(255,0,0);
	char* erreur1 = "/!\\ La fonction malloc ou calloc a echoue";
	char* erreur2 = "/!\\ Un des sprites dans game.c n'a pas pu etre charge ";
	char* erreur3 = "/!\\ Un des sprites dans meun.c n'a pas pu etre charge ";
	char* message = "\0";

	if(p==-1)
		message = erreur1;
	else if(p==1)
		message = erreur2;
	else if(p==-2)
		message = erreur3;
	if(message[0]!='\0') {
		ChoisirCouleurDessin(rouge);
		printf("%s\n", message);
		EcrireTexte(XERREUR, YERREUR, message, TAILLEERREUR);
		while(!SourisCliquee());
		FermerGraphique();
		exit(EXIT_FAILURE);
	}
}

int main(void) {
	int joueur1N, joueur1C, joueurs2N, joueurs2C, bouton3, gaucheN, droiteN;
	int numBouton=3, t=0, joueurPerdu=0, relancer=1, fin=0;
	int menuN, menuC, quitterN, quitterC, droiteC, gaucheC;

		InitialiserGraphique();
		CreerFenetre(0, 0, LF, HF);

		droiteN = ChargerSprite("./img/flècheDroite.png");
		gaucheN = ChargerSprite("./img/flècheGauche.png");
		bouton3 = ChargerSprite("./img/bouton3.png");
	  	ChargerSprite("./img/bouton4.png");
	  	ChargerSprite("./img/bouton5.png");
	  	ChargerSprite("./img/bouton6.png");
	  	ChargerSprite("./img/bouton7.png");
	  	ChargerSprite("./img/bouton8.png");
	  	ChargerSprite("./img/bouton9.png");
		joueur1N = ChargerSprite("./img/1joueur.png");
		joueur1C = ChargerSprite("./img/1joueurC.png");
		joueurs2N = ChargerSprite("./img/2joueurs.png");
		joueurs2C = ChargerSprite("./img/2joueursC.png"); 
		menuN = ChargerSprite("./img/menu.png");
		menuC = ChargerSprite("./img/menuC.png");
		quitterN = ChargerSprite("./img/quitter.png");
		quitterC = ChargerSprite("./img/quitterC.png");
		droiteC = ChargerSprite("./img/flècheDroiteC.png");
		gaucheC = ChargerSprite("./img/flècheGaucheC.png");
		/*verifie si les sprites sont bien chargé*/
		if(droiteN<=0 || gaucheN<=0 || bouton3<=0 || joueur1N<=0 || joueur1C<=0 || 
		  joueurs2N<=0 || joueurs2C<=0 || menuN<=0 || menuC<=0 || quitterN<=0 || 
		  quitterC<=0 || droiteC<=0 || gaucheC<=0 || (joueur1N - bouton3 != 7)) { 
		  /*vu que les spritjoueur1N - bouton3es sont attribué dans l'ordre quand il sont
		   chargé on peut faire : SpriteFin - SpriteDebut == nbSpriteEntre+1*/ 
			erreur(-2);
		}

		bouton joueur1 = {joueur1N, joueur1C, XBOUTON1, YBOUTON, LBOUTON, HBOUTON};
		bouton joueurs2 = {joueurs2N, joueurs2C, XBOUTON2, YBOUTON, LBOUTON, HBOUTON};
		bouton flecheGauche ={gaucheN,gaucheC, XGAUCHE, YGAUCHE, COTEFLECHE, COTEFLECHE};
		bouton flecheDroite ={droiteN,droiteC, XDROITE, YDROITE, COTEFLECHE, COTEFLECHE};
		bouton menu = {menuN, menuC, DECAL, HF-DECAL-HMENU, LMENU, HMENU};
		bouton quitter ={quitterN, quitterC, LF-DECAL-LQUITTER, HF-DECAL-HMENU, LQUITTER,
						 HQUITTER};
	

		ecran_menu(joueur1, joueurs2, flecheGauche, flecheDroite, bouton3);
		erreur(0);
	while(fin==0) {
		t = presser_bouton(&joueur1); 
		if(t==0) {
			joueurPerdu = game(LF, HF, numBouton,1);
			erreur(joueurPerdu);
			relancer = ecran_perdu(joueurPerdu, menu, quitter);
			fin = relancer;
		}
		t = presser_bouton(&joueurs2);
		if(t==0) {
			joueurPerdu = game(LF, HF, numBouton,2);
			erreur(joueurPerdu);
			relancer = ecran_perdu(joueurPerdu, menu, quitter);
			fin = relancer;
		}
		if(relancer==0) {
			ecran_menu(joueur1, joueurs2, flecheGauche, flecheDroite, numBouton);
			relancer=1;
		}
		t = presser_bouton(&flecheDroite);
		if(t==0 && numBouton < 9) {
			numBouton++;
			AfficherSprite(numBouton,XNUMBOUTON,YNUMBOUTON);
		}
		t = presser_bouton(&flecheGauche);
		if(t==0 && numBouton > 3) {
			numBouton--;
			AfficherSprite(numBouton,XNUMBOUTON,YNUMBOUTON);
		}	

	}
	FermerGraphique();
	return EXIT_SUCCESS;
}
