struct date{
	int jour;
	int mois;
	int annee;
};

typedef struct Station{
	int hauteur;
	int hauteur1;
	int ID;
	float temp;
	float temp_max;
	float temp_min;
	int pres;
	int pres_min;
	int pres_max;
	int dir_vent;
	float vit_vent;
	int alt;
	int hum;
	int elmt;
	int compteur;
	float lon;
	float lat;
	float ventX;
	float ventY;
	struct date date;
	struct Station *fg;
	struct Station *fd;
}Station;


