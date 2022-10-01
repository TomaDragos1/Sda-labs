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

int parcurgere(TArb a)
{
	int dr, st;
	if (a == NULL)
		return 1;
	st = NrNiv(a->st);
	dr = NrNiv(a->dr);
	if (abs(dr - st) <= 1 && parcurgere(a->st) && parcurgere(a->dr))
		return 1;

	return 0;
}
int DSR(TArb a, int n, int crt)
{
	int ls, ld;
	if (n == crt)
		return 0;
	if (a == NULL)
		return 0;
	ld = DSR(a->dr, n, crt + 1);
	ls = DSR(a->st, n, crt + 1);
	printf("informatia de la nivelul %d este : %d\n", crt, a->info);
	return ls + ld + 1;
}
int ex3(TArb a, int crt, int x, int y, int *ok)
{
	int ls = -2, ld = -2;
	if (a == NULL)
		return -2;
	//if(*ok == 1) return -2;
	ls = ex3(a->st, crt + 1, x, y, 0);
	ld = ex3(a->dr, crt + 1, x, y, 0);
	if (ls == -1 || ld == -1)
		return -1;
	if (a->info >= x && a->info <= y)
	{
		if (ls != -2 || ld != -2)
			return -1;
		else
			return crt;
	}
	if (ls != -2)
		return ls;
	else
		return ld;
}

int cautare_nod(TArb nod, int x)
{
	// if(nod == NULL) return 0;

	// if(nod->info == x || nod->info == y)
	// {
	// 	return 1;
	// }
	// return cautare_nod(nod->st, x, y);
	// return cautare_nod(nod->dr, x, y);

	if (nod == NULL)
		return 0;

	if (x == nod->info)
		return 1;
	if (x < nod->info)
		return cautare_nod(nod->st, x);
	return cautare_nod(nod->dr, x);
}

int gasire_cale(TArb a, int x, int **cale)
{
	int contor = 0;
	while (a != NULL)
	{
		if (a->info == x)
			return 1;
		if (x < a->info)
		{
			//printf("sa dau la muie %d\n", a->info);
			(*cale)[contor] = a->info;
			//printf("sa dau la muie %d\n", (*cale)[contor]);
			contor++;
			a = a->st;
		}
		else
		{
			//printf("sa dau la muie sda %d\n", a->info);
			(*cale)[contor] = a->info;
			//printf("sa dau la muie %d\n", (*cale)[contor]);
			contor++;
			a = a->dr;
		}
	}

	//printf("sug pula %d\n", contor);
	return 0;
}

int stramos(TArb a, int x, int y)
{

	int *cale1 = calloc(100, sizeof(int));
	int *cale2 = calloc(100, sizeof(int));

	int nr1 = gasire_cale(a, x, &cale1);
	int nr2 = gasire_cale(a, y, &cale2);

	if (nr1 == 0 || nr2 == 0)
		return 0;

	int i = 0;
	while (1)
	{
		if (cale2[i] != cale1[i] || (cale2[i] == 0 && cale1[i] == 0))
		{
			return cale1[i - 1];
		}

		i++;
	}
}

int suma(TArb a, int max)
{
	if (a == NULL)
		return 0;

	int dr = suma(a->dr, max);
	int st = suma(a->st, max);

	if (a->info < dr)
		return dr;
	else if (a->info < st)
		return st;

	return a->info;
}

int main()
{
	TArb arb = NULL;
	int elem[9] = {15, 7, 17, 6, 8, 16, 34, 89, 4}, i;

	for (i = 0; i < 9; i++)
		Inserare_ABC(&arb, elem[i]);
	AfiArb(arb);
	printf("noduri: %i   niveluri: %i\n",
		   NrNoduri(arb), NrNiv(arb));
	RSD(arb);

	/*-- se completeaza cu apelurile functiilor implementate --*/
	int numar = 0;
	int n = 3;
	int crt = 0;
	printf("\n");
	numar = DSR(arb, n, crt);
	printf("asata e nuamrul %d\n", numar);
	printf("\n");
	int a = parcurgere(arb);
	printf("asta e rez pt ex 1 :  %d\n", a);
	int rez = 0;
	int ok = 0;
	//rez = ex3(arb, crt, 60, 70, &ok);
	//printf("rez = %d\n", rez);
	//int crt = 0;

	int x = 20;
	int y = 8;
	int nod = 0;
	//rez = stramos(arb, x, y);
	//printf("\n aste e nodu : %d\n", rez);
	int max = 0;
	rez = suma(arb, max);

	printf("mata %d\n", rez);

	DistrArb(&arb);
	return 0;
}
