/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

/*-- se completeaza cu definitiile functiilor implementate --*/

void RSD(TArb a)
{
	if (!a)
	{
		printf("-");
		return;
	}
	if (!a->st && !a->dr)
	{
		printf(" %d ", a->info);
		return;
	}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

int ex1(TArb a)
{
	if (a == NULL)
		return 0;
	if(a->st != NULL && a->dr != NULL)
	{
		if(a->info < a->st->info + a->dr->info)
		return 1 + ex1(a->st) + ex1(a->dr);
	}
	return ex1(a->dr) + ex1(a->st);
}
int DRS(TArb a)
{
	int ok = 0;
	int ns, nd;
	if(a == NULL)
	return 0;
	nd = DRS(a->dr);
	if(a->st != NULL || a->dr != NULL)
	{
		if(a->st == NULL && a->dr != NULL)
		printf("ordin 1 :%d\n", a->info);
		if(a->st != NULL && a->dr == NULL)
		printf("ordin 1 :%d\n", a->info);
		if(a->st != NULL && a->dr != NULL)
		printf("ordin 2 :%d\n", a->info);
	}
	else ok = 1;
	ns = DRS(a->st);
	return ns + nd + ok;
}

int verificare(TArb a)
{
	int ns, nd;
	int ok = 0;
	if(a == NULL)
	return 0;
	ns = verificare(a->dr);
	if(a->st == NULL ^ a->dr == NULL)
	{
		ok = 1;
	}
	nd = verificare(a->st);
	return nd + ns + ok;
}

int main()
{
	TArb arb;

	randomize();
	//do
	{
		arb = ConstrAA(5, random(16), -50, 50);
		AfiArb(arb);
		printf("noduri: %i   niveluri: %i\n",
			   NrNoduri(arb), NrNiv(arb));
		RSD(arb);

		/*-- se completeaza cu apelurile functiilor implementate --*/

		printf("\nInca un arbore ? [D/N] ");

		// if (getchar() == 'n')
		// 	break;
		printf("\n");
	} //while (1);

	int rez = ex1(arb);
	printf("\nasta e rez : %d \n\n", rez);
	rez = DRS(arb);
	printf("\nasta e rez la ex 2 : %d \n", rez);
	rez = verificare(arb);
	printf("\nasta e rez la ex 3 : %d \n", rez);
	DistrArb(&arb);
	//printf("\nda");
	return 0;
}
