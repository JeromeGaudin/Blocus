# Authors: Ranto RALIJAONA
# and    : Jérôme GAUDIN	


# CHAPITRE 1 : BUT FINAL

but : blocus;

# CHAPITRE 2 : VARIABLES

OFILES = fonctionGame.o \
		 game.o \
		 menu.o
		 
         

CC = gcc

CFLAGS = -Wall -ansi 

LIBRARY = -lgraph

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

menu.o : menu.h game.h

game.o : game.h fonctionGame.h

fonctionGame.o : fonctionGame.h

#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES

blocus : $(OFILES)
	$(CC) $(CFLAGS) -o blocus $(OFILES) $(LIBRARY)

#CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES

clean :
	-rm -f $(OFILES)
	-rm -f blocus
