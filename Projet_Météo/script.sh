#!/bin/bash 
#script.sh

function menu_help () {

echo " "
echo "*** Bienvenue dans le menu help ***"
echo " "
echo "* Le nombre d'argument est peut être incorrect ou alors vous avez besoin d'aide."
echo " "
echo "* Utilisation : ./$(basename $0) [-f <fichier>] (paramètre obligatoire)"
echo " "
echo "* Paramètres obligatoires (au moins un) : [-t 1/2/3] [-p 1/2/3] [-w] [-m] [-h]"
echo " "
echo "* Paramètre supplémentaires :"
echo " "
echo "* Voici les territoires disponibles : [-F](France) [-G](Guyane) [-S](SaintPierre) [-A](Antilles) [-O](Ocean) [-Q](Antarctique)"
echo "* Vous ne pouvez choisir qu'un seul territoire"
echo "* le paramètre territoire est optionnel."
echo " "
echo "* Méthode de tri : [--tab] ou [--abr] ou [--avl] (une méthode de tri maximum)."
echo "* Méthode de tri par défaut : avl"
echo " "
echo "* Paramètre de filtrage de la date : [-d YYYY-MM-DD_YYYY-MM-DD]"
echo "* Voici le format pour saisir un intervalle pour la date (min puis max) : YYYY-MM-DD_YYYY-MM-DD "
echo "* le paramètres date est optionnel."
exit 1
}


function temp () {
#Fonction qui permet de découper le fichier de données pour récupérer les colonnes nécessaires aux différents modes de températures. Ensuite on exécute le c et on affiche les graphiques selon le mode choisi.

		if [[ $modeT = 1 ]]
			then
			cut -d';' -f1,11,12,13 tmp1 > temp1
			
			./tri_donnees temp1 $tri ${fichier_sortie}
			gnuplot < fctdiag/t1_diag.gnu --persist
			cp filtered ${fichier_sortie}
			rm filtered
			rm temp1
			
		elif [[ $modeT = 2 ]]
			then
			cut -d';' -f2,11 tmp1 > temp2
			
			./tri_donnees temp2 $tri ${fichier_sortie}
			gnuplot < fctdiag/t2_diag.gnu --persist
			cp filtered ${fichier_sortie}
			rm filtered
			rm temp2

		elif [[ $modeT = 3 ]]
			then
			cut -d';' -f1,2,11 tmp1 > temp3
			
			./tri_donnees temp3 $tri ${fichier_sortie}
			gnuplot < fctdiag/t3_diag.gnu --persist
			cp filtered2 ${fichier_sortie}
			rm filtered2
			rm temp3

		elif [[ $modeT -ne 1 ]] || [[ $modeT -ne 2 ]] || [[ $modeT -ne 3 ]]
			then
			echo "Le mode sélectionné pour la température n'existe pas. Veuillez choisir le mode 1, 2 ou 3 !"
		fi
}

function pres () {
#Fonction qui permet de découper le fichier de données pour récupérer les colonnes nécessaires aux différents modes de pression. Ensuite on exécute le c et on affiche les graphiques selon le mode choisi.

		if [[ $modeP = 1 ]]
			then
			cut -d';' -f1,7 tmp1 > pres1
		
			./tri_donnees pres1 $tri ${fichier_sortie}
			gnuplot < fctdiag/pres1_diag.gnu --persist
			cp filtered ${fichier_sortie}
			rm filtered
			rm pres1

		elif [[ $modeP = 2 ]]
			then
			cut -d';' -f2,7 tmp1 > pres2
		
			./tri_donnees pres2 $tri ${fichier_sortie}
			gnuplot < fctdiag/p2_diag.gnu --persist
			cp filtered ${fichier_sortie}
			rm filtered
			rm pres2

		elif [[ $modeP = 3 ]]
			then
			cut -d';' -f1,2,7 tmp1 > pres3
			
			./tri_donnees pres3 $tri ${fichier_sortie}
			gnuplot < fctdiag/p3_diag.gnu --persist
			cp filtered2 ${fichier_sortie}
			rm filtered2
			rm pres3

		elif [[ $modeP != "1" ]] || [[ $modeP != "2" ]] || [[ $modeP != "3" ]]
			then
			echo "Le mode sélectionné pour la pression n'existe pas. Veuillez choisir le mode 1, 2 ou 3 !"
		fi
}

