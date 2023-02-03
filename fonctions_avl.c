#include "header.h"


avl* creationavl(char* l, char* type)
{
	verifpchar(l);
	verifpchar(type);

	avl* nv = malloc(sizeof(avl));
	nv->equilibre = 0;
	nv->fg = NULL;
	nv->fd = NULL;
	strncpy(nv->cligne, l, TAILLE);
	nv->taille_ligne = 0;
	nv->ligne = creationligne(l, &(nv->taille_ligne), type);
	nv->nbr_moyenne[0] = 1;
	nv->nbr_moyenne[1] = 1;

	return nv;
}

avl* rotagauche(avl* a)
{
	verifpavl(a);

	int eq_a, eq_p;

	avl* pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - max2(eq_p, 0) - 1;
	pivot->equilibre = min3(eq_a-2, eq_a+eq_p-2, eq_p-1);
	a = pivot;

	return a;
}

avl* rotadroite(avl* a)
{
	verifpavl(a);

	int eq_a, eq_p;

	avl* pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - min2(eq_p, 0) + 1;
	pivot->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1);
	a = pivot;

	return a;
}

avl* doublerotagauche(avl* a)
{
	verifpavl(a);
	a->fd = rotadroite(a->fd);
	return rotagauche(a);
}

avl* doublerotadroite(avl* a)
{
	verifpavl(a);
	a->fg = rotagauche(a->fg);
	return rotadroite(a);
}

avl* equilibreravl(avl* a)
{
	verifpavl(a);
	
	if(a->equilibre >= 2)
	{	
		if(a->fd->equilibre >= 0)
			return rotagauche(a);
		else
			return doublerotagauche(a);
	}
	else if(a->equilibre <= -2)
	{
		if(a->fg->equilibre <= 0)
		{
			return rotadroite(a);
		}
		else
		{		
			return doublerotadroite(a);	
		}	
	}


	return a;
}

char* actualiseravl_cligne(avl* a)
{	// rentre les valeurs de a->ligne dans a->cligne

	verifpavl(a);
	
	char* verif = NULL;
	char virgule = ';';
	
	strcpy(a->cligne, a->ligne[0]);
	strncat(a->cligne, &virgule, 1);
	for(int i = 1; i < a->taille_ligne; i++)
	{
		strcat(a->cligne, a->ligne[i]);
		if(i < a->taille_ligne-1)
		{
			strncat(a->cligne, &virgule, 1);
		}
		
	}
	if(!strstr(a->cligne, "\n"))
		strcat(a->cligne, "\n");

	if((verif = strstr(a->cligne, ","))) // on change la ',' des coordonnees
	{
		*verif = ';';
	}

	

	return a->cligne;	
}

int infstrictavl(avl* a, avl* b, int idx, char* type)	
{// retourne 1 si a > b par rapport au type de trie que l'on fait, 0 sinon

	verifpavl(a);
	verifpavl(b);
	verifpchar(type);

	if(!strcmp(type, "t1"))
	{
		return infstrictavl_t1(a, b, idx);
	}
	else if(!strcmp(type, "t2"))
	{
		return infstrictavl_t2(a,b, idx);
	}
	else if(!strcmp(type, "t3"))
	{
		return infstrictavl_t3(a,b, idx);
	}
	else if(!strcmp(type, "p1"))
	{
		return infstrictavl_p1(a, b, idx);
	}
	else if(!strcmp(type, "p2"))
	{
		return infstrictavl_p2(a,b, idx);
	}
	else if(!strcmp(type, "p3"))
	{
		return infstrictavl_p3(a,b, idx);
	}
	else if(!strcmp(type, "w"))
	{
		return infstrictavl_w(a,b, idx);
	}
	else if(!strcmp(type, "h"))
	{
		return infstrictavl_h(a, b, idx);
	}
	else if(!strcmp(type, "m1"))
	{
		return infstrictavl_m1(a, b, idx);
	}
	else if(!strcmp(type, "m2"))
	{
		return infstrictavl_m2(a, b, idx);
	}
	
	return 0;
}

