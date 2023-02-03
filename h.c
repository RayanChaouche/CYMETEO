#include "header.h"

int tri_h_avl(char* input_fich, char* output_fich)
{
	char* type = "h";
	avl* a = construireavl(input_fich, 1, type);
	
	// on doit faire decroissant de base	
	parcoursdecroissantavl_appel(a, output_fich);
}




int infstrictavl_h(avl* a, avl* b, int idx)
{	//return 1 si a < b (en comparant par ordre chonologique) return 0 sinon


	// idx represente l'indice du champ que l'on trie
	//return 1 si a < b (en comparant un elem) return 0 sinon
	verifpavl(a);
	verifpavl(b);		
	
	//on verifie si on trie des lignes sans valeurs a trier
	int verif_a = strcmp(a->ligne[idx], " "); // strcmp retourne un nombre positif si le string n'est pas le meme et 0 sinon
	int verif_b = strcmp(b->ligne[idx], " ");

	if(verif_a && verif_b) // on compare les valeurs (si a et b en ont)
	{	
		if(atoi(a->ligne[idx]) < atoi(b->ligne[idx]))
		{
			return 1;
		}

		if(atoi(a->ligne[idx]) == atoi(b->ligne[idx]) && strcmp(a->ligne[idx-1],b->ligne[idx-1])) // si ce n'est pas la mm station mais la mm altitude, on compare par rapport a l'id
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




avl* egalavl_h(avl* a, avl* b, int i)
{	// si c'est la meme station il n'y a rien a faire
	
	verifpavl(a);
	verifpavl(b);

	return a;
}

avl* finiravl_h(avl* a, int i)
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




