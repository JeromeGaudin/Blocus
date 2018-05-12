# Blocus

## Description

C'est un jeu tour par tour qui se joue sur une grille qui est variable(de 3 à 9). Le but du jeu est de bloquer son adversaire, pour cela à chaque tour vous devez bloquer une case et vous déplacer.

Pour avoir un apperçu de l'interface graphique vous pouvez aller [ici](http://www.iut-fbleau.fr/sitebp/doc/doc_bib_graphique/index.php)

## Utiliser l'application

### Prérequis
- Être sous Linux
- avoir l'interface graphique X11
- avoir les libraires de développement de X11


### Installation
Pour que ce jeu compile il faut installer une bibliothèque graphique qui est une simplification de la bibliotèque graphique de X11.

1. Récupérez l' [archive](http://www.iut-fbleau.fr/sitebp/doc/doc_bib_graphique/bibliotheque-graphique-iut-1.1.tar.gz). Après avoir désarchiver, lancer le script configure pour préparer la compilation et l'installation :
```
./configure --prefix=/usr --disable-exemples
```

--prefix permet de choisir le repertoire d'installation. --enable/--disable-exemples permet de construire ou non la librairie avec des exemples. (ExempleMandelbrot,ExempleSouris, ExempleGraphique, ExempleSprite). --enable/--disable-xpm permet ou non le support des images de format xpm.

2. Lancez la commande make pour la compilation et make install pour l'installation.
3. Lancez make uninstall pour la désinstallation.

Installation inspiré de [cette page](http://www.iut-fbleau.fr/sitebp/doc/doc_bib_graphique/index.php)

### Lancement
Compiler les sources avec ```Make ```
Puis lancer le fichier blocus

## Auterus
- Ranto RALIJAONA
- [Jérôme GAUDIN](https://github.com/JeromeGaudin)
