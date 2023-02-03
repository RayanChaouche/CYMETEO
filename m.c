#include "header.h"

int tri_m1_avl(char* input_fich, char* output_fich)
{	//cette fonction fait un fichier intermediaire duquel on pourras reconstruire un avl pour faire le fichier voulu
	
	char* type = "m1";
	avl* a1 = construireavl(input_fich, 0, type); // on construit un avl trie par rapport aux id, pour faire le maximum des humidites par station

	parcourscroissantavl_appel(a1, output_fich);

	//////////// IL FAUT FAIRE 2 PARTIES PSK LE FICHIER FRRR.TXT NE S'UPDATE PAS AVANT DE LE REPRENDRE EN ENTREE, IL FAUT APPELER LE C 2 FOIS, ET FAIRE TRI_M1 ET TRI_M2
}

int tri_m2_avl(char* input_fich, char* output_fich)
{	// cette fonction doit etre appelee dans une autre instance de tri_m1, sinon le fichier intermediaire aura des probleme
	// cette fonction tri dans un avl le fichier d'entree par rapport a l'humidite et cree un fichier trie
	
	// IL FAUT APPELER LE C 2 FOIS, UNE FOIS POUR M1 UNE FOIS POUR M2	/////////////////////////////////////////////////////////////
	
	char* type = "m2";
	char* fichier_int = "frrrrrrr.txt";
	avl* a2 = construireavl(fichier_int, 1, type); // puis on reconstruit un avl qui trie le fichier precedent par rapport a l'humidite
	
	// on doit faire decroissant de base
	parcoursdecroissantavl_appel(a2, output_fich);
}

int infstrictavl_m2(avl* a, avl* b, int idx)
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
		else if(atoi(a->ligne[idx]) == atoi(b->ligne[idx]) && strcmp(a->ligne[idx-1],b->ligne[idx-1])) // si ce n'est pas la mm station mais la mm humidite, on compare par rapport a l'id
		{
			if(atoi(a->ligne[idx-1]) < atoi(b->ligne[idx-1]))
			{
				return 1;
			}
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

int infstrictavl_m1(avl* a, avl* b, int idx)
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

avl* egalavl_m(avl* a, avl* b, int i)
{	// prend l'humidite maximum parmi les 2 noeuds
	

	verifpavl(a);
	verifpavl(b);
	
	int verif1_a = strcmp(a->ligne[i+1], " ");
	int verif1_b = strcmp(b->ligne[i+1], " ");

	if(verif1_a && verif1_b)	// si il y a des valeurs dans a et b on choisit le minimun
		sprintf(a->ligne[i+1], "%d", max2(atoi(a->ligne[i+1]), atoi(b->ligne[i+1])));
	else if(!verif1_a && verif1_b) // si il y a pas de valeur en a mais il y en a en b on assigne la valeur de b a a
		sprintf(a->ligne[i+1], "%d", atoi(b->ligne[i+1]));

	return a;
}

avl* finiravl_m(avl* a, int i)
{	// cette fonction actualise les lignes de chaque noeud
	if(a)
	{
		verifpavl(a);

		// on rentre les valeurs de la ligne dans le string du noeud
		strcpy(a->cligne, actualiseravl_cligne(a));

		finiravl_h(a->fd, i);
		finiravl_h(a->fg, i);
	}
	return a;
}








