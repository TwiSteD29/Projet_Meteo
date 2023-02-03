#include"territoire.h"


int territoire(float Xmax, float Xmin, float Ymin, float Ymax,float Xmax2,float Xmin2,float Ymin2,float Ymax2){
//Fonction qui filtre le fichier de données pour ne garder que la zone géographique choisie par l'utilisateur.

	char line[1024];
	char saveline[1024];
	char saveline2[1024];
	char savecoord[1024];
	
	char *X,*Y;
	float X2,Y2;
        FILE *file = fopen("tmp1", "r");
        FILE *newFile = fopen("filtered", "w");
	rewind(newFile);
	
	if (file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
	memset(saveline,0,1024);
	memcpy(saveline,line,1024);
	while (fgets(line, 1024, file)){
       		memset(saveline,0,1024);
		memcpy(saveline,line,1024);
		memset(saveline2,0,1024);
		memcpy(saveline2,line,1024);
		if (line != NULL) {
			X = strtok(line, ";");
			for(int i=1;i<10;i++){
				X = strtok(NULL, ";,");
			}
		}
		X2=strtof(X,NULL);
		if(saveline != NULL){
			Y = strtok(saveline, ";");
			for(int i=1;i<11;i++){
				Y = strtok(NULL, ";,");
			}
		} 
		Y2=strtof(Y,NULL);
		
		if((Xmin<X2 && X2<Xmax &&  Ymin<Y2 && Y2<Ymax) || (Xmin2<X2 && X2<Xmax2 && Ymin2<Y2 && Y2<Ymax2)){
			fputs(saveline2,newFile);
		}
	}	
	
	fclose(file);		
	fclose(newFile);
	remove("tmp1");
	rename("filtered","tmp1");
	return 0;
}



