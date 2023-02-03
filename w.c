#include "header.h"

int tri_w_avl(char* input_fich, char* output_fich, int decroissant)
{

	char* type = "w";
	avl* a = construireavl(input_fich, 0, type);
	
	if(!decroissant)
		parcourscroissantavl_appel(a, output_fich);
	else
		parcoursdecroissantavl_appel(a, output_fich);
}




int infstrictavl_w(avl* a, avl* b, int idx)	// faire la mm en tab et en abr	AAAAAAAAAAAAAAAAAAAAAAAAAOUOUGOUOuUUOOUOUiUoUHUPHhupHUpjlhvTIYfoYIvvtyFoluTCtYlhJhdrixipmvRXRTRIFULO
{	//return 1 si a < b (en comparant les identifiants) return 0 sinon

	// idx represente l'indice du champ que l'on trie
	//return 1 si a < b (en comparant un elem) return 0 sinon
	verifpavl(a);
	verifpavl(b);		
	

	//on verifie si on trie des lignes sans valeurs a trier
	int verif_a = strcmp(a->ligne[idx], " "); // strcmp retourne un nombre positif si le string n'est pas le meme et 0 sinon
	int verif_b = strcmp(b->ligne[idx], " ");

	if(verif_a && verif_b) // on compare les valeurs si il y en a
	{	
		
		if(atoi(a->ligne[idx]) < atoi(b->ligne[idx]))
		{
			return 1;
		}

	}
	else if(verif_a) // on place les lignes qui ont le champ que l'on trie vide en dernier dans l'ordre croissant (on considere " " comme toujours superieur)
	{
		if(!verif_b)
		{
			return 1;
		}
	}

	return 0;
}


avl* egalavl_w(avl* a, avl* b, int i)
{	// cumule les vitesse et orientation puis augmente nbr_moyenne 

	verifpavl(a);
	verifpavl(b);
	
	int condition1_a = strcmp(a->ligne[i], " "); // il y a une valeur pour a
	int condition1_b = strcmp(b->ligne[i], " "); // il y a une valeur pour b
	
	// on additionne les vitesses vu que c'est la meme station
	if(condition1_a && condition1_b)
	{ 
		sprintf(a->ligne[i], "%d", atoi(a->ligne[i]) + atoi(b->ligne[i]));
		a->nbr_moyenne[0]++; // et on incremente le nombre de la division a faire si il y a eu un ajout 
	}
	else if(!condition1_a && condition1_b) // si il n'y a pas de valeur en a on ne prend que b (et inversement mais pas besoin de le faire)
	{
		a->ligne[i] = strcpy(a->ligne[i], b->ligne[i]);
	}


	int condition2_a = strcmp(a->ligne[i+1], " "); // il y a une valeur pour a
	int condition2_b = strcmp(b->ligne[i+1], " "); // il y a une valeur pour b
	int condition2 = (condition2_a && condition2_b); // il y a une valeur pour a et b

	// on additionne les orientations vu que c'est la meme station
	if(condition2)
	{ 
		sprintf(a->ligne[i+1], "%d", atoi(a->ligne[i+1]) + atoi(b->ligne[i+1]));
		a->nbr_moyenne[1]++; // et on incremente le nombre de la division a faire si il y a eu un ajout
	}
	else if(!condition2_a) // si il n'y a pas de valeur en a on ne prend que b (et inversement mais pas besoin de le faire)
	{
		sprintf(a->ligne[i+1], "%d", atoi(b->ligne[i]));
	}

	return a;
}

avl* finiravl_w(avl* a, int i)
{	// cette fonction fait le calcul des moyennes et actualise les lignes de chaque noeud
	if(a)
	{
		verifpavl(a);
		if(a->nbr_moyenne[0] > 1)
		{
			// on fait la moyenne des vitesses et orientations pour le noeud
			sprintf(a->ligne[i], "%d", atoi(a->ligne[i]) / a->nbr_moyenne[0]);
			a->nbr_moyenne[0] = 1;
		}
		if(a->nbr_moyenne[1] > 1)
		{
			// on fait la moyenne des vitesses et orientations pour le noeud
			
			sprintf(a->ligne[i+1], "%d", atoi(a->ligne[i+1]) / a->nbr_moyenne[1]);
			a->nbr_moyenne[1] = 1;
		}


		// on rentre les valeurs de la ligne dans le string
		strcpy(a->cligne, actualiseravl_cligne(a));

		finiravl_w(a->fd, i);
		finiravl_w(a->fg, i);
	}
	return a;
}
