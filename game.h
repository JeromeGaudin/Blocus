/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#ifndef GAME_H
#define GAME_H

/*
 * Lance une partie 1 joueur contre l'ordinateur (il joue aléatoirement)
 *
 * Précondition : nbCase doit être positif et non nul, x et y sont les coordonnée du coin
 * en haut a gauche où la grille va être afficher, pionO, pionB, croixO, croroicB sont 
 * des numéro de sprite, xTour est la position X ou va être afficher si c'est au tour du
 * joueur bleu de joueur ou si c'est au tour du joueur orange
 * 
 * postcondition : retourne le numéro de sprite qui a perdu
 */
int un_joueur(int nbCase,int x,int y,int pionO,int pionB,int croixO,int croixB,int xTour);

/*
 * Lance une partie 1 joueur contre un autre joueur
 *
* Précondition : nbCase doit être positif et non nul, x et y sont les coordonnée du coin
 * en haut a gauche où la grille va être afficher, pionO, pionB, croixO, croroicB sont 
 * des numéro de sprite, xTour est la position X ou va être afficher si c'est au tour du
 * joueur bleu de joueur ou si c'est au tour du joueur orange
 * 
 * postcondition : retourne le numéro de sprite qui a perdu
 */
int deux_joueurs(int nbCase,int x,int y,int pionO,int pionB,int croixO,int croixB,
				 int xTour);

/*
 * Initialise tout les éléments pour ensuite appeler la fonction un_Joueur ou 
 * deux_Joueurs
 *
 * Précondition : le nombre de case doit étre positif et non nul, nbJoueur varie entre 
 * 1 et 2
 *
 * Postcondition : retourne un chiffre entre 2(y compris) et 5(y compris) en fonction
 * du joueur qui a gagner et dans quel mode de jeu, il peut retourner -1 si un malloc ou
 * un calloc n'a pas pu être effectuer, ou il peut retourner 1 si la fonction n'a pas pu
 * charger un sprite
 */
int game(int lFenetre, int hFenetre, int nbCase,int nbJoueur);

#endif
