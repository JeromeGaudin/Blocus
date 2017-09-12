/* Authors: Ranto RALIJAONA
 * and    : Jérôme GAUDIN	
 */

#ifndef FONCTIONGAME_H
#define FONCTIONGAME_H

/*-------------------------------------Graphique-----------------------------*/

/*
 * Affiche la grille de jeu
 *
 * Précondition : xGrille et yGrille sont les coordonnée du point en haut a gauche de 
 * la grille
 */
void afficher_grille(int xGrille, int yGrille, int nbCase);

/*
 * Affiche un sprite centré dans une case de la grille
 *
 * Précondition : i et j sont les variables qui permettent de déterminer dans quelle case
 * on veut afficher le sprite
 */
void afficher_le_sprite(int xGrille, int yGrille, int i, int j, char numSprite);

/*
 * Efface le sprite dans une case de la grille
 * Préondition : i et j sont les vraiables qui permettent de déterminer dans quelle case
 * on veut supprimer le sprite
 */
void effacer_le_sprite(int xGrille, int yGrille, int i, int j);

/*
 * Efface une zone de texte affiché à l'écran
 *
 * Précondition : x, y sont les coordonnées de la ligne d'écriture du texte, la variable
 * s correspond au texte a effacer( c'est pour connaitre sa longeur)
 */
void effacer_texte(int x, int y, char* s, int taille);

/*-------------------------------------Logique-------------------------------*/

/*
 * calcule l'empacement de la grille pour la centré sur l'écran
 *
 * retourne les valeur dans x et y, les valeurs correspondent au coin suppérieur gauche
 * de la grille
 */
void emplacement_grille(int* x, int* y, int lFenetre, int hFenetre, int nbCase);

/*
 * Crée un tableau en deux dimentions avec malloc pour pouvoir être accessible dans le
 * programme
 *
 * Précondition : n correspond à la taille du tableau(c'est un tableau carré)
 */
int ** creer_tableau(int n);

/*
 * Efface le tableau de la mémoire
 *
 * Précondition : n correspond à la taille du tableau
 */
void effacer_tableau(int ** t, int n);

/*
 * Détermine la case cliqué en fonction des coordonnées de la souris
 *
 * Poste condition : retourne l'emplacement de la case dans i et j
 */
int quelle_case(int*i, int*j, int nbCase, int xGrille,int  yGrille);

/*
 * Trouve un numéro dans un tableau en deux dimentions
 *
 * Précondition : le nombre correspond au "charactère" que l'on veut trouver dans le
 * tableau
 *
 * Postcondition : retourne l'emplacement de la case dans i et j
 */
void trouver_numero(int* i, int* j, int ** tab, int taille, int nombre);

/*
 * Vérifie si un pion peut être palcé à l'emlacement voulu (i, j) si l'empacement est
 * libre alors il ajoute le numSprite dans le tableau et fait bouger le pion 
 * graphiquement
 *
 * Précondition : x et y correspondent à l'emplacement de la grille
 *
 * Postcondition : retourne 0 si le pion a bien été placé sinon la fonction retourne 1
 */
int placer_pion(int x, int y, int i, int j, int ** tab, int taille, char numSprite);

/*
 * Vérifie si une croix peut être placé à l'emplacement voulu (i ,j) si l'emplacement est
 * libre alors il ajoute le numSprite dans le tableau et crée une croix graphiquement
 *
 * Précondition : x et y correspondent à l'emplacement de la grille
 *
 * Postcondition ; retourne 0 si le pion a bien été placé sinon la fonction retourne 1
 */
int placer_croix(int x, int y, int i, int j, int ** tab, int numSprite);

/*
 * test si le joueur a perdu
 *
 * Précondition : player correspond au numéro de sprte du joueur
 *
 * PostCondition : retourne 0 si le joueur n'a pas perdu, si le joueur a perdu alors il r
 * etourne le numéro du sprite
 */
int perdu(int ** tab, int n, int player);

#endif
