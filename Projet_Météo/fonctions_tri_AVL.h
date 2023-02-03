#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include"struct.h"

int min1(int a, int b);
int max1(int a, int b);
int max3(int a, int b, int c);
int min3(int a, int b, int c);
Station* rotationGauche(Station* a);
Station* rotationDroite(Station* a);
Station* doubleRotationGauche(Station *a);
Station* doubleRotationDroite(Station *a);
Station* equilibrageAVL(Station *a);

//*********************************************************************************************

//temp1

Station* creationArbreAVL(int a, float temp, float temp_min, float temp_max);
Station* insertionAVL(Station* a, int ID, int *h,float temp, float temp_min, float temp_max);
void parcoursInfixeAVL(Station* a);
int tempMode1AVL();

//*********************************************************************************************

//pres1

Station* creationArbreAVL_pres(int a, int pres);
Station* insertionAVL_pres(Station* a, int ID, int *h,int pres);
void parcoursInfixeAVL_pres(Station* a);
int Mode1AVL_pres();

//*********************************************************************************************

//temp2
Station* creationArbreAVL_temp2(struct date date,int temp);
Station* insertAVL_temp2(Station* a, struct date date,int temp,int *h);
void parcoursInfixeAVL_temp2(Station* a);
int tempMode2AVL();

//*********************************************************************************************

//pres2
Station* creationArbreAVL_pres2(struct date date,int pres);
Station* insertAVL_pres2(Station* a, struct date date,int pres,int *h);
void parcoursInfixeAVL_pres2(Station* a);
int presMode2AVL();

//*********************************************************************************************

//altitude
Station* creationArbreAVL_alt(int a, float lat, float lon);
Station* insertionAVL_alt(Station* a, int alt, int *h,float lat,float lon);
void parcoursInfixeAVL_alt(Station* a);
int AVL_alt();

//*******************************************************************************************

//humidité
Station* creationArbreAVL_hum(int a,int hum,float lat, float lon);
Station* creationArbreAVL_hum1(int a,float lat, float lon);
Station* insertionAVL_hum(Station* a, int ID, int *h,int hum,float lat, float lon);
Station* insertionAVL_hum1(Station* a,int hum1,int *h1,float lat, float lon);
void parcoursInfixeAVL_hum(Station* a);
void parcoursInfixeAVL_hum1(Station* b);
int AVL_hum();

//*******************************************************************************************

//vent
Station* creationArbreAVL_vent(int a,int dir_vent,float vit_vent, float lat, float lon);
Station* insertionAVL_vent(Station* a, int ID, int *h,int dir_vent,float vit_vent, float lat, float lon);
void parcoursInfixeAVL_vent(Station* a);
int AVL_vent();


//*******************************************************************************************


/*
Station* creationArbreAVL_temp3(struct date date,int ID,float temp);
Station* insertAVL_temp3(Station* a, struct date date,int ID,float temp,int *h);
void parcoursInfixeAVL_temp3(Station* a);
int tempMode3AVL();

Station* creationArbreAVL_temp3_2(int ID,struct date date,float temp);
Station* insertAVL_temp3_2(Station* b, int ID, struct date date, float temp,int *h1);
void parcoursInfixeAVL_temp3_2(Station* b);
*/

//*******************************************************************************************




