#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

typedef struct celula2
{
	void *info;
	struct celula2 *ant, *urm;
} Tcelula2, *TL2;

typedef struct coord
{
	int x;
	int y;
} cord;

TL2 ex1(TL2 s, float *rez)
{

	TL2 p;
	TL2 s2 = NULL;
	s2 = malloc(sizeof(Tcelula2));
	s2->urm = s2;
	s2->ant = s2;
	s2->info = s2;

	int cont1 = 0, cont2 = 0;

	for (p = s->urm; p != s;)
	{	cont1++;
		cord *info = (cord *)(p->info);
		//printf("celula : %d %d\n", info->x, info->y);
		if (info->x > 0 && info->y > 0)
		{	
			cont2++;
			TL2 pars = s2->urm;
			for (pars = s2->urm; pars != s2; pars = pars->urm)
			{
				cord *info2 = (cord *)(pars->info);
				//printf("mata celula : %d %d\n", info2->x, info2->y);
				if(info2->x < info->x)
				break;
			}
		//printf("fut prost %d %d\n", info->x , info->y);

		p->ant->urm = p->urm;
		p->urm->ant = p->ant;

		TL2 aux = p->urm;
		p->ant = pars;
		p->urm = pars->urm;
		pars->urm->ant = p;
		pars->urm = p;

		p = aux;

		}
		else
			p = p->urm;
	}

	int aux = cont1 - cont2;
	*rez = (float)aux / (float)cont1;


	return s2;
}

int main()
{
	TL2 santi = NULL;
	santi = malloc(sizeof(Tcelula2));
	santi->urm = santi;
	santi->ant = santi;
	santi->info = NULL;

	srand(time(NULL));
	int a = rand() % 72;
	a = a - 36;

	TL2 crt_el = santi;

	int contor = 0;
	while (contor != 7)
	{
		TL2 new_cel = malloc(sizeof(Tcelula2));
		new_cel->ant = NULL;
		new_cel->urm = NULL;
		cord *new_info = malloc(sizeof(cord));

		int a = rand() % 72;
		new_info->x = a - 36;

		int b = rand() % 72;
		new_info->y = b - 36;

		new_cel->info = new_info;

		cord *info = (cord *)(new_cel->info);

		//printf("celula : %d %d\n", info->x, info->y);

		//INSERARE

		new_cel->ant = santi;
		new_cel->urm = santi;
		crt_el->urm->ant = new_cel;
		crt_el->urm = new_cel;

		crt_el = crt_el->urm;

		contor++;
	}

	printf("\n");

	float rez = 0;
	TL2 rezd = ex1(santi, &rez);

	TL2 p;
	for (p = rezd->urm; p != rezd; p = p->urm)
	{
		cord *info = (cord *)(p->info);
		printf("celula : %d %d\n", info->x, info->y);
	}

	printf("\n%f\n", 100 * rez);


	return 0;
}
