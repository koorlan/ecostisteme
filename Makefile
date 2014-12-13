HEADER_FILES = main.h mob.h grille.h liste.h eco.h libgraphique.h mobs_ia.h pecheur.h pont.h canne.h filet.h
CC = gcc -std=c99 -g -o
LIB = -lglut -lGLU -lGL -lm

prog: main.o mob.o grille.o liste.o eco.o libgraphique.o mobs_ia.o pecheur.o pont.o canne.o filet.o $(HEADER_FILES)
	$(CC) prog main.o mob.o grille.o liste.o eco.o libgraphique.o mobs_ia.o pecheur.o pont.o canne.o filet.o $(LIB)

main.o: main.c $(HEADER_FILES)
	$(CC) main.o -c main.c $(LIB)

mob.o: mob.c $(HEADER_FILES)
	$(CC) mob.o -c mob.c $(LIB)

grille.o: grille.c $(HEADER_FILES)
	$(CC) grille.o -c grille.c $(LIB)


liste.o: liste.c $(HEADER_FILES)
	$(CC) liste.o -c liste.c $(LIB)

eco.o : eco.c $(HEADER_FILES)
	$(CC) eco.o -c eco.c $(LIB)

libgraphique.o : libgraphique.c $(HEADER_FILES)
		$(CC) libgraphique.o -c libgraphique.c $(LIB)

mobs_ia.o : mobs_ia.c $(HEADER_FILES)
	$(CC) mobs_ia.o -c mobs_ia.c $(LIB)

pecheur.o : pecheur.c $(HEADER_FILES)
	$(CC) pecheur.o -c pecheur.c $(LIB) 

pont.o : pont.c $(HEADER_FILES)
	$(CC) pont.o -c pont.c $(LIB) 

canne.o : canne.c $(HEADER_FILES)
	$(CC) canne.o -c canne.c $(LIB) 

filet.o : filet.c $(HEADER_FILES)
	$(CC) filet.o -c filet.c $(LIB) 