int egalavl(avl* a, avl* b, char* type)
{ // fait le cas ou a = b selon le type de trie (ex: cumul de valeurs pour faire moyenne)
	verifpchar(type);
	verifpavl(a);
	verifpavl(b);

	if(!strcmp(type, "t1"))
	{
		a = egalavl_t1(a, b, 1);
	}
	else if(!strcmp(type, "t2"))
	{
		a = egalavl_t2(a, b, 1);
	}
	else if(!strcmp(type, "t3"))
	{
		a = egalavl_t3(a, b, 1);
	}
	else if(!strcmp(type, "p1"))
	{
		a = egalavl_p1(a, b, 1);
	}
	else if(!strcmp(type, "p2"))
	{
		a = egalavl_p2(a, b, 1);
	}
	else if(!strcmp(type, "p3"))
	{
		a = egalavl_p3(a, b, 1);
	}
	else if(!strcmp(type, "w"))
	{
		a = egalavl_w(a, b, 1);
	}
	else if(!strcmp(type, "h"))
	{
		a = egalavl_h(a, b, 1);
	}
	
	else if(!strcmp(type, "m1"))
	{
		a = egalavl_m(a, b, 0);
	}
	return 1;
}

avl* insertavl(avl* a, avl* nv, int* h, int idx, char* type)
{
	verifpavl(nv);
	verifpchar(type);

	if (a == NULL)
	{	
		(*h)++;
		a = nv;

		return a; 
	}
	else if(infstrictavl(nv, a, idx, type))	// les comparaisons change en fonctions des types
	{	
		a->fg = insertavl(a->fg, nv, h, idx, type);	
		*h = -(*h);
	}
	else if(infstrictavl(a, nv, idx, type))
	{
		a->fd = insertavl(a->fd, nv, h, idx, type);
	}
	else
	{
		egalavl(a, nv, type); // dans le cas où la ligne est egal, on doit faire des operations differentes selon les types
		*h = 0;
	}

	if(*h != 0)
	{
		a->equilibre = a->equilibre + *h;
		a = equilibreravl(a);
		if( a->equilibre == 0)
			*h = 0;
		else
			*h = 1;
	}

	return a;
}

avl* insertavl_appel(avl* a, char* ligne, int idx, char* type)
{
	verifpchar(ligne);
	verifpchar(type);

	avl* nv = creationavl(ligne, type);


	int* h = NULL;
	if(a)
	{
		h = &(a->equilibre);
	}
	else
	{
		a = nv;
		return a;
	}

	return insertavl(a, nv, h, idx, type);
}

avl* construireavl(char* nomf, int idx, char* type)
{
	verifpchar(nomf);
	verifpchar(type);	

	avl* a = NULL;	
	char ligne[TAILLE];
	int verif = 0;
	size_t len = 0;

	//ouvrir le fichier
	FILE * fichier = fopen(nomf,"r");
	if (fichier == NULL){
		printf("pas de fichier d'entree de ce nom");
		exit(2);
	}
	
	while(fgets(ligne, sizeof(ligne), fichier) != NULL) // on lit chaque ligne
	{

		//ligne = prendreligne(&verif, len, fichier);

		printf("\n\n\n'%s' \n\n\n", ligne);
		
		//puis on ajoute la ligne a l'avl
		a = insertavl_appel(a, ligne, idx, type);
		
	}

	fclose(fichier);	

	// on fait les operations necessaires sur les donnees de l'avl
	finiravl(a, type);


	return a;
}

avl* finiravl(avl* a, char* type)
{ // cette fonction realise toute les operations necessaire une fois l'avl fini
  // ex: diviser la somme de valeur pour obtenir la moyenne
	verifpavl(a);
	verifpchar(type);
	
	if(!strcmp(type, "t1"))
	{
		finiravl_t1(a, 1);
	}
	else if(!strcmp(type, "t2"))
	{
		finiravl_t2(a, 1);
	}
	else if(!strcmp(type, "t3"))
	{
		finiravl_t3(a, 0);
	}
	else if(!strcmp(type, "p1"))
	{
		finiravl_p1(a, 1);
	}
	else if(!strcmp(type, "p2"))
	{
		finiravl_p2(a, 1);
	}
	else if(!strcmp(type, "p3"))
	{
		finiravl_p3(a, 0);
	}
	else if(!strcmp(type, "w"))
	{
		finiravl_w(a, 1);
	}
	else if(!strcmp(type, "h"))
	{
		finiravl_h(a, 1);
	}
	else if(!strcmp(type, "m1"))
	{
		finiravl_m(a, 1);
	}
	
}






