#include "header.h"

int tri_p2_avl(char* input_fich, char* output_fich, int decroissant)
{

	char* type = "p2";
	avl* a = construireavl(input_fich, 0, type);
	
	if(!decroissant)
		parcourscroissantavl_appel(a, output_fich);
	else
		parcoursdecroissantavl_appel(a, output_fich);
}




int infstrictavl_p2(avl* a, avl* b, int idx)	// faire la mm en tab et en abr	AAAAAAAAAAAAAAAAAAAAAAAAAOUOUGOUOuUUOOUOUiUoUHUPHhupHUpjlhvTIYfoYIvvtyFoluTCtYlhJhdrixipmvRXRTRIFULO
{	//return 1 si a < b (en comparant par ordre chonologique) return 0 sinon

	// idx represente l'indice du champ que l'on trie
	//return 1 si a < b (en comparant un elem) return 0 sinon
	verifpavl(a);
	verifpavl(b);		
	

	//on verifie si on tri des dates ou autres chose (le format de la date dans les donnees ayant un "T")
	char* verif1_a = strstr(a->ligne[idx], "T");
	char* verif1_b = strstr(b->ligne[idx], "T");
	

	if(verif1_a && verif1_b) //si on a 2 dates, on fait la comparaison de date
	{
		if(compare_dates(a->ligne[idx], b->ligne[idx]) == -1)
		{
			return 1;
		}
	}
	else if(a->ligne[idx] != " ") // on place les lignes qui ont le champ que l'on trie vide en dernier dans l'ordre croissant (on considere " " comme toujours superieur)
	{
		if(b->ligne[idx] != " " && atoi(a->ligne[idx]) < atoi(b->ligne[idx]))
		{
			return 1;
		}
	}

	return 0;
}




avl* egalavl_p2(avl* a, avl* b, int i)
{	// cumule les temperatures et augmente nbr_moyenne 
	
	verifpavl(a);
	verifpavl(b);
	
	int verif_a = (a->ligne[i] != NULL && strcmp(a->ligne[i], " ")); // si il y a une valeur en a
	int verif_b = (b->ligne[i] != NULL && strcmp(b->ligne[i], " ")); // si il y a une valeur dans b
	if(verif_a && verif_b)
	{
		//printf("\n  a->ligne[i] = %s   \n", a->ligne[i]);
		int abs_a = atoi(a->ligne[i]);
		if(abs_a<0)
			abs_a= 0-abs_a;
		int abs_b = atoi(b->ligne[i]);
		if(abs_b<0)
			abs_b= 0-abs_b;
		int abs_som = abs_a + abs_b;
		if(abs_som<0)
			abs_som = 0-abs_som;
		sprintf(a->ligne[i], "%d", abs_som);
		(a->nbr_moyenne[0])++; // et on incremente le nombre de la division a faire une fois l'arbre fini
	}

	return a;
}

avl* finiravl_p2(avl* a, int i)
{	// cette fonction fait le calcul des moyennes et actualise les lignes de chaque noeud

	if(a)
	{
		verifpavl(a);

		if(a->nbr_moyenne[0] > 1)
		{	
			// on fait la moyenne des temperature pour le noeud
			sprintf(a->ligne[i], "%d", atoi(a->ligne[i]) / a->nbr_moyenne[0]);
			a->nbr_moyenne[0] = 1;
		}
		// on rentre les valeurs de la ligne dans le string
		strcpy(a->cligne, actualiseravl_cligne(a));

		finiravl_p2(a->fd, i);
		finiravl_p2(a->fg, i);
	}
	return a;
}
