#!/bin/bash
# $@ = tt les arg     $# = nbr arg


#france		41.32 <latitude< 5.10892	  -5.16 < longitude< 9.56
latitude_min_fr=41.32
latitude_max_fr=5.10
longitude_min_fr=-5.16
longitude_max_fr=9.56

#antilles	14.345 <latitude< 18.77		  -63.67<longitude< -60.661
latitude_min_a=14.34
latitude_max_a=18.77
longitude_min_a=-63.67
longitude_max_a=-60.66

#guyane francaise 5.00 <latitude< 4.73		  -52.01<longitude< -52.43
latitude_min_g=5
latitude_max_g=4.73
longitude_min_g=-52.01
longitude_max_g=-52.43

#saint pierre/miquelon 	46.7 <latitude< 47.1	-56.10<longitude< -56.56
latitude_min_p=46.7
latitude_max_p=47.1
longitude_min_p=-56.10
longitude_max_p=-56.56

#ocean indien	-33.89 <latitude< 37.278	24.456<longitude<117.339
latitude_min_o=-33.89
latitude_max_o=37.27
longitude_min_o=24.45
longitude_max_o=117.33

#antarctique	 -90 <latitude< -60			0<longitude<180
latitude_min_o=-90
latitude_max_o=-60
longitude_min_o=0
longitude_max_o=180


declare -i nbr_modes=0

for arg in $@ #on compte le nombre de graphique a faire
do
case $arg in
	"-t1")
		nbr_modes=nbr_modes+1
	;;
	"-t2")
		nbr_modes=nbr_modes+1
	;;
	"-t3")
		nbr_modes=nbr_modes+1
	;;

	"-p1")
		nbr_modes=nbr_modes+1
	;;

	"-p2")
		nbr_modes=nbr_modes+1
	;;

	"-p3")
		nbr_modes=nbr_modes+1
	;;

	"-w")
		nbr_modes=nbr_modes+1
	;;

	"-h")
		nbr_modes=nbr_modes+1
	;;

	"-m")
		nbr_modes=nbr_modes+1
	;;
	
	"-help")
		echo "Pour faire fonctionner le script, vous devez obligatoirement avoir un -f suivis du nom du fichier contenant les données triés ( ex: -f data.csv ) et un -o suivis du nom du fichier de sortie. Vous devez aussi obligatoirement entrer au moins une option selon votre/vos choix parmis -h ( pour avoir une carte interpolé et coloré de l'altitude), -m ( pour avoir la même chose mais de l'humidité), -w (pour avoir un diagramme de type vecteur) et -p ou -t suivis de 1,2 ou 3 (ex:-p3)( t pour température et p pour pression, 1 pour avoir un diagramme de type barres d'erreur, 2 pour un diagramme de type ligne simple et 3 pour un diagramme de type multi-ligne). En option vous pouvez préciser une zone en ajoutant - suivis de A pour Antilles, G pour Guyane, F pour France, S pour St-Pierre et Miquellon, O pour Océan Indien et Q pour l'océan Antartique. L'ordre de tout ces options n'est pas important mais ne doivent pas être collée (ex: -A-p1 n'est pas bon mais -A -p1 l'est). Si rien ou --avl est ajouté, les données seront triés en AVL, si vous voulez trier les données en ABR ou en tableau, ajoutez --abr ou --tab. Pour trier les donner de façon décroissante, ajoutez -r."
		exit
	;;
	esac
done


#recupere les dates demandee
date_bool=0
arr=($@)
for ((i=0; i<$#; i++)); do
	if [[ ${arr[i]} == "-d" ]]
	then
		if [ $date_bool == 1 ]
		then
			echo "erreur plusieurs arguments -d"
		exit
		fi
		
		echo ${arr[i]}
		date_bool=1

		date_min=${arr[i+1]}
		date_max=${arr[i+2]}
		if [[ $date_min > $date_max ]]
		then
			echo $date_min		
			echo $date_max
			echo "erreur arguments de dates invalides"
		exit
		fi
	fi
done

#verifie quel lieu est demandee
lieu=0
decroissant=0
mode_trie="avl" #de base on trie en avl
 
fichier=0
mode=0
for argument in $@ # on verifie -r et le type de tri
do
case $argument in
    "-r")
        decroissant=1
    ;;
    "--abr")
        mode_trie="abr"
    ;;
    "--tab")
        mode_trie="tab"
    ;;
    "--avl")
        mode_trie="avl"
    ;;
    esac
