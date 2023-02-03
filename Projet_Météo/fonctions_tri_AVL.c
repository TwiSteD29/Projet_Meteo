#include"fonctions_tri_AVL.h"



int min1(int a, int b){
	return (a<b ? a:b);
}

int max1(int a, int b){
	return (a>b ? a:b);
}

int max3(int a, int b, int c) {
	if(a>=b && a>c){
		return a;
	}
	if(b>=a && b>c){
		return b;
	}
	if(c>=a && c>b){
		return c;
	}
}

int min3(int a, int b, int c) {
	if(a<=b && a<c){
		return a;
	}
	if(b<=a && b<c){
		return b;
	}
	if(c<=a && c<b){
		return c;
	}	
}


Station* rotationGauche(Station* a){
	Station* b;
	int h_a;
	int h_b; 
	b= a->fd;
	a->fd = b->fg;
	b->fg = a;
	h_a=a->hauteur;
	h_b=b->hauteur;
	a->hauteur = h_a-max1(h_b,0)-1;
	b->hauteur= min3(h_a-2,h_a+h_b-2,h_b-1);
	a=b;
	return a;
}

Station* rotationDroite(Station* a){
	Station* b;
	int h_a;
	int h_b; 
	b= a->fg;
	a->fg = b->fd;
	b->fd = a;
	h_a=a->hauteur;
	h_b=b->hauteur;
	a->hauteur = h_a-min1(h_b,0)+1;
	b->hauteur= max3(h_a+2,h_a+h_b+2,h_b+1);
	a=b;
	return a;
}


Station* doubleRotationGauche(Station *a){
	a->fd=rotationDroite(a->fd);
	return rotationGauche(a);
}

Station* doubleRotationDroite(Station *a){
	a->fg=rotationGauche(a->fg);
	return rotationDroite(a);
}


Station* equilibrageAVL(Station *a){
	if(a->hauteur>= 2){
		if(a->fd->hauteur >= 0){
			return rotationGauche(a);
		}
		else return doubleRotationGauche(a);
	}
	else if(a->hauteur <= -2){
		if(a->fg->hauteur <= 0){
			return rotationDroite(a);
		}
		else return doubleRotationDroite(a);
	}
	return a;

}

//*********************************************************************************************
//temp1

Station* creationArbreAVL(int a, float temp, float temp_min, float temp_max){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->temp=temp;
	new->temp_min=temp_min;
	new->temp_max=temp_max;
	new->hauteur = 0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertionAVL(Station* a, int ID, int *h,float temp, float temp_min, float temp_max){
//Fonction qui permet d'insérer chaque valeur ID de station selon le principe de l'AVL.
	if(a==NULL){
		*h=1;
		a=creationArbreAVL(ID,temp,temp_min,temp_max);
	}
	else if(ID<a->elmt){
		a->fg=insertionAVL(a->fg,ID,h,temp,temp_min,temp_max);
		*h=-*h;
	}
	else if(ID>a->elmt){
		a->fd=insertionAVL(a->fd,ID,h,temp,temp_min,temp_max);
	}
	else if(ID==a->elmt){
		if(temp_min==0 && temp_max==0){
			a->temp_min=min1(temp,a->temp_min);
			a->temp_max=max1(temp,a->temp_max);
			a->temp=(a->temp_min+a->temp_max)/2;
		}
		else{
			a->temp_min=min1(a->temp_min,temp_min);
			a->temp_max=max1(a->temp_max,temp_max);
			a->temp=(a->temp_min+a->temp_max)/2;
		}
	
		*h=0;
		return a;
	}
	if(*h!=0){
		a->hauteur=a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else *h=1;
	}
	return a;
}


void parcoursInfixeAVL(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à un noeud, dans l'ordre croissant des valeurs des noeuds pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){

		parcoursInfixeAVL(a->fg);

		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%f;%f;%f; \n", a->elmt, a->temp, a->temp_min, a->temp_max);
		fclose(newFile);

		parcoursInfixeAVL(a->fd);

	}
}


