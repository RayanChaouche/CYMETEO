#include "header.h"


/*
	FAUT TEST T1
	FAUT TEST M
	FAUT FAIRE P1,2,3
*/


int main(int argc, char** argv)
{
	/*	
		(0 ./exec)
		1 -f nom du fichier entree = 1 arg
		2 -o nom du fichier sortie = 1 arg
		3 -type (t1, p2, h, w...)

		4 --mode (abr, avl, tab) = 1 arg	(optionel)	avl par defaut
		5 -r decroissant = 1 arg		(optionel)	croissant sinon

		argc = 4 à 6
	*/
	
	
	char* input_fich = (argv[1]+1);
	char* output_fich = (argv[2]+1);
	char* type = (argv[3]+1);
	char* mode_sort = NULL;
	int decroissant = 0;


	if (argc == 5)
	{
		if(argv[4][0] == '-' && argv[4][1] == '-')
		{
			mode_sort = (argv[4]+2);
			verifmode(mode_sort);
		}

		else if(argv[4][0] == '-' && argv[4][1] == 'r')
			decroissant = 1;

		else
			exit(1);
	}
	else if (argc == 6)
	{
		mode_sort = (argv[4]+2);
		decroissant = 1;
	}
	

	if(!strcmp(type, "t1"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_t1_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_t1_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_t1_avl(input_fich, output_fich, decroissant);

		}
		
	}
	else if(!strcmp(type, "t2"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_t2_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_t2_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_t2_avl(input_fich, output_fich, decroissant);

		}
		
	}
	else if(!strcmp(type, "t3"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_t3_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_t3_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_t3_avl(input_fich, output_fich, decroissant);

		}
		
	}
	else if(!strcmp(type, "p1"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_p1_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_p1_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_p1_avl(input_fich, output_fich, decroissant);

		}
		
	}
	
	else if(!strcmp(type, "p2"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_p2_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_p2_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_p2_avl(input_fich, output_fich, decroissant);

		}
		
	}

	else if(!strcmp(type, "p3"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_p3_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_p3_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_p3_avl(input_fich, output_fich, decroissant);

		}
		
	}

	else if(!strcmp(type, "h"))
	{
		if(!strcmp(mode_sort, "tab"))
		{
			//tri_h_tab(input_fich, output_fich);

		}
		else if(!strcmp(mode_sort, "abr"))
		{
			//TriDecroissantAltitude(input_fich, output_fich);

		}
		else
		{
			tri_h_avl(input_fich, output_fich);

		}
		
	}

	else if(!strcmp(type, "m1"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}
		else
		{
			tri_m1_avl(input_fich, output_fich);

		}
		
	}
	else if(!strcmp(type, "m2"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}
		else
		{
			tri_m2_avl(input_fich, output_fich);

		}
		
	}
	else if(!strcmp(type, "m"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//TriDecroissantHumidite(input_fich, output_fich);

		}

		
	}

	else if(!strcmp(type, "w"))
	{
		if(!strcmp(mode_sort,"tab"))
		{
			//tri_w_tab(input_fich, output_fich, decroissant);

		}
		else if(!strcmp(mode_sort,"abr"))
		{
			//tri_w_abr(input_fich, output_fich, decroissant);

		}
		else
		{
			tri_w_avl(input_fich, output_fich, decroissant);

		}
		
	}
	//toutes les fonctions ne sont pas faites, il faut effacer celle qui ne sont pas encore faites

	


	printf("\nfini\n");
	
	return 0;
}




