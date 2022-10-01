/*--- graf-M.c --- Graf implementat cu Matrice de adiacente --*/

#include "graf-M.h"
#include "graf.h"
#include <string.h>

void* AlocG(int nr)
{ int i;
  AGM g = (AGM)malloc (sizeof(TGM));              /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (int*)malloc(nr * nr * sizeof(int)); /* matrice liniarizata */
  if (!g->x) { free(g); return NULL; }
  for (i = 0; i < nr * nr; i++)
    g->x[i] = ArcInex;
  g->n = nr;
  return (void*)g;
}


void DistrG(void** ag)
{ free (((AGM)(*ag))->x);
  free(*ag);
  * ag = NULL;
}


int CostArc(void* g, int s, int d)
{ 
  /* functia intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */

	int cost = ((AGM)g)->x[s * NrNoduri(g) + d];

	return cost;
}

int NrNoduri(void* g)
{
    return ((AGM)g)->n;
}

void printCycle(int recStack[], int v, int i, int n) {
	printf("Ciclul gasit este format din urm. varfuri: \n");
	for (int j = 0; j < n; ++j) {
		if (recStack[j]) {
			printf("%d ", j + 1);
		}
	}

	printf("\nMuchia inapoi este: %d %d\n", v + 1, i + 1);
}

int isCyclicUtil(void *g, int v, int visited[], int recStack[]) {

	if (!visited[v]) {
		// add to visited
		visited[v] = 1;
		// add to recursion stack
		recStack[v] = 1;

		// iterate through neighbors
		for (int i = 0; i < NrNoduri(g); ++i) {
			// the weight of the edge will be != 0 if it's a neighbour
			if (CostArc(g , v, i)) {
				// valid path, but at some point forward a cycle is detected
				if (!visited[i] && isCyclicUtil(g, i, visited, recStack))
					return 1;
				// the neighbour is on the recursion stack, it's been visited
				// on the current path
				else if (recStack[i]) {

					printCycle(recStack, v, i, NrNoduri(g));
					return 1;
				}

			}
		}
	}

	// remove node from recursion stack
	recStack[v] = 0;
	return 0;
}

int isCyclic(void *g) {

	int n = NrNoduri(g);
	int visited[n];
	int recStack[n];

	for (int i = 0; i < n; ++i) {
		visited[i] = recStack[i] = 0;
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\b", i);


		if (!visited[i] && isCyclicUtil(g, i, visited, recStack)) {
			return 1;
		}

	}

	return 0;
}

void AfiGrafM(void* g)
{ int i,j,k, n = NrNoduri(g);
	for (i = 0; i < n; i++)
	{ for (j = 0; j < n; j++)
		{ k = ((AGM)g)->x[i * n + j];
			if(k == ArcInex) printf("  - ");
			else printf("%3i ", k);
		}
		printf("\n");
	}
}

void AfiGrafL(void *g)
{
	printf("This is an adjacency matrix represented graph. Use AfiGrafM\n");
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  int i, j, n;
  int x;
  AGM g;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen(numefis, "rt");
  if (!f) return -2;
  if (!fscanf(f, "%i", &n) || n <= 0) return -3;
  *ag = g = (AGM)AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &i, &j, &x) == 3)
  { if (i < 1 || i > n || j < 1 || j > n)
    { fclose(f); return -4;}
      ((AGM)g)->x[(i-1)*((AGM)g)->n + j-1] = x;
  }
  fclose(f);
  return 1;
}