done

min_lattitude=0
max_lattitude=0
min_longitude=0
max_longitude=0
for arg in $@ # on verifie si un lieu qui a été précisé
do
case $arg in
    "-F")
        if [ $lieu == 0 ];
        then
            lieu="France"
            min_lattitude=40
            max_lattitude=52
            min_longitude=-10
            max_longitude=12
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    "-A")
        if [ $lieu == 0 ];
        then
            lieu="Antille"
            min_lattitude=12
            max_lattitude=19
            min_longitude=-65
            max_longitude=-58
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    "-G")
        if [ $lieu == 0 ];
        then
            lieu="Guyane"
            min_lattitude=-1
            max_lattitude=10
            min_longitude=-58
            max_longitude=-48
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    "-S")
        if [ $lieu == 0 ];
        then
            lieu="Saint_pierre_et_miquelon"
            min_lattitude=44
            max_lattitude=53
            min_longitude=-64
            max_longitude=-49
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    "-O")
        if [ $lieu == 0 ];
        then
            lieu="Ocean_indien"
            min_lattitude=-60
            max_lattitude=3
            min_longitude=26
            max_longitude=100
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    "-Q")
        if [ $lieu == 0 ];
        then
            lieu="Antartique"
            min_lattitude=40
            max_lattitude=52
            min_longitude=-10
            max_longitude=12
        else
            echo "erreur trop d'argument de lieu"
            exit
        fi
    ;;
    esac
done

