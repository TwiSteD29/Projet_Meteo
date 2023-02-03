#include"fonctions_tri_ABR.h"

int min(int a, int b){
	return (a<b ? a:b);
}

int max(int a, int b){
	return (a>b ? a:b);
}

//**********************************************************************************************************
//temp1

Station* creationArbre(int a,float temp, float temp_min, float temp_max){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.

	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->temp=temp;
	new->temp_min=temp_min;
	new->temp_max=temp_max;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR(Station* a, int ID, float temp, float temp_min, float temp_max){
//Fonction qui permet d'insérer chaque valeur ID de station selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre(ID,temp,temp_min,temp_max);
	}
	else if(ID<a->elmt){
		a->fg=insertABR(a->fg,ID,temp,temp_min,temp_max);
	}
	else if(ID>a->elmt){
		a->fd=insertABR(a->fd,ID,temp,temp_min,temp_max);
	}
	else if(ID==a->elmt){
		if(temp_min==0 && temp_max==0){
			a->temp_min=min(temp,a->temp_min);
			a->temp_max=max(temp,a->temp_max);
			a->temp=(a->temp_min+a->temp_max)/2;
		}
		else{
			a->temp_min=min(a->temp_min,temp_min);
			a->temp_max=max(a->temp_max,temp_max);
			a->temp=(a->temp_min+a->temp_max)/2;
		}
	}	
	return a;
}

void parcoursInfixe(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à un noeud, dans l'ordre croissant des valeurs des noeuds pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixe(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		fprintf(newFile,"%d;%f;%f;%f; \n", a->elmt, a->temp, a->temp_min, a->temp_max);
		fclose(newFile);

		parcoursInfixe(a->fd);
	}
}


int tempMode1ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station, sa temp moyenne, sa temp min et sa temp max pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.

	remove("filtered");
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("temp1","r");
	rewind(file);
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%f;%f;%f; \n",&stat.ID,&stat.temp,&stat.temp_min,&stat.temp_max);		
	a=creationArbre(stat.ID,stat.temp,stat.temp_min,stat.temp_max);
	
	while(fgets(line,1024,file)){
		
		fscanf(file,"%d;%f;%f;%f; \n",&stat.ID,&stat.temp,&stat.temp_min,&stat.temp_max);
		a=insertABR(a,stat.ID,stat.temp,stat.temp_min,stat.temp_max);
	}
	parcoursInfixe(a);
	fclose(file);
	
	
	return 0;
}


//********************************************************************************************************************
//pres1

Station* creationArbre_pres(int a,int pres){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->pres=pres;
	new->pres_min=0;
	new->pres_max=0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_pres(Station* a, int ID, int pres){
//Fonction qui permet d'insérer chaque valeur ID de station selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_pres(ID,pres);
	}
	else if(ID<a->elmt){
		a->fg=insertABR_pres(a->fg,ID,pres);
	}
	else if(ID>a->elmt){
		a->fd=insertABR_pres(a->fd,ID,pres);
	}
	else if(ID==(a->elmt)){
		if(a->pres_min==0 && a->pres_max==0){
			a->pres_min=min(pres,a->pres);	
			a->pres_max=max(pres,a->pres);
		}
		else{
			a->pres_min=min(pres,a->pres_min);
			a->pres_max=max(pres,a->pres_max);
			a->pres=(a->pres_min+a->pres_max)/2;
		}
	}	
	return a;
}

void parcoursInfixe_pres(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à un noeud, dans l'ordre croissant des valeurs des noeuds pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixe_pres(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%d;%d;%d; \n", a->elmt, a->pres,a->pres_min,a->pres_max);
		fclose(newFile);

		parcoursInfixe_pres(a->fd);
		
	}
}


int presMode1ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station et sa pression pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("pres1","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%d; \n",&stat.ID,&stat.pres);
	if(stat.pres!=0){
		a=creationArbre_pres(stat.ID,stat.pres);
	}
	while(fgets(line,1024,file)){
		
		fscanf(file,"%d;%d; \n",&stat.ID,&stat.pres);
		if(stat.pres!=0){
			a=insertABR_pres(a,stat.ID,stat.pres);
		}
	}
	parcoursInfixe_pres(a);
	fclose(file);
	return 0;
}

