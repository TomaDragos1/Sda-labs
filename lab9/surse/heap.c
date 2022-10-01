#include "heap.h"

#define NMAX 25
static char desen[20][81], cri[] = "xxx"; /* caractere reprezentare arbore, info */

THeap AlocaHeap(int nMax, TRel rel)
{
	THeap h = (THeap)malloc(sizeof(struct Heap));
	if (!h)
		return NULL;

	h->v = (int *)malloc(nMax * sizeof(int));
	if (!h->v)
	{
		free(h);
		return NULL;
	}

	h->nMax = nMax;
	h->ne = 0;
	h->rel = rel;

	return h;
}

void DistrugeHeap(THeap *ah)
{
	free((*ah)->v);
	free(*ah);
	*ah = NULL;
}

/**
 * Functie auxiliara pentru desenarea unui arbore cu radacina in centrul liniei
 * dif - distanta pe orizontala intre radacina si cei doi descendenti
 *	Exemple:  dif = 5	|	 dif = 2	|
 *			    xxx				 xxx
 *		    ___/ \___			  / \
 */
void AfiHeapAux(THeap h, int k, int centru, int linie, int dif)
{
	int s, d;

	desen[linie][0] = ':';

	if (dif <= 1)
	{ /* spatiu de afisare insuficient -> ... */
		memset(desen[linie] + centru, '.', 3);
		return;
	}

	desen[linie][centru] = '|';					   /* legatura spre radacina */
	sprintf(cri, "%3i", h->v[k]);				   /* converteste valoare info la 3 caractere */
	d = (cri[0] == ' ') ? 2 : 1;				   /* decalaj fata de centru */
	memcpy(desen[linie + 1] + centru - d, cri, 3); /* copiaza cele 3 caractere in desen */
	desen[linie + 1][0] = ':';
	desen[linie + 2][0] = ':';

	if ((s = k * 2 + 1) < h->ne)
	{
		desen[linie + 2][centru - 1] = '/';
		memset(desen[linie + 2] + centru - dif + 1, '_', dif - 2);
		AfiHeapAux(h, s, centru - dif, linie + 3, (dif + 1) / 2);
	}

	if (s + 1 < h->ne)
	{
		desen[linie + 2][centru + 1] = '\\';
		memset(desen[linie + 2] + centru + 2, '_', dif - 2);
		AfiHeapAux(h, s + 1, centru + dif, linie + 3, (dif + 1) / 2);
	}
}

/**
 * Afiseaza arborele r in partea superioara a ecranului
 */
void AfiHeap(THeap h, int linie)
{
	int j;
	for (j = 0; j < 20; ++j)
		memset(desen[j], ' ', 79);

	if (h->ne == 0)
	{
		printf("\t\t\t\t-=- Arbore VID -=-\n");
	}
	else
	{
		printf("\n");
		AfiHeapAux(h, 0, 40, 0, 19); /* afiseaza incepand de la mijlocul primei linii de pe ecran */

		for (j = 0; j < 16 && desen[j][0] == ':'; ++j)
		{
			desen[j][79] = '\0';
			printf("%s\n", desen[j] + 1);
		}
	}

	printf("\n");
}

/**
 * Intoarce 1 daca @valParinte < @valCopil, 0 altfel
 */
int RelMinHeap(int valParinte, int valCopil)
{
	return valParinte < valCopil;
}

/**
 * Intoarce 1 daca @valParinte > @valCopil, 0 altfel
 */
int RelMaxHeap(int valParinte, int valCopil)
{
	return valParinte > valCopil;
}

int leftchild(int i)
{
	return 2 * i + 1;
}

int rightchild(int i)
{
	return 2 * i + 2;
}

int parent(int i)
{
	return (i - 1) / 2;
}
void swap(int *el1, int *el2)
{
	int a = *el1;
	*el1 = *el2;
	*el2 = a;
}

void InsHeap(THeap h, int val)
{
	int parinte = (h->ne - 1) /2;
	h->v[h->ne] = val;
	int temp = h->ne;
	h->ne ++;
	while(!h->rel(h->v[parinte], val))
	{
		int aux = h->v[parinte];
		h->v[parinte] = h->v[temp];
		h->v[temp] = aux;
		temp = parinte;
		parinte = (parinte - 1)/2;
	}
}

void ConstrHeap(THeap h, int i)
{
	int l = leftchild(i);
	int r = rightchild(i);
	int next_node = i;
	if (l < h->ne && !h->rel(h->v[i], h->v[l]))
		next_node = l;
	if (r < h->ne && h->rel(h->v[r], h->v[next_node]))
		next_node = r;
	if (next_node != i)
	{
		swap(&h->v[i], &h->v[next_node]);
		ConstrHeap(h, next_node);
	}
}
int ExtrHeap(THeap h)
{
	int root = h->v[0];

	//h->ne--;
	h->v[0]= h->v[h->ne - 1];
	h->ne --;
	ConstrHeap(h, 0);

	return root;

}

void HeapSort(int *v, int nv, TRel rel)
{
	THeap h;
	h = AlocaHeap(NMAX, rel);
	for(int i = 0 ; i < nv ; i ++)
	h->v[i] = v[i];
	h->ne = nv;
	//h->rel = rel;

	for(int i = nv / 2 - 1 ; i >=0 ; i--)
	ConstrHeap(h, i);

	for(int i = 0 ; i < nv - 1 ; i++)
	{
		swap(&h->v[h->ne - 1], &h->v[0]);
		h->ne--;
		ConstrHeap(h, 0);
	}
	for(int i = 0 ; i < nv ; i++)
	{
		printf("%d ", h->v[i]);
	}
	printf("\n");


}

int main()
{
	THeap h;

	h = AlocaHeap(NMAX, RelMinHeap);
	if (!h)
		return 1;

	/* Demo structura min-heap */
	int i, heapv[] = {2, 5, 3, 11, 9, 13, 8},
		   nh = sizeof(heapv) / sizeof(heapv[0]);
	printf("Min-heap:\n");
	for (i = 0; i < nh; ++i)
		h->v[h->ne++] = heapv[i];
	//AfiHeap(h, 13);
	//h->ne = 0;
	//InsHeap(h, 4);
	AfiHeap(h, 13);
	//printf("%d", ExtrHeap(h));
	HeapSort(h->v , h->ne , RelMaxHeap);
	//DistrugeHeap(&h);

	
	AfiHeap(h, 13);

	return 0;
}
