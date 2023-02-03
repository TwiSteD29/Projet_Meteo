all : tri_donnees

fonctions_tri_TAB.o : fonctions_tri_TAB.c fonctions_tri_TAB.h struct.h
			gcc -o fonctions_tri_TAB.o -c fonctions_tri_TAB.c 

fonctions_tri_ABR.o : fonctions_tri_ABR.c fonctions_tri_ABR.h  struct.h
			gcc -o fonctions_tri_ABR.o -c fonctions_tri_ABR.c -lm 

fonctions_tri_AVL.o : fonctions_tri_AVL.c fonctions_tri_AVL.h struct.h
			gcc -o fonctions_tri_AVL.o -c fonctions_tri_AVL.c -lm

redirection.o : redirection.c redirection.h
			gcc -o redirection.o -c redirection.c

territoire.o : territoire.c territoire.h
			gcc -o territoire.o -c territoire.c

main.o : main.c fonctions_tri_AVL.h fonctions_tri_ABR.h fonctions_tri_TAB.h redirection.h territoire.h
			gcc -o main.o -c main.c

tri_donnees : main.o fonctions_tri_AVL.o fonctions_tri_ABR.o fonctions_tri_TAB.o struct.h redirection.o territoire.o
	gcc main.o fonctions_tri_AVL.o fonctions_tri_ABR.o fonctions_tri_TAB.o redirection.o territoire.o -o tri_donnees -lm
