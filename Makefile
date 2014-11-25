HEADER_FILES = mob.h grille.h liste.h
CC = gcc -std=c99 -o


prog: main.o mob.o grille.o liste.o $(HEADER_FILES)
	$(CC) prog main.o mob.o grille.o liste.o

main.o: main.c $(HEADER_FILES)
	$(CC) main.o -c main.c 

mob.o: mob.c $(HEADER_FILES)
	$(CC) mob.o -c mob.c

grille.o: grille.c $(HEADER_FILES)
	$(CC) grille.o -c grille.c

liste.o: liste.c $(HEADER_FILES)
	$(CC) liste.o -c liste.c

