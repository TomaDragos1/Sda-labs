/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

void* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  AGL g = (AGL)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return (void*)g;
}

void DistrG(void** ag)
{ int i;
  AArc p, aux;
  for(i = 1; i < NrNoduri(*ag); i++)
  { p = ((AGL)(*ag))->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free(((AGL)(*ag))->x);
  free(*ag);
  *ag = NULL;
}


int CostArc(void* g, int s, int d)
{   /* intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */

	AArc p;
	int cost = 0;

	s++;
	d++;
	p = *(((AGL)g)->x + s);

	while (p) {
		if (p->d == d) {
			cost = p->c;
			break;
		}
		p = p->urm;
	}

	return cost;
}

int NrNoduri(void* g)
{ return ((AGL)(g))->n; }

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

void AfiGrafL(void* g) {
	int i, j, k, n = NrNoduri(g);
	AArc p;

	for (i = 1; i <= n; i++) {
		p = *(((AGL) g)->x + i);
		printf("%d : ", i);
		while (p) {
			k = p->c;
			if (k == ArcInex) printf("  - ");
			else printf("%d(%i) ", p->d, k);
			p = p->urm;
		}
		printf("\n");
	}
}

void AfiGrafM(void *g)
{
	printf("This is an adjacency list represented graph. Use AfiGrafL\n");
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  AGL g;
  int s, d;
  int x;
  AArc *p, aux;
  int n;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen (numefis, "rt");
  if (!f) return -2;
  if (!fscanf (f, "%i", &n) || n <= 0) return -3;
  *ag = AlocG(n);
  g = *(AGL*)ag;
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &s, &d, &x) == 3)
  { if (s < 1 || s > n || d < 1 || d > n)
    { fclose(f); return -4;}
    p = g->x + s;
    while (*p && (*p)->d < d) p = &(*p)->urm;
    aux = (TCelArc*)calloc(sizeof(TCelArc),1);
    if (!aux) return -2;                     /* criza spatiu */
    aux->urm = *p; *p = aux;
    aux->d = d; aux->c = x;
  }
  fclose(f);
  return 1;
}

