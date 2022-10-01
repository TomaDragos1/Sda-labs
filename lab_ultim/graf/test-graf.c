/*--- test-graf.c ---*/
#include "graf.h"


int main()
{
	void* g;

	if (CitGraf(&g) <= 0)
	{ printf("-=- eroare la citire -=-\n"); return -1;}
	printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
	AfiGrafM(g);
	AfiGrafL(g);

	/*-- apel functii definite --*/
	printf("\n======================== Pb 1 ========================\n");

	if (isCyclic(g))
		printf("Graful este ciclic.\n");
	else printf("Graful este aciclic.\n");

	printf("\n======================================================\n");

	DistrG(&g);
	return 0;
}
