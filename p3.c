#include "header.h"

int tri_p3_avl(char* input_fich, char* output_fich, int decroissant)
{

	char* type = "p3";
	avl* a = construireavl(input_fich, 1, type);
	
	if(!decroissant)
		parcourscroissantavl_appel(a, output_fich);
	else
		parcoursdecroissantavl_appel(a, output_fich);
}

int infstrictavl_p3(avl* a, avl* b, int idx)
{	//return 1 si a < b (en comparant par ordre chonologique puis par rapport a l'id si la date est la meme) return 0 sinon
	// idx represente l'indice du champ que l'on trie

	verifpavl(a);
	verifpavl(b);

	//on verifie si on tri des dates ou autres chose (le format de la date dans les donnees ayant un "T")
	char* verif1_a = strstr(a->ligne[idx], "T");
	char* verif1_b = strstr(b->ligne[idx], "T");

	
	if(verif1_a && verif1_b) //si on a 2 dates, on fait la comparaison de date
	{

		int cmp_date = compare_dates(a->ligne[idx], b->ligne[idx]);
		if(cmp_date == -1)
		{
			return 1;
		}

		else if(!cmp_date) // si les dates sont egales, on compare les id
		{
			if(a->ligne[idx-1] < b->ligne[idx-1])	// dans notre situation, indice de date = 2, indice de id = 1
			{
				return 1;
			}
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



avl* egalavl_p3(avl* a, avl* b, int i)
{	// on fait rien dans cette situation
	
	verifpavl(a);
	verifpavl(b);
	
	return a;
}

avl* finiravl_p3(avl* a, int i)
{	// cette fonction actualise les lignes (ca fait rien en vrai mais c'est un secret)

	if(a)
	{
		verifpavl(a);

		// on rentre les valeurs de la ligne dans le string
		strcpy(a->cligne, actualiseravl_cligne(a));

		finiravl_p3(a->fd, i);
		finiravl_p3(a->fg, i);
	}
	
	return a;
}





