function vent () {
#Fonction qui permet de découper le fichier de données pour récupérer les colonnes associées au vent . Ensuite on exécute le c et on affiche les graphiques selon le mode choisi.

	cut -d';' -f1,4,5,10 tmp1 > vent 
	
	./tri_donnees vent $tri ${fichier_sortie}
	gnuplot <  fctdiag/vent_diag.gnu --persist
	cp filtered ${fichier_sortie}
	rm filtered
	rm vent
	
}

function humidite () {
#Fonction qui permet de découper le fichier de données pour récupérer les colonnes nécessaire au tri de l'humidité. Ensuite on exécute le c et on affiche les graphiques selon le mode choisi.

	cut -d';' -f1,6,10 tmp1 > humidite
	
	./tri_donnees humidite $tri ${fichier_sortie}
	gnuplot < fctdiag/hum_diag.gnu --persist
	cp filtered ${fichier_sortie}
	rm filtered
	rm humidite
}

function altitude () {
#Fonction qui permet de découper le fichier de données pour récupérer les colonnes nécessaire au tri de l'altitude. Ensuite on exécute le c et on affiche les graphiques selon le mode choisi.

	cut -d';' -f10,14 tmp1 > altitude 
	
	./tri_donnees altitude $tri  ${fichier_sortie}
	gnuplot < fctdiag/alt_diag.gnu --persist
	cp filtered ${fichier_sortie}
	rm filtered
	rm altitude
}

function DATES () {
#Fonction qui permet de récupérer l'intervalle de date choisi par l'utilisateur puis exécute le c pour filtrer le fichier météo avec les dates choisies.

	DATE_min=`echo $DATES_intervalle | awk -F"_" '{print $1}'`
	DATE_max=`echo $DATES_intervalle | awk -F"_" '{print $2}' | awk -F" " '{print $1}'`
	echo "Vous avez choisi l'intervalle de dates suivant : $DATE_min $DATE_max"
	
	./tri_donnees $DATE_min $DATE_max z1
}

function coords () {
#Fonction qui permet de d'exécuter le c pour filtrer le fichier météo selon le territoire choisi par l'utilisateur.

	./tri_donnees $territoire z2
}



if [[ $# -lt 4 ]] #Si moins de 4 arguments, on ne peut pas exécuter le c. 
		  #Il faut au moins ./script.sh + [-f] + [-o] + [-paramètre obligatoire (t ou p ou w ou h ou m)].
then
	menu_help
fi

fichier=`echo $@ | awk -F "-f" '{print $2}'|awk -F" " '{print $1}'` #on récupère l'argument après -f (le fichier des données)

if [[ -z $fichier ]] #si pas d'argument après -f alors menu help
then
menu_help
fi

if [[ ! -f $fichier ]]
then 
	echo "L'argument n'est pas un fichier."
	echo "Faites --help si vous avez besoin d'aide."
	exit 2
fi

fichier_sortie=`echo $@ | awk -F "-o" '{print $2}'|awk -F" " '{print $1}'` #on récupère l'argument après -o (le fichier de sortie)

if [[ -z $fichier_sortie ]] #si pas d'argument après -o alors menu help
then
menu_help
fi

echo "Bienvenue sur la météo"

chmod +x tri_donnees

while getopts ":t:p:f:-:d:o:wmhFGSAOQ" opt
do
if [[ $opt = "-" ]]
then
 opt=$OPTARG
fi
case $opt in

	help)	menu_help
	;;
	
	tab)	option_tab=1
			
	;;
	
	abr)	option_abr=1
		tri=$OPTARG
	;;

	avl)	option_avl=1
		tri=$OPTARG
	;;

	f) 	fichier=$OPTARG
	;;	
	t) 	modeT=$OPTARG
		option_temp=1
	;;
	p) 	modeP=$OPTARG
		option_pres=1
	;;
	w) 	option_vent=1
	;;
	m)	option_humidite=1
	;;
	h) 	option_altitude=1
	;;
	d) 	DATES_intervalle=$OPTARG
		option_DATES=1
	;;
	o)	fichier_sortie=$OPTARG
		
	;;
	F)	option_france=1
		
	;;
	G)	option_guyane=1
			
	;;
	S)	option_saintpierre=1
		
	;;
	A)	option_antilles=1
		
	;;
	O)	option_ocean=1
		
	;;
	Q)	option_antarctique=1

	;;
	*) 	menu_help
		exit 3