//***************************************************************************************************************
//temp2

Station* creationArbre_temp2(struct date date,int temp){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->date=date;
	new->temp=temp;
	new->compteur=1;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_temp2(Station* a, struct date date,int temp){
//Fonction qui permet d'insérer chaque date selon le principe de l'arbre binaire de recherche.
	
	if(a==NULL){
		return creationArbre_temp2(date,temp);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertABR_temp2(a->fg,date,temp);
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertABR_temp2(a->fg,date,temp);
	}
	else if(date.annee==annee && date.mois==mois && date.jour<jour){
		a->fg=insertABR_temp2(a->fg,date,temp);
	}	
	else if(date.annee>annee){
		a->fd=insertABR_temp2(a->fd,date,temp);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertABR_temp2(a->fd,date,temp);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertABR_temp2(a->fd,date,temp);
	}	
	else if(date.annee==annee && date.mois==mois && date.jour==jour){
		a->compteur=a->compteur+1;
		a->temp=a->temp+temp;
	}
	return a;
}

void parcoursInfixe_temp2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_temp2(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->temp=(a->temp)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%f; \n", a->date.annee, a->date.mois,a->date.jour,a->temp);
		fclose(newFile);
		
		parcoursInfixe_temp2(a->fd);
	}
}



int tempMode2ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère la date et la température de chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("temp2","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d-%d-%d;%f; \n",&date.annee,&date.mois,&date.jour,&stat.temp);
	a=creationArbre_temp2(date,stat.temp);
	while(fgets(line, 1024, file)){
		fscanf(file,"%d-%d-%d;%f; \n",&date.annee,&date.mois,&date.jour,&stat.temp);
		a=insertABR_temp2(a,date,stat.temp);
	}
	parcoursInfixe_temp2(a);
	fclose(file);
	return 0;
}


//**********************************************************************************************************
//pres2

Station* creationArbre_pres2(struct date date,int pres){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station.

	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->date=date;
	new->pres=pres;
	new->compteur=1;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_pres2(Station* a, struct date date,int pres){
//Fonction qui permet d'insérer chaque date selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_pres2(date,pres);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertABR_pres2(a->fg,date,pres);
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertABR_pres2(a->fg,date,pres);
	}
	else if(date.annee==annee && date.mois==mois && date.jour<jour){
		a->fg=insertABR_pres2(a->fg,date,pres);
	}	
	else if(date.annee>annee){
		a->fd=insertABR_pres2(a->fd,date,pres);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertABR_pres2(a->fd,date,pres);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertABR_pres2(a->fd,date,pres);
	}	
	else if(date.annee==annee && date.mois==mois && date.jour==jour){
		a->compteur=a->compteur+1;
		a->pres=a->pres+pres;
	}
	return a;
}

void parcoursInfixe_pres2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_pres2(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->pres=(a->pres)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%d; \n", a->date.annee, a->date.mois,a->date.jour,a->pres);
		fclose(newFile);
		
		parcoursInfixe_pres2(a->fd);
	}
}


int presMode2ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère la date et la pression de chaque station pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("pres2","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d-%d-%d;%d; \n",&date.annee,&date.mois,&date.jour,&stat.pres);
	if(stat.pres!=0){
		a=creationArbre_pres2(date,stat.pres);
	}
	while(fgets(line, 1024, file)){
		fscanf(file,"%d-%d-%d;%d; \n",&date.annee,&date.mois,&date.jour,&stat.pres);
		if(stat.pres!=0){
			a=insertABR_pres2(a,date,stat.pres);
		}
	}
	parcoursInfixe_pres2(a);
	fclose(file);
	return 0;
}


//**********************************************************************************************************
//temp3

Station* creationArbre_temp3(struct date date,int ID,float temp){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->ID=ID;
	new->date=date;
	new->temp=temp;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}


