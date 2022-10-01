#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int x, y;
} TPunct;

/* insereaza N elemente in coada c - elemente de tip TPunct
   cu valori intre v1 si v2 */
int GenereazaCoadaPuncte(void* c, size_t N, int v1, int v2)
{ 
  	int n = 0;
  	TPunct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!IntrQ(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

/* insereaza N elemente in stiva s - elemente de tip TPunct
   cu valori intre v1 si v2 */
int GenereazaStivaPuncte(void* s, size_t N, int v1, int v2)
{ 
	int n = 0;
  	TPunct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!Push(s, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPunct*)a).x, (*(TPunct*)a).y); 
	return 1;
}


int main()
{ 
	void *c, *s;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPunct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPunct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	lgc = GenereazaCoadaPuncte(c, 8, -5, 5);
  	lgs = GenereazaStivaPuncte(s, 6, 8, 14);
  
	printf("\nCoada cu %d elemente\n", lgc);
  	AfisareQ(c, AfiPct);
  	printf("\n\nStiva cu %d elemente\n", lgs);
   	AfisareS(s, AfiPct);

 	/* apeluri functii */

	DistrS(&s);
  	DistrQ(&c);
  	return 0;
}
