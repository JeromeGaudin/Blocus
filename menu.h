/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#ifndef MENU_H
#define MENU_H
/*
 * Structure pour définir les boutons
 */
struct bouton_s {
	int numSprite;
	int numSpritePresse;
	int x;
	int y;
	int longueur;
	int largeur;
};

typedef struct bouton_s bouton;

/*
 * Affiche le numSprite d'une structure bouton_s
 */
void afficher_bouton(bouton b);

/*
 * Vérifie si le bouton est presser ou non, et affiche une autre image si la souris passe
 * sur le bouton
 *
 * Postcondition : retourne 0 si le bouton est presser et 1 dans le cas contraire
 */
int presser_bouton(bouton* b);

/*
 * affiche l'écrant de défaite quand la partie est fini
 *
 * Précondition : val correspond au jouer qui a perdu, la phrase est différente en
 * fonction du mode de jeu (voir la fonction)
 *
 * Postcondition ; retourne 0 si l'utilisateur a appuyer sur le bouton menu, retourne
 * 1 si l'utilisateur a appuyer sur le bouton quitter
 */
int ecran_perdu(int val, bouton menu, bouton quitter);

/*
 * Affiche à l'écrant et a la console (si le programme a été lancé depuis la console)
 * si il y a une erreur critique et que le programme ne peut pas fonctionner
 *
 * Précondition : p doit valoir -1 ou -2 ou 1 suivant l'erreur (voir la fonction)
 *
 * Postcondition : quitte le programme brutalement avec exit
 */
void erreur(int p);

/*
 * Affiche l'écran de menu
 *
 * Précondition : le spriteNum doit être le numéro de sprite du bouton : "nuBouton"
 */
void ecran_menu(bouton joueur1, bouton joueurs2, bouton gauche, bouton droite,
				int spriteNum);

#endif