Station* insertABR_temp3(Station* a, struct date date,int ID,float temp){
//Fonction qui permet d'insérer chaque date selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_temp3(date,ID,temp);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertABR_temp3(a->fg,date,ID,temp);
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertABR_temp3(a->fg,date,ID,temp);
	}
	else if(date.annee==annee && date.mois==mois && date.jour<=jour){
		a->fg=insertABR_temp3(a->fg,date,ID,temp);
	}	
	else if(date.annee>annee){
		a->fd=insertABR_temp3(a->fd,date,ID,temp);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertABR_temp3(a->fd,date,ID,temp);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertABR_temp3(a->fd,date,ID,temp);
	}	
	return a;
}


void parcoursInfixe_temp3(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_temp3(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		fprintf(newFile,"%d;%d-%02d-%02d;%f; \n",a->ID, a->date.annee, a->date.mois,a->date.jour,a->temp);
		fclose(newFile);
		
		parcoursInfixe_temp3(a->fd);
	}
}



int tempMode3ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la date et la température de chaque station pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("temp3","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
	a=creationArbre_temp3(date,stat.ID,stat.temp);
	while(fgets(line, 1024, file)){
		fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
		a=insertABR_temp3(a,date,stat.ID,stat.temp);
	}
	parcoursInfixe_temp3(a);
	fclose(file);
	return 0;
}

//****

Station* creationArbre_temp3_2(int ID,struct date date,float temp){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->compteur=1;
	new->ID=ID;
	new->date=date;
	new->temp=temp;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_temp3_2(Station* a, int ID, struct date date, float temp){
//Fonction qui permet d'insérer chaque ID de station pour chaque date différente selon le principe de l'arbre binaire de recherche.	
		if(a==NULL){
			return creationArbre_temp3_2(ID,date,temp);
		}

		int annee=a->date.annee;
		int mois=a->date.mois;
		int jour=a->date.jour;

		if(date.jour!=jour || date.mois!=mois || date.annee!=annee){
			a->fd=insertABR_temp3_2(a->fd,ID,date,temp);
		}
		else if(ID<a->ID){
			a->fg=insertABR_temp3_2(a->fg,ID,date,temp);
		}
		else if(ID>a->ID){
			a->fd=insertABR_temp3_2(a->fd,ID,date,temp);
		}
		else if(ID==(a->ID)){
			a->compteur=a->compteur+1;
			a->temp=a->temp+temp;
		}	
		return a;
	
}

void parcoursInfixe_temp3_2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque ID de station, dans l'ordre croissant pour chaque date pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_temp3_2(a->fg);
		FILE *newFile = fopen ("filtered2", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->temp=(a->temp)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%d;%f; \n",a->date.annee, a->date.mois,a->date.jour,a->ID,a->temp);
		fclose(newFile);
		
		parcoursInfixe_temp3_2(a->fd);
	}
}

int tempMode3ABR_2(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la date et la température de chaque station pour chaque ligne du fichier intermédiaire qui est déjà trié par ordre chronologique.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered2");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("filtered","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 4;	// fichier intermédiaire
	}
	struct date date;
	fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
	a=creationArbre_temp3_2(stat.ID,date,stat.temp);
	while(fgets(line, 1024, file)){
		fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
		a=insertABR_temp3_2(a,stat.ID,date,stat.temp);
	}
	parcoursInfixe_temp3_2(a);
	fclose(file);
	return 0;
}


//**********************************************************************************************************
//pres3

Station* creationArbre_pres3(struct date date,int ID,int pres){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->ID=ID;
	new->date=date;
	new->pres=pres;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}


Station* insertABR_pres3(Station* a, struct date date,int ID,int pres){
//Fonction qui permet d'insérer chaque date selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_pres3(date,ID,pres);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertABR_pres3(a->fg,date,ID,pres);
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertABR_pres3(a->fg,date,ID,pres);
	}
	else if(date.annee==annee && date.mois==mois && date.jour<=jour){
		a->fg=insertABR_pres3(a->fg,date,ID,pres);
	}	
	else if(date.annee>annee){
		a->fd=insertABR_pres3(a->fd,date,ID,pres);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertABR_pres3(a->fd,date,ID,pres);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertABR_pres3(a->fd,date,ID,pres);
	}	
	return a;
}