int tempMode1AVL(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station, sa temp moyenne, sa temp min et sa temp max pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	int h=0;
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("temp1","r");

	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%f;%f;%f; \n",&stat.ID,&stat.temp,&stat.temp_min,&stat.temp_max);

	a=creationArbreAVL(stat.ID,stat.temp,stat.temp_min,stat.temp_max);

	while(fgets(line,1024,file)){

		fscanf(file,"%d;%f;%f;%f; \n",&stat.ID,&stat.temp,&stat.temp_min,&stat.temp_max);

		a=insertionAVL(a,stat.ID,&h,stat.temp,stat.temp_min,stat.temp_max);

	}
	parcoursInfixeAVL(a);
	fclose(file);
	return 0;
}

//**********************************************************************************************
//pres1

Station* creationArbreAVL_pres(int a, int pres){
//Fonction qui permet de créer un noeud par rapport à l'ID de chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->pres=pres;
	new->pres_min=0;
	new->pres_max=0;
	new->hauteur = 0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertionAVL_pres(Station* a, int ID, int *h,int pres){
//Fonction qui permet d'insérer chaque valeur ID de station selon le principe de l'AVL
	if(a==NULL){
		*h=1;
		a=creationArbreAVL_pres(ID,pres);
	}
	else if(ID<a->elmt){
		a->fg=insertionAVL_pres(a->fg,ID,h,pres);
		*h=-*h;
	}
	else if(ID>a->elmt){
		a->fd=insertionAVL_pres(a->fd,ID,h,pres);
	}
	else if(ID==a->elmt){
		if(a->pres_min==0 && a->pres_max==0){
			a->pres_min=min1(pres,a->pres);	
			a->pres_max=max1(pres,a->pres);
		}
		else{
			a->pres_min=min1(pres,a->pres_min);
			a->pres_max=max1(pres,a->pres_max);
			a->pres=(a->pres_min+a->pres_max)/2;
		}	

		*h=0;
		return a;
	}
	if(*h!=0){
		a->hauteur=a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else *h=1;
	}
	return a;
}


void parcoursInfixeAVL_pres(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à un noeud, dans l'ordre croissant des valeurs des noeuds pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixeAVL_pres(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%d;%d;%d; \n", a->elmt, a->pres,a->pres_min,a->pres_max);
		fclose(newFile);

		parcoursInfixeAVL_pres(a->fd);
		
	}
}