for ((j=0; j<nbr_modes; j++)); do # on fait une boucle pour faire chaque graphique
 
 
for arg in $@ #for qui lit tous les arguments donne par l'utilisateur
do
 
    case $a in # switch
 
	"-t1") # on doit mtn vérifié si on prends en compte le parametre date (-d min max)
	        #on regarde si on doit filtré par date ou par un lieu precise par l'utilisateur
                mode="-t1"
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode t1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $11 ";" $11 ";" $11 ";" $2}' > tmp.txt
 
                    #date_max represente la date maximum de l'intervalle a filtre fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtre le fichier .txt creer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$3 >= date_min && $3 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Données Filtrées, On passe au C"
 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
                        latitude_max_fr=52
                        latitude_min_fr=41
                        longitude_min_fr=-5
                        longitude_max_fr=10
                        #on rajoute les coordonnes en dernier au fichier .txt
			command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $11 ";" $11 ";" $11 ";" $10}' | awk '{gsub(/,/,";",$NF);print}' > tmp.txt`
                        echo $command
                        #filtre par lattitude
                        compare_lattitude=`cat tmp.txt | tail -n+2 | awk -F ';' '{if($3<='"52"' && $3>='"41"') print $0;}' tmp.txt > tmp.txt`
                        echo $compare_lattitude
                        #filtre par longitude  
                        compare_longitude=`cat tmp.txt | tail -n+2 | awk -F ';' '{if($4<='"10"' && $4>'"-5"') print $0;}' tmp.txt > tmp.txt`  
                        echo $compare_longitude
                        echo "Donnée Filtrées par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,11 > tmp.txt`
                    echo $command
                   echo "Donnée Filtrées, On passe au C"

                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $11 ";" $11 ";" $11 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    cat tmp.txt | tail -n+2 | awk -F ';' '{if($3<='"52"' && $3>='"41"') print $0;}' tmp.txt > tmp.txt
                    cat tmp.txt | tail -n+2 | awk -F ';' '{if($4<='"10"' && $4>'"-5"') print $0;}' tmp.txt > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Données Filtrées, On passe au C"
                fi
        ;;
        "-t2")
            mode="-t2"
          #  command=`cat meteo.csv | tail -n+2 |cut -d ';' -f 2,11 > tmp.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $11}' > tmp.txt
 
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$1 >= date_min && $1 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"

 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $11 ";" $10}' > tmp.txt
 
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 2,11 > tmp.txt`
                    echo $command
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $11 ";" $10}' > tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$1 >= date_min && $1 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
                fi
 
        ;;
        "-t3")
            mode="-t3"
            #command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $11}' > tempmode3_no_triage.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $11}' > tmp.txt
 
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$2 >= date_min && $2 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $11 ";" $10}' > tmp.txt
 
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tempmode3_filtre.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,2,11 > tempmode3_filtre.txt`
                    echo $command
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $11 ";" $10}' > tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$2 >= date_min && $2 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
                fi
        ;;
        "-p1")
            mode="-p1"
            #command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,7 > pressmode1_no_filtrage.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $7 ";" $7 ";" $7}' > tmp.txt
 
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$3 >= date_min && $3 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"

                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $7 ";" $7 ";" $7 ";" $10}' > tmp.txt
 
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $7 ";" $7 ";" $7 ";" $10}' > tmp.txt`
                    echo $command
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $7 ";" $7 ";" $7 ";" $10 ";" $2}' > tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
                fi
        ;;
        "-p3")
            mode="-p3"
            #command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,2,7 > pressmode3_no_triage.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $7}' > tmp.txt
 
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$2 >= date_min && $2 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"

                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $7 ";" $10}' > tmp.txt
 
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C" 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,2,7 > tmp.txt`
                    echo $command
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $7 ";" $10}' > tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$2 >= date_min && $2 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
                fi
        ;;
        "-p2")
            mode="-p2"
          #  command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 2,7 > pressmode2_no_triage.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $7}' > press2_no_filtrage.txt
 
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$1 >= date_min && $1 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"
 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $7 ";" $10}' > tmp.txt
 
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 2,7 > tmp.txt`
                    echo $command
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $7 ";" $10}' > tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$1 >= date_min && $1 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
                fi
        ;;
        "-m") #colonne 10 c'est les coordonnées
            mode="-m"
            #command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10}' > tmp.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"
 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10}' > tmp.txt
                        sed -i -e "s/,/;/g" tmp.txt
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
 
                fi
        ;;
        "-h") # on doit mtn vérifié si on prends en compte le parametre date (-d min max)
            mode="-h"
            #command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10}' > altitude_pas_trie.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"
 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10}' > tmp.txt
                        sed -i -e "s/,/;/g" tmp.txt
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($3>min_lattitude && $3<max_lattitude && $4>min_longitude && $4<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$5 >= date_min && $5 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
 
                fi
 
 
 
 
        ;;
        "-w")
            mode="-w"
            #`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $4 ";"$5 ";" $10}' > vent_no_triage.txt`
                if [ $date_bool == 1 ] && [ $lieu == 0 ]; then
                    # commande qui recupere tous les donnes pour le mode température 1 + la date
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $4 ";" $5 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$6 >= date_min && $6 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtré par date, On passe au C"
 
                elif [ $date_bool == 0 ] && [ $lieu != 0 ]; then
 
                        #on rajoute les coordonnes en dernier au fichier .txt
                        cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $4 ";" $5 ";" $10}' > tmp.txt
                        sed -i -e "s/,/;/g" tmp.txt
                        cat tmp.txt  | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tmp.txt
                        echo "Donnée Filtré par lieu, On passe au C"
 
 
                    #filtre par longitude et latitude
                elif [ $date_bool == 0 ] && [ $lieu == 0 ]; then
                    # pas de filtrage
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $4 ";" $5 ";" $10}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    echo "Pas de filtrage, On passe au C"
 
                elif [ $date_bool == 1 ] && [ $lieu != 0 ]; then
                    cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $4 ";" $5 ";" $10 ";" $2}' > tmp.txt
                    sed -i -e "s/,/;/g" tmp.txt
                    cat tmp.txt | tr ',' ';' | awk -v min_lattitude="$min_lattitude" -v max_lattitude="$max_lattitude" -v min_longitude="$min_longitude" -v max_longitude="$max_longitude" -F ';' '{if($4>min_lattitude && $4<max_lattitude && $5>min_longitude && $5<max_longitude) {print $0}}' > tmp.txt
                    #date_max represente la date maximum de l'intervalle a filtré fourni par l'utilisateur et on rajoute 1 jour a la date que nous a fourni l'utilisateur car pour l'inclure dans l'intevalle 
                    date_max=$(date -d "$date_max + 1 day" +"%Y-%m-%d")
                    #la commande awk va filtré le fichier .txt créer par la commande cat (ligne 121). elle filtre par l'intervalle de date et garde que les lignes compris dans l'intervalle de dates
                    awk -v date_min="$date_min" -v date_max="$date_max" -F ";" '$6 >= date_min && $6 <= date_max' tmp.txt > tmp.txt
                    # on supprime l'ancien fichier qui n'était pas filtré.
                    echo "Donnée Filtrée par date et par lieu, On passe au C ! " 
 
                fi
        ;;
 
    esac
