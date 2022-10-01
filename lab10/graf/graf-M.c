/*--- graf-M.c --- Graf implementat cu Matrice de adiacente --*/
#include "graf-M.h"
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
  return ((AGM)g)->x[(s - 1) * ((AGM)g)->n + d - 1];
  //return ArcInex;
}

int Grad_iesire(void *g, int n)
{
  int grad = 0;
  for (int i = 1; i < ((AGM)g)->n + 1; i++)
  {
    if (CostArc(g, n, i))
      grad++;
  }

  return grad;
}

int ArcCostMax(void *g, int *s, int *d)
{
  int minim = 0;
  for (int i = 1; i < ((AGM)g)->n + 1; i++)
  {
    for (int j = 1; j < ((AGM)g)->n + 1; j++)
    {
      if (minim < CostArc(g, i, j) && CostArc(g, i, j) != 0)
      {
        minim = CostArc(g, i, j);
        *s = i;
        *d = j;
      }
    }
  }
  return minim;
}

int grad_max_intrare(void *g)
{
  AGM matrice = (AGM)g;
  int max = 0;
  int nod = 0;
  for(int i = 0 ; i < matrice->n; i++)
  {
    int contor = 0;
    for(int j = 0 ; j < matrice->n ; j++)
    {
      if(matrice->x[matrice->n * j + i] > 0)
      {
        contor++;
      }

    }
    if(contor > max)
    {
      max = contor;
      nod = i;
    }
  }

  return nod + 1;
}

int NrNoduri(void* g)
{
    return ((AGM)g)->n;
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

