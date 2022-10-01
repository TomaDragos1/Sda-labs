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

void SRD(TArb a, int n, int m, int x, int **vector, int niv)
{
	if (a == NULL)
		return;

	SRD(a->st, n, m, x, vector, niv + 1);

	//printf("asta e numaru: %d asta e niv : %d\n", a->info, niv);
	if (niv >= n && niv <= m && a->info >= x)
	{
		printf("asta e numaru: %d asta e niv : %d ", a->info, niv);
		//(*vector)[niv]++;
		int ordin = 0;
		if (a->st != NULL && a->dr == NULL)
			ordin = 1;
		else if (a->st == NULL && a->dr != NULL)
			ordin = 1;
		else if (a->st != NULL && a->dr != NULL)
			ordin = 2;
		(*vector)[ordin]++;
		printf("asta e ordin %d\n", ordin);
	}
	SRD(a->dr, n, m, x, vector, niv + 1);
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int height(TArb a)
{
	if (a == NULL)
		return 0;

	return 1 + max(height(a->st), height(a->dr));
}

int verif_echilibrat(TArb a)
{
	int dr, st;
	if (a == NULL)
		return 1;

	dr = height(a->dr);
	st = height(a->st);

	if(abs(dr - st) <= 1 && verif_echilibrat(a->dr) && verif_echilibrat(a->st))
	{
		return 1;
	}

	return 0;
}


int DSR(TArb a, int n, int niv)
{	
	int st, dr;
	if(a == NULL)
	return 0;

	dr = DSR(a->dr, n, niv + 1);
	st = DSR(a->st, n, niv + 1);

	if(niv < n)
	{
		printf("aste e element :%d\n", a->info);
		int s = 1 + st + dr;
		printf("asta e recursiv : %d\n", s);
		return s; 
	}

	return 0;

}

int suma(TArb a, int nivel, int *suma_max)
{
	if(a == NULL) return 0;

	int st, dr;

	st = suma(a->st, nivel + 1, suma_max);
	dr = suma(a->dr, nivel + 1, suma_max);


}


// int ex3(TArb a, int x, int y)
// {
	
// }

int stramos(TArb a, int x, int y, int *contor)
{
	if(a == NULL)
	return 0;

	stramos(a->dr, x, y, contor);

	a->info = *contor;
	*contor++;

	stramos(a->st, x, y, contor);
}

int main()
{
	TArb arb;

	randomize();
	do
	{
		arb = ConstrAA(5, random(16), -50, 50);
		AfiArb(arb);
		printf("noduri: %i   niveluri: %i\n",
			   NrNoduri(arb), NrNiv(arb));
		RSD(arb);

		int n, m, x;
		int *vector = calloc(3, sizeof(int));
		int niv = 0;
		n = 3;
		m = 4;
		x = 3;
		printf("\n");
		int rez;
		rez = verif_echilibrat(arb);
		//printf("\n aste e rez:%d \n", rez);
		SRD(arb, n, m, x, &vector, niv);

		printf("\n\n");
		for (int i = 0; i < 3; i++)
		{
			printf("%d ", vector[i]);
		}
		printf("\n");

		/*-- se completeaza cu apelurile functiilor implementate --*/		
		rez = DSR(arb, n, niv);
		printf("\n aste e rez:%d \n", rez);

		int cont = 0;
		x = 0;
		int y = 0;
		stramos(arb, x, y , &cont);

		AfiArb(arb);

		DistrArb(&arb);
		printf("\nInca un arbore ? [D/N] ");

		if (getchar() == 'n')
			break;
		printf("\n");
	} while (1);

	return 0;
}