done
 
 
make
if [ -x "exec" ]; then
    	case $mode in
		"-m")
        		if [ $mode_trie != "abr" && $mode_trie != "tab"];
        		then
        	    		./exec -ftmp.txt -o sortie.txt --m1 "$mode"
		    		./exec -ftmp.txt -o sortie.txt --m2 "$mode"
        		else
        	    		./exec -ftmp.txt -osortie.txt --"$mode_trie" "$mode"
       			fi
    		;;
    		*)
		    	if [ $decroissant == 1 ]; then
				./exec -ftmp.txt -osortie.txt --"$mode_trie" "$mode"
			else        
				./exec -ftmp.txt -osortie.txt --"$mode_trie" -r "$mode"
   	 		fi
    		;;
	esac
else
	echo "exec n'est pas un fichier exécutable ou n'existe pas"
	exit 1
fi

echo "On passe maintenant à GNUPLOT !"
echo "On va créer un fichier graphique.png, si vous avez choississez plusieurs modes alors il yaura graphique1.png et graphique2.png etc..."
 
if [ $mode == "-h" ]; then
    gnuplot gnuplot_h.gnu
elif [ $mode == "-m" ]; then
    gnuplot gnuplot_m.gnu
elif [ $mode == "-w" ]; then
    gnuplot gnuplot_w.gnu
elif [ $mode == "-t1" ]; then
    gnuplot gnuplot_t1.gnu
elif [ $mode == "-t2" ]; then
    gnuplot gnuplot_t2.gnu
elif [ $mode == "-t3" ]; then
    gnuplot gnuplot_t3.gnu
elif [ $mode == "-p1" ]; then
    gnuplot gnuplot_p1.gnu
elif [ $mode == "-p2" ]; then
    gnuplot gnuplot_p2.gnu
elif [ $mode == "-p3" ]; then
    gnuplot gnuplot_p3.gnu
fi

mv graphique.png graphique$j.png
 
done


##POUR T1
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $11 ";" $11 ";" $11}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
#echo $command

## POUR T2
#command=`cat meteo.csv | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 2,11 > tmp.txt`
#echo $command

## POUR T3
#command=`cat meteo.csv | sed 's/;;/; ;/g' | tail -n+2 |cut -d ';' -f 1,2,11 > tmp.txt`
#echo $command

##POUR P1
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $7 ";" $7 ";" $7}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
#echo $command

## POUR P2
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $2 ";" $7}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
#echo $command

## POUR P3
##command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $2 ";" $7}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
##echo $command

##POUR W
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk '{gsub(/,/,";",$NF);print}' | cut -d ';' -f 1,4,5,10 > tmp.txt`
#echo $command

##POUR H
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $14 ";" $10}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
#echo $command

##POUR M
#command=`cat meteo.csv | sed 's/;;;/; ; ;/g' | sed 's/;;/; ;/g' | tail -n+2 | awk -F ';' '{print $1 ";" $6 ";" $10}' | awk '{gsub(/,/,";",$NF);print}'  > tmp.txt`
#echo $command
