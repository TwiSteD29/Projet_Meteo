#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"fonctions_tri_AVL.h"

int min(int a, int b);
int max(int a, int b);

//*******************************************************************************************
//temp1

int tempMode1ABR();
Station* insertABR(Station* a,int ID, float temp, float temp_min, float temp_max);
Station* creationArbre(int a,float temp, float temp_min, float temp_max);
void parcoursInfixe(Station* a);

//*******************************************************************************************
//pres1

Station* creationArbre_pres(int a,int pres);
Station* insertABR_pres(Station* a, int ID, int pres);
void parcoursInfixe_pres(Station* a);
int presMode1ABR();

//*******************************************************************************************
//temp2

int tempMode2ABR();
Station* creationArbre_temp2(struct date date,int temp);
Station* insertABR_temp2(Station* a, struct date date,int temp);
void parcoursInfixe_temp2(Station* a);

//*******************************************************************************************
//pres2

int presMode2ABR();
Station* creationArbre_pres2(struct date date,int pres);
Station* insertABR_pres2(Station* a, struct date date,int pres);
void parcoursInfixe_pres2(Station* a);


//*******************************************************************************************
//temp3

int tempMode3ABR();
Station* creationArbre_temp3(struct date date,int ID,float temp);
Station* insertABR_temp3(Station* a, struct date date,int ID,float temp);
void parcoursInfixe_temp3(Station* a);

//****

int tempMode3ABR_2();
Station* creationArbre_temp3_2(int ID,struct date date,float temp);
Station* insertABR_temp3_2(Station* a, int ID, struct date date, float temp);
void parcoursInfixe_temp3_2(Station* a);

//*******************************************************************************************
//pres3
int presMode3ABR();
Station* creationArbre_pres3(struct date date,int ID,int pres);
Station* insertABR_pres3(Station* a, struct date date,int ID,int pres);
void parcoursInfixe_pres3(Station* a);

//****

int presMode3ABR_2();
Station* creationArbre_pres3_2(int ID,struct date date,int pres);
Station* insertABR_pres3_2(Station* a, int ID, struct date date,int pres);
void parcoursInfixe_pres3_2(Station* a);

//*********************************************************************************************
//altitude

int ABR_alt();
Station* creationArbre_alt(int a, float lat, float lon);
Station* insertABR_alt(Station* a, int alt, float lat, float lon);
void parcoursInfixe_alt(Station* a);

//*********************************************************************************************
//humidite

int ABR_hum();
Station* creationArbre_hum(int a,int hum,float lat, float lon);
Station* creationArbre_hum1(int a,float lat, float lon);
Station* insertABR_hum(Station* a, int ID, int hum, float lat, float lon);
Station* insertABR_hum1(Station* b, int hum1, float lat, float lon);
void parcoursInfixe_hum(Station* a);
void parcoursInfixe_hum1(Station* b);

//*********************************************************************************************
//vent 

int ABR_vent();
Station* creationArbre_vent(int a,int dir_vent,float vit_vent, float lat, float lon);
Station* insertABR_vent(Station* a, int ID, int dir_vent,float vit_vent, float lat, float lon);
void parcoursInfixe_vent(Station* a);



