#include"redirection.h"


int date_filtrage(char *date_min[],char *date_max[]){
//Fonction qui permet de filtrer les dates selon l'intervalle de dates choisi par l'utilisateur.

	char line[1024];
	char saveline[1024];
        char *date;

        FILE *file = fopen("tmp1", "r");
        FILE *newFile = fopen("filtered", "w");
	rewind(newFile);
	if(file==NULL){
		printf("Erreur lors de l'ouverture d'un fichier");
		return 2;
	}
        while(fgets(line, 1024, file)){
		memset(saveline,0,1024);
		memcpy(saveline,line,1024);
		if (line != NULL) {
			date = strstr(line, ";");
			sscanf(date + 1 ,"%[^;]s", date);
		}
  
		if(strcmp(date,*date_min) > 0 && strcmp(*date_max,date) > 0){
			fputs(saveline,newFile);
		}
    	}
    	fclose(file);
    	fclose(newFile);
	remove("tmp1");
	rename("filtered","tmp1");
    	return 0;
}

int territoire_filtrage(char *p1[]){ 
//Fonction qui permet de déterminer la zone géographique choisi par l'utilisateur en fonction des paramètres d'entrée.

	float Xmax,Xmin,Ymin,Ymax,Xmax2,Xmin2,Ymin2,Ymax2;
		if(strchr(*p1,'5')!=NULL){ 
			printf("Territoire : France\n");
			Xmax=52.0;
			Xmin=41.0;
			Ymin=-6.0;
	    		Ymax=10.0;
			
			Xmax2=1000;
			Xmin2=1000;
			Ymin2=1000;
	    		Ymax2=1000;
		}
		else if(strchr(*p1,'6')!=NULL){ 
			printf("Territoire : Guyane\n");
			Xmax=9.28;
			Xmin=-0.23;
			Ymin=-62.70;
	    		Ymax=-50.30;
		
			Xmax2=1000;
			Xmin2=1000;
			Ymin2=1000;
	    		Ymax2=1000;
		}	
		else if(strchr(*p1,'7')!=NULL){ 
			printf("Territoire : SaintPierre\n");
			Xmax=47.17;
			Xmin=46.70;
			Ymin=-56.50;
	    		Ymax=-56;
		
			Xmax2=1000;
			Xmin2=1000;
			Ymin2=1000;
	    		Ymax2=1000;
		}	
		else if(strchr(*p1,'8')!=NULL){ 
			printf("Territoire : Antilles\n");
			Xmax=-2.55;
			Xmin=-26.82;
			Ymin=41.44;
	    		Ymax=63.44;

			Xmax2=21.05;
			Xmin2=11.60;
			Ymin2=-75.32;
	    		Ymax2=-58.31;
		}	
		else if(strchr(*p1,'9')!=NULL){ 
			printf("Territoire : Ocean\n");
			Xmax=-28.26;
			Xmin=-61.59;
			Ymin=26.10;
	    		Ymax=106.48;
			
			Xmax2=1000;
			Xmin2=1000;
			Ymin2=1000;
	    		Ymax2=1000;
		}	
		else if(strchr(*p1,'0')!=NULL){ 
			printf("Territoire : Antarctique\n");
			Xmax=-62.70;
			Xmin=-82.80;
			Ymin=73.20;
	    		Ymax=163;

			Xmax2=1000;
			Xmin2=1000;
			Ymin2=1000;
	    		Ymax2=1000;
		}	
		territoire(Xmax,Xmin,Ymin,Ymax,Xmax2,Xmin2,Ymin2,Ymax2);
}



int  redirection( char *p1[], char *p2[],char *p3[]){ 
//Fonction qui permet de rediriger vers le bon mode de tri selon les paramètres d'entrée.
	
	if((strchr(*p1,'t') !=NULL) && (strchr(*p1,'1') !=NULL)){ //temp1
		
	
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			tempMode1ABR();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			tempMode1AVL();
		} 
	}
	
	else if((strchr(*p1,'t') !=NULL) && (strchr(*p1,'2') !=NULL)){ //temp2
		
		
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			tempMode2ABR();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			tempMode2AVL();
		} 
	} 

	else if((strchr(*p1,'t') !=NULL) && (strchr(*p1,'3') !=NULL)){ //temp3
		

		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			tempMode3ABR();
			tempMode3ABR_2();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			//tempMode3AVL();
			
		} 
	} 

	else if((strchr(*p1,'r') !=NULL) && (strchr(*p1,'1') !=NULL)){ //pression1
		
	
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			presMode1ABR();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			Mode1AVL_pres();
		} 
	} 

	else if((strchr(*p1,'r') !=NULL) && (strchr(*p1,'2') !=NULL)){ //pression2
		

		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			presMode2ABR();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			presMode2AVL();
		} 
	} 

	else if((strchr(*p1,'r') !=NULL) && (strchr(*p1,'3') !=NULL)){ //pression3
		

		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			presMode3ABR();
			presMode3ABR_2();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
		} 
	} 

	else if((strchr(*p1,'v') !=NULL)){ //vent
		
	
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			ABR_vent();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			AVL_vent();
		} 
	} 

	else if((strchr(*p1,'h') !=NULL)){ //humidite
		
	
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			ABR_hum();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			AVL_hum();
		} 
	} 

	else if((strchr(*p1,'l') !=NULL)){ //altitude
		
	
		if((strchr(*p2,'t') !=NULL) && (strchr(*p2,'b') !=NULL)){
		//On appelle fonction de tri par tab
			
		}
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'r') !=NULL)){
		//On appelle fonction de tri par abr
			
			ABR_alt();
		} 
		else if((strchr(*p2,'a') !=NULL) && (strchr(*p2,'l') !=NULL)){
		//On appelle fonction de tri par avl
			
			AVL_alt();
		} 
	} 
	return 0;
}
