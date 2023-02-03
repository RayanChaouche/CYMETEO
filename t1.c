#include "header.h"

int tri_t1_avl(char* input_fich, char* output_fich, int decroissant)
{

	char* type = "t1";
	avl* a = construireavl(input_fich, 0, type);
	
	if(!decroissant)
		parcourscroissantavl_appel(a, output_fich);
	else
		parcoursdecroissantavl_appel(a, output_fich);
}

int infstrictavl_t1(avl* a, avl* b, int idx)	// faire la mm en tab et en abr	AAAAAAAAAAAAAAAAAAAAAAAAAOUOUGOUOuUUOOUOUiUoUHUPHhupHUpjlhvTIYfoYIvvtyFoluTCtYlhJhdrixipmvRXRTRIFULO
{	//return 1 si a < b (en comparant par ordre chonologique) return 0 sinon

	

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

avl* egalavl_t1(avl* a, avl* b, int i)
{	// cumule les temperatures, augmente nbr_moyenne et met a jour les maximums et minimums 
	
	verifpavl(a);
	verifpavl(b);
	

	//printf("\n\n\n avant  a->ligne[i]=%s   \n\n\n\n", a->ligne[i]);
	// on additionne les temperatures vu que c'est la meme station
	sprintf(a->ligne[i], "%d", atoi(a->ligne[i]) + atoi(b->ligne[i]));
	a->nbr_moyenne[0]++; // et on incremente le nombre de la division a faire une fois l'arbre fini
	
	//printf("\n\n\n apres a->ligne[i] = %s   \n\n\n\n", a->ligne[i]);
	
	int verif1_a = (a->ligne[i+1] != NULL || strcmp(a->ligne[i+1], " ")); // si il y a une valeur minimum en a
	int verif1_b = strcmp(b->ligne[i], " "); // si il y a une valeur dans b

	if(verif1_a && verif1_b)	// si il y a des valeurs dans a et b on choisit le minimun
		sprintf(a->ligne[i+1], "%d", min2(atoi(a->ligne[i+1]), atoi(b->ligne[i])));
	else if(!verif1_a && verif1_b) // si il y a pas de valeur en a mais il y en a en b on assigne la valeur de b a a
		sprintf(b->ligne[i+1], "%d", atoi(b->ligne[i]));

	
	int verif2_a = (a->ligne[i+2] != NULL || strcmp(a->ligne[i+1], " ")); // si il y a une valeur max en a
	int verif2_b = strcmp(b->ligne[i], " "); // si il y a une valeur dans b

	if(verif2_a && verif2_b)	// si il y a des valeurs dans a et b on choisit le maximum
		sprintf(a->ligne[i+2], "%d", max2(atoi(a->ligne[i+2]), atoi(b->ligne[i])));
	else if(!verif2_a && verif2_b) // si il y a pas de valeur en a mais il y en a en b on assigne la valeur de b a a
		sprintf(b->ligne[i+2], "%d", atoi(b->ligne[i]));

	return a;
}

avl* finiravl_t1(avl* a, int i)
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

		finiravl_t1(a->fd, i);
		finiravl_t1(a->fg, i);
	}
	return a;
}