int Mode1AVL_pres(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station et sa pression pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	int h=0;
	char line[1024];
	char saveline[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("pres1","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%d; \n",&stat.ID,&stat.pres);
	
	if(stat.pres!=0){
		a=creationArbreAVL_pres(stat.ID,stat.pres);
	}
	while(fgets(line,1024,file)){
		
		fscanf(file,"%d;%d; \n",&stat.ID,&stat.pres);
		
		if(stat.pres!=0){
		a=insertionAVL_pres(a,stat.ID,&h,stat.pres);
	}
		
	}
	parcoursInfixeAVL_pres(a);
	fclose(file);
	
	
	return 0;
}


//*********************************************************************************************
//temp2

Station* creationArbreAVL_temp2(struct date date,int temp){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->hauteur=0;
	new->date=date;
	new->temp=temp;
	new->compteur=1;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertAVL_temp2(Station* a, struct date date,int temp,int *h){
//Fonction qui permet d'insérer chaque date selon le principe de l'AVL	
	if(a==NULL){
		*h=1;
		return creationArbreAVL_temp2(date,temp);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertAVL_temp2(a->fg,date,temp,h);
		*h=-*h;
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertAVL_temp2(a->fg,date,temp,h);
		*h=-*h;
	}
	else if(date.annee==annee && date.mois==mois && date.jour<jour){
		a->fg=insertAVL_temp2(a->fg,date,temp,h);
		*h=-*h;
	}	
	else if(date.annee>annee){
		a->fd=insertAVL_temp2(a->fd,date,temp,h);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertAVL_temp2(a->fd,date,temp,h);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertAVL_temp2(a->fd,date,temp,h);
	}	
	else if(date.annee==annee && date.mois==mois && date.jour==jour){
		*h=0;
		a->compteur=a->compteur+1;
		a->temp=a->temp+temp;
	}
	if(*h!=0){
		a->hauteur = a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

void parcoursInfixeAVL_temp2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixeAVL_temp2(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->temp=(a->temp)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%f; \n", a->date.annee, a->date.mois,a->date.jour,a->temp);
		fclose(newFile);
		
		parcoursInfixeAVL_temp2(a->fd);
	}
}



int tempMode2AVL(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère la date et la température de chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	int h=0;
	Station* a=NULL;
	Station stat;
	FILE *file = fopen ("temp2","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d-%d-%d;%f; \n",&date.annee,&date.mois,&date.jour,&stat.temp);
	a=creationArbreAVL_temp2(date,stat.temp);
	while(fgets(line, 1024, file)){
		fscanf(file,"%d-%d-%d;%f; \n",&date.annee,&date.mois,&date.jour,&stat.temp);
		a=insertAVL_temp2(a,date,stat.temp,&h);
	}
	parcoursInfixeAVL_temp2(a);
	fclose(file);
	return 0;
}


//**********************************************************************************************************
//pres2

Station* creationArbreAVL_pres2(struct date date,int pres){
//Fonction qui permet de créer un noeud par rapport à la date associée à chaque station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->hauteur=0;
	new->date=date;
	new->pres=pres;
	new->compteur=1;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertAVL_pres2(Station* a, struct date date,int pres,int *h){
//Fonction qui permet d'insérer chaque date selon le principe de l'AVL	
	if(a==NULL){
		*h=1;
		return creationArbreAVL_pres2(date,pres);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		a->fg=insertAVL_pres2(a->fg,date,pres,h);
		*h=-*h;
	}
	else if(date.annee==annee && date.mois<mois){
		a->fg=insertAVL_pres2(a->fg,date,pres,h);
		*h=-*h;
	}
	else if(date.annee==annee && date.mois==mois && date.jour<jour){
		a->fg=insertAVL_pres2(a->fg,date,pres,h);
		*h=-*h;
	}	
	else if(date.annee>annee){
		a->fd=insertAVL_pres2(a->fd,date,pres,h);
	}	
	else if(date.annee==annee && date.mois>mois){
		a->fd=insertAVL_pres2(a->fd,date,pres,h);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		a->fd=insertAVL_pres2(a->fd,date,pres,h);
	}	
	else if(date.annee==annee && date.mois==mois && date.jour==jour){
		*h=0;
		a->compteur=a->compteur+1;
		a->pres=a->pres+pres;
	}
	if(*h!=0){
		a->hauteur = a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

void parcoursInfixeAVL_pres2(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque date, dans l'ordre chronologique pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		parcoursInfixeAVL_pres2(a->fg);
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		a->pres=(a->pres)/(a->compteur);
		fprintf(newFile,"%d-%02d-%02d;%d; \n", a->date.annee, a->date.mois,a->date.jour,a->pres);
		fclose(newFile);
		
		parcoursInfixeAVL_pres2(a->fd);
	}
}


int presMode2AVL(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère la date et la pression de chaque station pour chaque ligne.
//Ensuite on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	char line[1024];
	int h;
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
		a=creationArbreAVL_pres2(date,stat.pres);
	}
	while(fgets(line, 1024, file)){
		fscanf(file,"%d-%d-%d;%d; \n",&date.annee,&date.mois,&date.jour,&stat.pres);
		if(stat.pres!=0){
			a=insertAVL_pres2(a,date,stat.pres,&h);
		}
	}
	parcoursInfixeAVL_pres2(a);
	fclose(file);
	return 0;
}


//**********************************************************************************************************
//altitude

Station* creationArbreAVL_alt(int a, float lat, float lon){
//Fonction qui permet de créer un noeud par rapport l'altitude.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->lat=lat;
	new->lon=lon;
	new->hauteur = 0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertionAVL_alt(Station* a, int alt, int *h,float lat,float lon){
//Fonction qui permet d'insérer la valeur d'altitude de chaque station, pour chaque ligne, selon le principe de l'AVL
	if(a==NULL){
		*h=1;
		a=creationArbreAVL_alt(alt,lat,lon);
	}
	else if(alt<=a->elmt){
		*h=0;
		if(a->lat!=lat || a->lon!=lon){
			a->fg=insertionAVL_alt(a->fg,alt,h,lat,lon);
			*h=-*h;
		}
		return a;
	}
	else if(alt>a->elmt){
		a->fd=insertionAVL_alt(a->fd,alt,h,lat,lon);
	}
	if(*h!=0){
		a->hauteur=a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else *h=1;
	}
	return a;
}


void parcoursInfixeAVL_alt(Station* a){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque station, dans l'ordre décroissant de la valeur de l'altitude, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixeAVL_alt(a->fd);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%f;%f; \n", a->elmt,a->lat,a->lon);
		fclose(newFile);

		parcoursInfixeAVL_alt(a->fg);
		
	}
}


int AVL_alt(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'altitude et les coordonnées de chaque station pour chaque ligne du fichier.
//Ensuite on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	int h=0;
	char line[1024];
	char saveline[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("altitude","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%f,%f;%d; \n",&stat.lat,&stat.lon,&stat.alt);
	
	a=creationArbreAVL_alt(stat.alt,stat.lat,stat.lon);

	while(fgets(line,1024,file)){
		
		fscanf(file,"%f,%f;%d; \n",&stat.lat,&stat.lon,&stat.alt);
	
		a=insertionAVL_alt(a,stat.alt,&h,stat.lat,stat.lon);
		
	}
	parcoursInfixeAVL_alt(a);
	fclose(file);
	
	
	return 0;
}


//*********************************************************************************************************************
//humidite

Station* creationArbreAVL_hum(int a,int hum,float lat, float lon){
//Fonction qui permet de créer un noeud par rapport à l'ID de station.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->hum=hum;
	new->lon=lon;
	new->lat=lat;
	new->hauteur=0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* creationArbreAVL_hum1(int a,float lat, float lon){
//Fonction qui permet de créer un noeud par rapport l'humidité.
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->elmt=a;
	new->lon=lon;
	new->lat=lat;
	new->hauteur1=0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertionAVL_hum(Station* a, int ID, int *h,int hum,float lat, float lon){
//Fonction qui permet d'insérer chaque ID de station selon le principe de l'AVL
	if(a==NULL){
		*h=1;
		a=creationArbreAVL_hum(ID,hum,lat,lon);
	}
	else if(ID<a->elmt){
		a->fg=insertionAVL_hum(a->fg,ID,h,hum,lat,lon);
		*h=-*h;
	}
	else if(ID>a->elmt){
		a->fd=insertionAVL_hum(a->fd,ID,h,hum,lat,lon);
	}
	else if(ID==a->elmt){	
		a->hum=max1(a->hum,hum);
		*h=0;
		return a;
	}
	if(*h!=0){
		a->hauteur=a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else *h=1;
	}
	return a;
}

Station* insertionAVL_hum1(Station* a,int hum1,int *h1,float lat, float lon){
//Fonction qui permet d'insérer chaque valeur d'humidité selon le principe de l'AVL
	if(a==NULL){
		*h1=1;
		a=creationArbreAVL_hum1(hum1,lat,lon);
	}
	else if(hum1<=a->elmt){
		*h1=0;
		a->fg=insertionAVL_hum1(a->fg,hum1,h1,lat,lon);
		*h1=-*h1;
		return a;
	}
	else if(hum1>a->elmt){
		a->fd=insertionAVL_hum1(a->fd,hum1,h1,lat,lon);
	}
	if(*h1!=0){
		a->hauteur1=a->hauteur1 + *h1;
		a=equilibrageAVL(a);
		if(a->hauteur1==0){
			*h1=0;
		}
		else *h1=1;
	}
	return a;
}

void parcoursInfixeAVL_hum(Station* a){
//Fonction qui permet d'écrire dans un fichier intermédiaire les lignes associées à chaque station, dans l'ordre croissant de la valeur de l'ID de la station, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixeAVL_hum(a->fg);
		
		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile,"%d;%d;%f;%f; \n", a->elmt, a->hum, a->lat, a->lon);
		fclose(newFile);

		parcoursInfixeAVL_hum(a->fd);
		
	}
}

void parcoursInfixeAVL_hum1(Station* b){
//Fonction qui permet d'écrire dans un fichier les lignes associées à chaque station, dans l'ordre décroissant de la valeur de l'humidité de la station, pour chaque ligne, en parcourant l'arbre.
	if(b!=NULL){
		
		parcoursInfixeAVL_hum1(b->fd);

		FILE *newFile1 = fopen ("filtered1", "a");
		rewind(newFile1);
		if(newFile1==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}

		fprintf(newFile1,"%d;%f;%f; \n", b->elmt,b->lat, b->lon);
		fclose(newFile1);

		parcoursInfixeAVL_hum1(b->fg);
	}
}

int AVL_hum(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,l'humidité et les coordonnées de chaque station pour chaque ligne du fichier.
//On exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
//Ensuite on lit chaque ligne du fichier intermédiaire qui est trié par ordre croissant de l'ID de station et on récupère l'ID, l'humidité et les coordonnées de chaque station.
//Enfin on exécute les fonctions creationArbre et insertAVL avec les paramètres que l'on récupère.
	remove("filtered");
	int h=0;
	char line[1024];
	Station* a;
	Station stat;
	FILE *file = fopen ("humidite","r");
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	fscanf(file,"%d;%d;%f,%f; \n",&stat.ID,&stat.hum,&stat.lat,&stat.lon);
	
	a=creationArbreAVL_hum(stat.ID,stat.hum,stat.lat,stat.lon);

	while(fgets(line,1024,file)){
		
		fscanf(file,"%d;%d;%f,%f; \n",&stat.ID,&stat.hum,&stat.lat,&stat.lon);
	
		a=insertionAVL_hum(a,stat.ID,&h,stat.hum,stat.lat,stat.lon);
		
	}
	parcoursInfixeAVL_hum(a);
	fclose(file);
  	remove("filtered1");
	FILE* file1 =fopen ("filtered","r");
	int h1=0;
	Station *b;
	Station stat1;
	rewind(file1);
	if (file1==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 4;	//fichier intermédiaire
	}
	fscanf(file1,"%d;%d;%f;%f; \n",&stat1.ID,&stat1.hum,&stat1.lat,&stat1.lon);
	
	b=creationArbreAVL_hum1(stat1.hum,stat1.lat,stat1.lon);

	while(fgets(line,1024,file1)){
		
		fscanf(file1,"%d;%d;%f;%f; \n",&stat1.ID,&stat1.hum,&stat1.lat,&stat1.lon);

		b=insertionAVL_hum1(b,stat1.hum,&h1,stat1.lat,stat1.lon);
		
	}
	parcoursInfixeAVL_hum1(b);	
	fclose(file1);
	remove("filtered");
	rename("filtered1","filtered");
	return 0;
}

//**********************************************************************************************************************
//vent

Station* creationArbreAVL_vent(int a,int dir_vent,float vit_vent, float lat, float lon){
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
	new->hauteur=0;
	new->ventX=0;
	new->ventY=0;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
}

Station* insertionAVL_vent(Station* a, int ID, int *h,int dir_vent,float vit_vent, float lat, float lon){
//Fonction qui permet d'insérer chaque noeud par rapport à l'ID de chaque station selon le principe de l'AVL.
	if(a==NULL){
		*h=1;
		a=creationArbreAVL_vent(ID,dir_vent,vit_vent,lat,lon);
	}
	else if(ID<a->elmt){
		a->fg=insertionAVL_vent(a->fg,ID,h,dir_vent,vit_vent,lat,lon);
		*h=-*h;
	}
	else if(ID>a->elmt){
		a->fd=insertionAVL_vent(a->fd,ID,h,dir_vent,vit_vent,lat,lon);
	}
	else if(ID==a->elmt){
		a->compteur=a->compteur+1;
		a->dir_vent=a->dir_vent+dir_vent;
		a->vit_vent=a->vit_vent+vit_vent;	
		*h=0;
		return a;
	}
	if(*h!=0){
		a->hauteur=a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else *h=1;
	}
	return a;
}

void parcoursInfixeAVL_vent(Station* a){
//Fonction qui permet d'écrire dans un fichier intermédiaire les vecteurs vents de chaque station et ses coordonnées, dans l'ordre croissant de la valeur de l'ID de la station, pour chaque ligne, en parcourant l'arbre.
	if(a!=NULL){
		
		parcoursInfixeAVL_vent(a->fg);
		
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

		parcoursInfixeAVL_vent(a->fd);
		
	}
}

int AVL_vent(){
//Fonction qui permet de lire chaque ligne d'un fichier et qui récupère l'ID de la station,la direction et la vitesse du vent ainsi que les coordonnées de chaque station pour chaque ligne du fichier.
	remove("filtered");
	int h=0;
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
		a=creationArbreAVL_vent(stat.ID,stat.dir_vent,stat.vit_vent,stat.lat,stat.lon);
	}
	while(fgets(line,1024,file)){
		fscanf(file,"%d;%d;%f;%f,%f; \n",&stat.ID,&stat.dir_vent,&stat.vit_vent,&stat.lat,&stat.lon);
		if(stat.dir_vent!=0 && stat.vit_vent!=0){
			a=insertionAVL_vent(a,stat.ID,&h,stat.dir_vent,stat.vit_vent,stat.lat,stat.lon);
		}
	}
	parcoursInfixeAVL_vent(a);
	fclose(file);
	return 0;
}






//**********************************************************************************************************


/*Station* creationArbreAVL_temp3(struct date date,int ID,float temp){
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->ID=ID;
	new->hauteur=0;
	new->date=date;
	new->temp=temp;
	new->fg=NULL;
	new->fd=NULL;

	return new;
	free(new);
}


Station* insertAVL_temp3(Station* a, struct date date,int ID,float temp,int *h){
	if(a==NULL){
		*h=1;
		return creationArbreAVL_temp3(date,ID,temp);
	}

	int annee=a->date.annee;
	int mois=a->date.mois;
	int jour=a->date.jour;

	if(date.annee<annee){
		
		a->fg=insertAVL_temp3(a->fg,date,ID,temp,h);
		*h=-*h;
		
	}
	else if(date.annee==annee && date.mois<mois){
	
		a->fg=insertAVL_temp3(a->fg,date,ID,temp,h);
		*h=-*h;
		
	}
	else if(date.annee==annee && date.mois==mois && date.jour<jour){
	
		a->fg=insertAVL_temp3(a->fg,date,ID,temp,h);
		*h=-*h;
	}
	else if(date.annee==annee && date.mois==mois && date.jour==jour){
		*h=0;
		
		a->fg=insertAVL_temp3(a->fg,date,ID,temp,h);
		return a;
	}	
	else if(date.annee>annee){
	
		a->fd=insertAVL_temp3(a->fd,date,ID,temp,h);
	}	
	else if(date.annee==annee && date.mois>mois){
	
		a->fd=insertAVL_temp3(a->fd,date,ID,temp,h);
	}
	else if(date.annee==annee && date.mois==mois && date.jour>jour){
		
		a->fd=insertAVL_temp3(a->fd,date,ID,temp,h);
	}
	if(*h!=0){
		a->hauteur = a->hauteur + *h;
		a=equilibrageAVL(a);
		if(a->hauteur==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}


void parcoursInfixeAVL_temp3(Station* a){
	if(a!=NULL){
		parcoursInfixeAVL_temp3(a->fg);
		printf("%d;%d-%02d-%02d;%f; \n",a->ID, a->date.annee, a->date.mois,a->date.jour,a->temp);

		FILE *newFile = fopen ("filtered", "a");
		rewind(newFile);
		if(newFile==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		fprintf(newFile,"%d;%d-%02d-%02d;%f; \n",a->ID, a->date.annee, a->date.mois,a->date.jour,a->temp);
		fclose(newFile);
		
		parcoursInfixeAVL_temp3(a->fd);
	}
}


//*******

Station* creationArbreAVL_temp3_2(int ID,struct date date,float temp){
	Station* new=malloc(sizeof(Station));
	if(new==NULL){
		exit(1);
	}
	new->hauteur1=0;
	new->compteur=1;
	new->elmt=ID;
	new->date=date;
	new->temp=temp;
	new->fg=NULL;
	new->fd=NULL;	
	return new;
	free(new);
	


}

Station* insertAVL_temp3_2(Station* b, int ID, struct date date, float temp, int *h1){
	if(b==NULL){
		*h1=1;
		return creationArbreAVL_temp3_2(ID,date,temp);

	}

	int annee=b->date.annee;
	int mois=b->date.mois;
	int jour=b->date.jour;

	if(date.jour!=jour || date.mois!=mois || date.annee!=annee){
		
		b->fd=insertAVL_temp3_2(b->fd,ID,date,temp,h1);
		
	}
	if(ID<b->elmt){
		
		b->fg=insertAVL_temp3_2(b->fg,ID,date,temp,h1);
		;
		*h1=-*h1; // ici erreur de segmentation alors que théoriquement il faut bien mettre "*h=-*h"
		
	}
	else if(ID>b->elmt){
		
		b->fd=insertAVL_temp3_2(b->fd,ID,date,temp,h1);
		
	}
	else if(ID==b->elmt){
		
		b->compteur=b->compteur+1;
		b->temp=b->temp+temp;
		*h1=0;
		return b;
	}	
	if(*h1!=0){
		b->hauteur1 = b->hauteur1 + *h1;
		b=equilibrageAVL(b);
		if(b->hauteur1==0){
			*h1=0;
		}
		else{
			*h1=1;
		}
	}
	return b;
}

void parcoursInfixeAVL_temp3_2(Station* b){
	if(b!=NULL){
		parcoursInfixeAVL_temp3_2(b->fg);
		printf("%d-%02d-%02d;%d;%f; \n",b->date.annee, b->date.mois,b->date.jour,b->ID,b->temp);

		FILE *newFile1 = fopen ("filtered2", "a");
		rewind(newFile1);
		if(newFile1==NULL){
			printf("Erreur lors de l'ouverture d'un fichier");
			exit(1);
		}
		b->temp=(b->temp)/(b->compteur);
		fprintf(newFile1,"%d-%02d-%02d;%d;%f; \n",b->date.annee, b->date.mois,b->date.jour,b->ID,b->temp);
		fclose(newFile1);
		
		parcoursInfixeAVL_temp3_2(b->fd);
	}
}

int tempMode3AVL(){
	remove("filtered");
	char line[1024];
	int h=0;
	Station* a;
	Station stat;
	FILE *file = fopen ("temp3","r");
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	struct date date;
	fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
	a=creationArbreAVL_temp3(date,stat.ID,stat.temp);

	while(fgets(line, 1024, file)){
		fscanf(file,"%d;%d-%d-%d;%f; \n",&stat.ID,&date.annee,&date.mois,&date.jour,&stat.temp);
		a=insertAVL_temp3(a,date,stat.ID,stat.temp,&h);
	}
	parcoursInfixeAVL_temp3(a);
	fclose(file);

	printf("le premier tri est bien exécuté\n");

	printf("on exécute la deuxieme partie du tri\n");


	remove("filtered2");
	FILE *file1 = fopen ("filtered","r");
	int h1=0;
	Station* b;
	Station stat1;
	rewind(file1);
	if (file1==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 4;	//fichier intermédiaire
	}
	
	fscanf(file1,"%d;%d-%d-%d;%f; \n",&stat1.ID,&date.annee,&date.mois,&date.jour,&stat1.temp);
	b=creationArbreAVL_temp3_2(stat1.ID,date,stat1.temp);

	while(fgets(line, 1024, file1)){

		fscanf(file1,"%d;%d-%d-%d;%f; \n",&stat1.ID,&date.annee,&date.mois,&date.jour,&stat1.temp);

		b=insertAVL_temp3_2(b,stat1.ID,date,stat1.temp,&h1);

	}

	parcoursInfixeAVL_temp3_2(b);
	fclose(file1);
	return 0;
}

*/




