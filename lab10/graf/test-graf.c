/*--- test-graf.c ---*/
#include "graf.h"

void AfiM(void* g)
{ int i,j,k, n = NrNoduri(g);
  for (i = 1; i <= n; i++)
  { for (j = 1; j <= n; j++)
    { k = CostArc(g,i,j);
      if(k == ArcInex) printf("  - ");
      else printf("%3i ", k);
    }
    printf("\n");
  }
}

int main()
{
  void* g;

  if (CitGraf(&g) <= 0)
  { printf("-=- eroare la citire -=-\n"); return -1;}
  printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
  int rez = Grad_iesire(g, 3);
  printf("%d\n\n", rez);
  int sursa; 
  int dest;
  int max;
  max = ArcCostMax(g, &sursa, &dest);
  printf("\n\n");
  printf("%d %d %d \n\n\n", max , sursa , dest);
  AfiM(g);
  int *vecini = calloc(NrNoduri(g), sizeof(int));
  //Cyclu_util(g);

  rez = grad_max_intrare(g);
  printf("\n aste e maximul de intrare : %d\n", rez);
  /*-- apel functii definite --*/
  DistrG(&g);
  return 0;
}
