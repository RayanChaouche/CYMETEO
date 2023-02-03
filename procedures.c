#include "header.h"

void verifpchar(char* c)
{
	if(c == NULL)
	{
		printf("\nerreur pointeur sur char NULL\n");
		exit(4);
	}
}

void verifpint(int* n)
{
	if(n == NULL)
	{
		printf("\nerreur pointeur sur int NULL\n");
		exit(4);
	}
}

void verifn(int n)
{
	if(n < 0)
	{
		printf("\nerreur n < 0\n");
		exit(4);
	}
}

void verifavl(avl a)
{
	if(a.taille_ligne < 0 || (a.nbr_moyenne)[0] < 0 || (a.nbr_moyenne)[1] < 0)
	{
		printf("\nerreur nbr_moyenne ou taille_ligne < 0\n");
		exit(4);
	}
}

void verifpavl(avl* a)
{
	if(a==NULL)
	{
		printf("\npointeur avl sur null\n");
		exit(4);
	}
	verifavl(*a);
}
/*
void verifabr(abr a)
{
	if(a.taille_ligne < 0 || a.nbr_moyenne[0] < 0 || a.nbr_moyenne[1] < 0)
	{
		printf("\nerreur nbr_moyenne ou taille_ligne < 0\n");
		exit(4);
	}
}

void verifpabr(abr* a)
{
	if(a==NULL)
	{
		printf("\npointeur abr sur null\n");
		exit(4);
	}
	verifabr(*a);
}
*/	
void verifmode(char* c)
{
	verifpchar(c);
	if(strcmp(c, "abr")!=0 && strcmp(c, "avl")!=0 && strcmp(c, "tab")!=0)
	{	
		printf("mode non valide");
		exit(1);
	}
}

void verifpfile(FILE * file)
{
	if(file == NULL)
	{
		printf("poiteur file sur null");
		exit(4);
	}
}

void parcourscroissantavl_appel(avl* a, char* nomf)
{ // procedure pour traiter un avl dans l'ordre decroissant

	verifpchar(nomf);

	if(a)
	{
		verifpavl(a);
		
		FILE* output_fichier = fopen(nomf, "w");
		if(output_fichier==NULL)
			exit(3);
		
		parcourscroissantavl(a, output_fichier);
	}
}

void parcourscroissantavl(avl* a, FILE* fichier)
{ // procedure pour traiter un avl dans l'ordre croissant

	verifpfile(fichier);

	if(a)
	{
		verifpavl(a);
		
		parcourscroissantavl(a->fg, fichier);
			traiteravl(a, fichier);
		parcourscroissantavl(a->fd, fichier);
	}
}

void parcoursdecroissantavl_appel(avl* a, char* nomf)
{ // procedure pour traiter un avl dans l'ordre decroissant

	verifpchar(nomf);

	if(a)
	{
		verifpavl(a);
		
		FILE* output_fichier = fopen(nomf, "w");
		if(output_fichier==NULL)
			exit(3);
		
		parcoursdecroissantavl(a, output_fichier);
	}
}

void parcoursdecroissantavl(avl* a, FILE* fichier)
{ // procedure pour traiter un avl dans l'ordre decroissant

	verifpfile(fichier);

	if(a)
	{
		verifpavl(a);

		parcoursdecroissantavl(a->fd, fichier);
			traiteravl(a, fichier);
		parcoursdecroissantavl(a->fg, fichier);
	}
}


void traiteravl(avl* a, FILE* out_fichier)
{	// rentre la ligne du noeud dans le fichier de sortie
	
	verifpfile(out_fichier);
	
	fprintf(out_fichier, "%s", a->cligne);
}