esac
done

if [[ ${option_tab} = "1" ]] # si utilisateur saisi --tab
then
	echo "Méthode de tri par tab en cours de développement...Veuillez choisir un autre mode de tri"	
	exit
fi


if [[ -z $tri ]] #si pas de mode de tri choisit par l'utilisateur alors "avl" par défaut
then
 tri=avl
fi

rest_tri=0

let "rest_tri=rest_tri+option_tab+option_avl+option_abr" # on calcule si plusieurs modes de tri saisis

if [[ "$((rest_tri))" -gt 1 ]]	#On ne peut choisir qu'un seul mode de tri 
then
	echo "Vous avez choisi plus d'une méthode tri."
	menu_help
fi

restriction=0

let "restriction=restriction+option_france+option_guyane+option_antilles+option_saintpierre+option_ocean+option_antarctique" # On calcule si plusieurs territoires saisis

if  [[ "$((restriction))" -gt 1 ]]  #On ne peut choisir qu'un seul territoire 
then 
	echo "Vous ne pouvez choisir qu'un seul territoire à la fois"
	menu_help
fi

parametres=0

let "parametres=parametres+option_temp+option_pres+option_vent+option_humidite+option_altitude" #On calcule si au moins un paramètre obligatoire a été saisi.

if [[ "$((parametres))" -lt 1 ]] #On est obligé de choisir un paramètre.
then
	echo "Vous devez choisir au moins un type de données à trier."
	menu_help
fi
#on enlève l'entête du fichier
tail -n+2 ${fichier} > tmp
#formatage de la date
sed 's/\(.*\)T[0-9]*:[0-9]*:[0-9]*+[0-9]*:[0-9]*;/\1;/' tmp > tmp1
#on remplie les cases vides avec des 0
sed 's/;;/;0;/g' tmp1 > test.csv
sed 's/;;/;0;/g' test.csv > tmp1


if [[ ${option_DATES} = "1" ]] #Si l'utilisateur à saisi une date on exécute la fonction "DATES"
then
	DATES
fi

if [[ ${option_france} = "1" ]] #Si l'utilisateur à saisi le territoire France on exécute la fonction "coords"
then
	territoire=france5
	coords
fi

if [[ ${option_guyane} = "1" ]] #Si l'utilisateur à saisi le territoire Guyane on exécute la fonction "coords"
then
	territoire=guyane6
	coords
fi

if [[ ${option_saintpierre} = "1" ]] #Si l'utilisateur à saisi le territoire Saint Pierre et Miquelon on exécute la fonction "coords"
then
	territoire=saintpierre7
	coords
fi

if [[ ${option_antilles} = "1" ]] #Si l'utilisateur à saisi le territoire Antilles on exécute la fonction "coords"
then
	territoire=antilles8
	coords
fi

if [[ ${option_ocean} = "1" ]] #Si l'utilisateur à saisi le territoire Océan on exécute la fonction "coords"
then
	territoire=ocean9
	coords
fi

if [[ ${option_antarctique} = "1" ]] #Si l'utilisateur à saisi le territoire Antarctique on exécute la fonction "coords"
then
	territoire=antarctique0
	coords
fi

rm test.csv
rm tmp

if [[ ${option_temp} = "1" ]] #Si l'utilisateur à saisi le paramètre "température" on exécute la fonction "temp"
then
	temp
fi

if [[ ${option_pres} = "1" ]] #Si l'utilisateur à saisi le paramètre "pression" on exécute la fonction "pres"
then
	pres
fi

if [[ ${option_vent} = "1" ]] #Si l'utilisateur à saisi le paramètre "vent" on exécute la fonction "vent"
then
	vent
fi

if [[ ${option_humidite} = "1" ]] #Si l'utilisateur à saisi le paramètre "humidité" on exécute la fonction "humidité"
then
	humidite
fi

if [[ ${option_altitude} = "1" ]] #Si l'utilisateur à saisi le paramètre "altitude" on exécute la fonction "altitude"
then
	altitude
fi

rm tmp1