void parcoursInfixe_pres3(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_pres3(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		fprintf(newFile,"%d;%d-%02d-%02d;%d; \n",a->ID, a->date.annee, a->date.mois,a->date.jour,a->pres);
		fclose(newFile);
		
		parcoursInfixe_pres3(a->fd);
	}
}

int presMode3ABR(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la date et la pression de chaque station pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("pres3","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d;%d-%d-%d;%d; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.pres);
	if(stat.pres!=0){
		a=creationArbre_pres3(date,stat.ID,stat.pres);
	}
	while(fgets(line, 1024, file)){
		fscanf(file,"%d;%d-%d-%d;%d; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.pres);
		if(stat.pres!=0){
			a=insertABR_pres3(a,date,stat.ID,stat.pres);
		}
	}
	parcoursInfixe_pres3(a);
	fclose(file);
	return 0;
}

//*****

Station* creationArbre_pres3_2(int ID,struct date date,int pres){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->compteur=1;
	new->ID=ID;
	new->date=date;
	new->pres=pres;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_pres3_2(Station* a, int ID, struct date date,int pres){
//Fonction qui permet d'insérer chaque ID de station pour chaque date différente selon le principe de l'arbre binaire de recherche.	
		if(a==NULL){
			return creationArbre_pres3_2(ID,date,pres);
		}

		int annee=a->date.annee;
		int mois=a->date.mois;
		int jour=a->date.jour;

		if(date.jour!=jour || date.mois!=mois || date.annee!=annee){
			a->fd=insertABR_pres3_2(a->fd,ID,date,pres);
		}
		else if(ID<a->ID){
			a->fg=insertABR_pres3_2(a->fg,ID,date,pres);
		}
		else if(ID>a->ID){
			a->fd=insertABR_pres3_2(a->fd,ID,date,pres);
		}
		else if(ID==(a->ID)){
			a->compteur=a->compteur+1;
			a->pres=a->pres+pres;
		}	
		return a;
	
}

void parcoursInfixe_pres3_2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque ID de station, dans l'ordre croissant pour chaque date pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixe_pres3_2(a->fg);
		FILE *newFile = fopen ("filtered2", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->pres=(a->pres)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%d;%d; \n",a->date.annee, a->date.mois,a->date.jour,a->ID,a->pres);
		fclose(newFile);
		
		parcoursInfixe_pres3_2(a->fd);
	}
}



int presMode3ABR_2(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la date et la pression de chaque station pour chaque ligne du fichier intermédiaire qui est déjà trié par ordre chronologique.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered2");
	char line[1024];
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("filtered","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 4; // fichier intermédiaire
	}
	struct date date;
	fscanf(file,"%d;%d-%d-%d;%d; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.pres);
	a=creationArbre_pres3_2(stat.ID,date,stat.pres);
	while(fgets(line, 1024, file)){
		fscanf(file,"%d;%d-%d-%d;%d; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.pres);
		a=insertABR_pres3_2(a,stat.ID,date,stat.pres);
	}
	parcoursInfixe_pres3_2(a);
	fclose(file);
	return 0;
}

//********************************************************************************************************
//altitude

Station* creationArbre_alt(int a, float lat, float lon){
//Fonction qui permet de créer un noeud par rapport l'altitude.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->lon=lon;
	new->lat=lat;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_alt(Station* a, int alt, float lat, float lon){
//Fonction qui permet d'insérer la valeur d'altitude de chaque station, pour chaque ligne, selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_alt(alt,lat,lon);
	}
	else if(alt<=a->elmt){
		if(a->lat!=lat || a->lon!=lon){
			a->fg=insertABR_alt(a->fg,alt,lat,lon);
		}
	}
	else if(alt>a->elmt){
		a->fd=insertABR_alt(a->fd,alt,lat,lon);
	}
	return a;
}

void parcoursInfixe_alt(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque station, dans l'ordre décroissant de la valeur de l'altitude, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixe_alt(a->fd);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%f;%f; \n", a->elmt,a->lat,a->lon);
		fclose(newFile);

		parcoursInfixe_alt(a->fg);
		
	}
}


int ABR_alt(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'altitude et les coordonnées de chaque station pour chaque ligne du fichier.
//Ensuite on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("altitude","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%f,%f;%d; \n",&stat.lat,&stat.lon,&stat.alt);
	
	a=creationArbre_alt(stat.alt,stat.lat,stat.lon);

	while(fgets(line,1024,file)){
		
		fscanf(file,"%f,%f;%d; \n",&stat.lat,&stat.lon,&stat.alt);
	
		a=insertABR_alt(a,stat.alt,stat.lat,stat.lon);
		
	}
	parcoursInfixe_alt(a);
	fclose(file);
	
	
	return 0;
}


//***********************************************************************************************************
//humidite

Station* creationArbre_hum(int a,int hum,float lat, float lon){
//Fonction qui permet de créer un noeud par rapport à l'ID de station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->hum=hum;
	new->lon=lon;
	new->lat=lat;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* creationArbre_hum1(int a,float lat, float lon){
//Fonction qui permet de créer un noeud par rapport l'humidité.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->lon=lon;
	new->lat=lat;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_hum(Station* a, int ID, int hum, float lat, float lon){
//Fonction qui permet d'insérer chaque ID de station selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_hum(ID,hum,lat,lon);
	}
	else if(ID<a->elmt){
		a->fg=insertABR_hum(a->fg,ID,hum,lat,lon);
	}
	else if(ID>a->elmt){
		a->fd=insertABR_hum(a->fd,ID,hum,lat,lon);
	}
	else if(ID==a->elmt){
		a->hum=max(a->hum,hum);

	}	
	return a;
}

Station* insertABR_hum1(Station* b, int hum1, float lat, float lon){
//Fonction qui permet d'insérer chaque valeur d'humidité selon le principe de l'arbre binaire de recherche.
	if(b==NULL){
		return creationArbre_hum1(hum1,lat,lon);
	}
	else if(hum1<=b->elmt){
		b->fg=insertABR_hum1(b->fg,hum1,lat,lon);
	}
	else if(hum1>b->elmt){
		b->fd=insertABR_hum1(b->fd,hum1,lat,lon);
	}	
	return b;
}


void parcoursInfixe_hum(Station* a){
//Fonction qui permet d'écrire dans un fichier intermédiaire les lignes associées à chaque station, dans l'ordre croissant de la valeur de l'ID de la station, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixe_hum(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%d;%f,%f; \n", a->elmt, a->hum, a->lat, a->lon);
		fclose(newFile);

		parcoursInfixe_hum(a->fd);
		
	}
}


void parcoursInfixe_hum1(Station* b){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque station, dans l'ordre décroissant de la valeur de l'humidité de la station, pour chaque ligne, en parcourant l'arbre.
	if(b!=NULL){
		
		parcoursInfixe_hum1(b->fd);

		FILE *newFile1 = fopen ("filtered1", "a");
		rewind(newFile1);
		if(newFile1==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile1,"%d;%f;%f; \n", b->elmt,b->lat, b->lon);
		fclose(newFile1);

		parcoursInfixe_hum1(b->fg);
	}
}

int ABR_hum(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,l'humidité et les coordonnées de chaque station pour chaque ligne du fichier.
//On exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
//Ensuite on lit chaque ligne du fichier intermédiaire qui est trié par ordre croissant de l'ID de station et on récupère l'ID, l'humidité et les coordonnées de chaque station.
//Enfin on exécute les fonctions creationArbre et insertABR avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("humidite","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%d;%f,%f; \n",&stat.ID,&stat.hum,&stat.lat,&stat.lon);
	
	a=creationArbre_hum(stat.ID,stat.hum,stat.lat,stat.lon);

	while(fgets(line,1024,file)){
		
		fscanf(file,"%d;%d;%f,%f; \n",&stat.ID,&stat.hum,&stat.lat,&stat.lon);
	
		a=insertABR_hum(a,stat.ID,stat.hum,stat.lat,stat.lon);
		
	}
	parcoursInfixe_hum(a);
	fclose(file);
  	remove("filtered1");
	FILE* file1 =fopen ("filtered","r");
	Station *b;
	Station stat1;
	rewind(file1);
	if (file1==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 4;	// fichier intermédiaire
	}
	fscanf(file1,"%d;%d;%f,%f; \n",&stat1.ID,&stat1.hum,&stat1.lat,&stat1.lon);
	
	b=creationArbre_hum1(stat1.hum,stat1.lat,stat1.lon);

	while(fgets(line,1024,file1)){
		
		fscanf(file1,"%d;%d;%f,%f; \n",&stat1.ID,&stat1.hum,&stat1.lat,&stat1.lon);

		b=insertABR_hum1(b,stat1.hum,stat1.lat,stat1.lon);
		
	}
	parcoursInfixe_hum1(b);	
	fclose(file1);
	remove("filtered");
	rename("filtered1","filtered");
	return 0;
}

//********************************************************************************************************************
//vent

Station* creationArbre_vent(int a,int dir_vent,float vit_vent, float lat, float lon){
//Fonction qui permet de créer un noeud par rapport à l'ID de station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->vit_vent=vit_vent;
	new->dir_vent=dir_vent;
	new->lon=lon;
	new->lat=lat;
	new->compteur=1;
	new->ventX=0;
	new->ventY=0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertABR_vent(Station* a, int ID, int dir_vent,float vit_vent, float lat, float lon){
//Fonction qui permet d'insérer chaque noeud par rapport à l'ID de chaque station selon le principe de l'arbre binaire de recherche.
	if(a==NULL){
		return creationArbre_vent(ID,dir_vent,vit_vent,lat,lon);
	}
	else if(ID<a->elmt){
		a->fg=insertABR_vent(a->fg,ID,dir_vent,vit_vent,lat,lon);
	}
	else if(ID>a->elmt){
		a->fd=insertABR_vent(a->fd,ID,dir_vent,vit_vent,lat,lon);
	}
	else if(ID==a->elmt){
		a->compteur=a->compteur+1;
		a->dir_vent=a->dir_vent+dir_vent;
		a->vit_vent=a->vit_vent+vit_vent;
	}	
	return a;
}

void parcoursInfixe_vent(Station* a){
//Fonction qui permet d'écrire dans un fichier intermédiaire les vecteurs vents de chaque station et ses coordonnées, dans l'ordre croissant de la valeur de l'ID de la station, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixe_vent(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->dir_vent=(a->dir_vent)/(a->compteur);
		a->vit_vent=(a->vit_vent)/(a->compteur);
		a->ventX=cosf(a->dir_vent*3.14/180)*a->vit_vent;
		a->ventY=sinf(a->dir_vent*3.14/180)*a->vit_vent;
		fprintf(newFile,"%d;%f;%f;%f;%f; \n", a->elmt, a->ventX, a->ventY, a->lat,a->lon);
		fclose(newFile);

		parcoursInfixe_vent(a->fd);
		
	}
}


int ABR_vent(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la direction et la vitesse du vent ainsi que les coordonnées de chaque station pour chaque ligne du fichier.
	remove("filtered");
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("vent","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%d;%f;%f,%f; \n",&stat.ID,&stat.dir_vent,&stat.vit_vent,&stat.lat,&stat.lon);
	if(stat.dir_vent!=0 && stat.vit_vent!=0){
		a=creationArbre_vent(stat.ID,stat.dir_vent,stat.vit_vent,stat.lat,stat.lon);
	}
	while(fgets(line,1024,file)){
		fscanf(file,"%d;%d;%f;%f,%f; \n",&stat.ID,&stat.dir_vent,&stat.vit_vent,&stat.lat,&stat.lon);
		if(stat.dir_vent!=0 && stat.vit_vent!=0){
			a=insertABR_vent(a,stat.ID,stat.dir_vent,stat.vit_vent,stat.lat,stat.lon);
		}
	}
	parcoursInfixe_vent(a);
	fclose(file);
	return 0;
}




