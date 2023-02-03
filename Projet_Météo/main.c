#include"redirection.h"


int main(int argc, char* argv[]){ 

	
	if(argc<3){ 
		printf("ERREUR\n");
		return 4;
	}

	char *p1=0;
	p1=argv[1];
	char *p2=0;
	p2=argv[2];
	char *p3=0;
	p3=argv[3];

	char *date_min=0;
	date_min=argv[1];
	char *date_max=0;
	date_max=argv[2];

	if(argv[3]!=NULL){
		if((strchr(argv[3],'z')==NULL) && (strchr(argv[3],'1')==NULL)){
			printf("Nombre d'argument : %d\n", argc);

			printf("programme exécuté : %s\n", argv[0]); 
			printf("fichier d'entrée : %s\n", argv[1]); 
			printf("Mode de tri : %s\n", argv[2]); 
			printf("Fichier de sortie : %s\n", argv[3]);
		}
	}

	if(argv[3]!=NULL){
		if((strchr(argv[3],'z')!=NULL) && (strchr(argv[3],'1')!=NULL)){ //Si l'utilisateur a choisi un intervalle pour la date alors on exécute la fonction qui va filtrer le fichier
			
			date_filtrage(&date_min,&date_max);
		}
	}
	
	if(argv[2]!=NULL){
		if((strchr(argv[2],'z')!=NULL) && (strchr(argv[2],'2')!=NULL)){ //Si l'utilisateur a choisi un territoire alors on exécute la fonction qui va définir la zone géographique.
		
			territoire_filtrage(&p1);
		}
	}	
	
	redirection(&p1,&p2,&p3);
	return 0;
}
