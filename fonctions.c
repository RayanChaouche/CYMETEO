#include "header.h"

char** strtotab(char* l, int* nl, char* type)
{

	verifpchar(l);
	verifpint(nl);

	char c;
	char* s = &c;
	char** res = &s;
    	int count = 0;
    	char* tmp = l;
    	char* last_comma = 0;
    	char delim[3];
    	delim[0] = ';';
	delim[1] = 0;
	

	// compte le nombre d'elements a extraire
 	while (*tmp)
 	{
   	   if (';' == *tmp)
    	   {
     	       count++;
     	       last_comma = tmp;
     	   }
    	   tmp++;
   	}

	// ajoute de l'espace pour le token
	if(last_comma < (l + strlen(l) - 1))
	{
   		count ++;
	}

	*nl = count;

	count++;
	res = malloc(sizeof(char*) * count);

	if(res)
	{
		int idx  = 0;
		char* token = strtok(l, delim);
		
		while (token)
		{
			*(res + idx) = strdup(token);
			token = strtok(0, delim);
			idx++;
		}
		*(res + idx) = 0;
	}

	return(res);
}


char** creationligne(char* l, int* nbr_i, char* type)
{
	verifpchar(l);
	verifpchar(type);
	verifpint(nbr_i);

	char** ligne = strtotab(l, nbr_i, type);

	return ligne;
}

int min3(int a, int b, int c)
{ //retourne minimum parmi a,b,c
	if(a <= b && a <= c)
		return a;
	if(b <= a && b <= c)
		return b;
	else
		return c;
}

int max2(int a, int b)
{ //retourne max parmi a,b
	if(a>b)
		return a;
	else
		return b;
}

int max3(int a, int b, int c)
{ //retourne max parmi a,b,c
	if(a >= b && a >= c)
		return a;
	if(b >= a && b >= c)
		return b;
	else
		return c;
}

int min2(int a, int b)
{//retourne minimum parmi a,b
	if(a<b)
		return a;
	else
		return b;
}


int compare_dates(const char *date1, const char *date2) 
{ // retourne 1 si date1 > date2, -1 si date1<date2, 0 si date1 = date2
  int an1, an2, mois1, mois2, jour1, jour2, heure1, heure2, minute1, minute2, second1, second2;
  sscanf(date1, "%4d-%2d-%2dT%2d:%2d:%2d", &an1, &mois1, &jour1, &heure1, &minute1, &second1);
  sscanf(date2, "%4d-%2d-%2dT%2d:%2d:%2d", &an2, &mois2, &jour2, &heure2, &minute2, &second2);

  if (an1 > an2) 
  {
    return 1;
  } 
  else if (an1 < an2) 
  {
    return -1;
  } 
  else 
  {
    if (mois1 > mois2) 
    {
      return 1;
    } 
    else if (mois1 < mois2) 
    {
      return -1;
    } 
    else 
    {
      if (jour1 > jour2) 
      {
        return 1;
      } 
      else if (jour1 < jour2) 
      {
        return -1;
      } 
      else 
      {
        if (heure1 > heure2) 
        {
          return 1;
        } 
        else if (heure1 < heure2) 
        {
          return -1;
        } 
        else 
        {
          if (minute1 > minute2) 
          {
            return 1;
          } 
          else if (minute1 < minute2) 
          {
            return -1;
          } 
          else 
          {
            if (second1 > second2) 
            {
              return 1;
            } 
            else if (second1 < second2) 
            {
              return -1;
            } 
            else 
            {
              return 0;
            }
          }
        }
      }
    }
  }
}

