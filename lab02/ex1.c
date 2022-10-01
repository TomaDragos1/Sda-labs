#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula
{ int info;
  struct celula * urm;
  int verif;
} TCelula, *TLista;

TLista AlocCelula(int e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
    aux->verif = 0;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
       /* afiseaza valorile elementelor din lista */
{
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
    printf("%d ", L->info);              /* afiseaza informatie */
  printf("]");                               /* marcheaza sfarsit lista */
}

void DistrugeL(TLista* aL)
{
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
}


void afisare_list(TLista l , int el)
{
    int contor = 1;
    for(; l != NULL; l = l->urm)
    {
        if(l->urm!=NULL && l->info % el == 0 && l->urm->info % el == 0 && contor % 2 == 1)
        {   
            int aux = contor;
            printf("%d %d : (%d %d) ", aux++ , aux, l->info, l->urm->info);

        }
        contor++;

    }
}

TLista CitireL(int *lg)
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )
  {
    aux = AlocCelula(x);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
    (*lg)++;
  }

  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int compar_lista(TLista l1, TLista l2)
{   
    
    for(;l1 != NULL; l1 = l1->urm)
    {
        TLista aux = l2;
        for(;aux != NULL; aux = aux->urm)
        {
            if(aux->info == l1->info && aux->verif == 0)
            {
                aux -> verif = 1;
                break;
            }

        }
        
    }
    for(;l2 != NULL;l2 = l2->urm)
    {
        if(l2->verif == 0)
        return 1;
    }
    return 0;

}

void lista_pereche(TLista *Al, int *p1, int *p2)
{
  TLista p, n,l;
  l = *Al;
  p = l;
  l = l->urm;
  n = l->urm;
  p->urm = NULL;
  while (1)
  {
    l->urm = p;
    p = l;
    l = n;
    n = n->urm;
    if(n == NULL){
      l->urm = p;
      break;
      }
  }
  *Al = l;
}
TLista copie(TLista l, int a, int b, int *len)
{
    TLista aranjat = NULL;
    TLista ant = NULL, aux = NULL;
    for(aux = l; aux != NULL; aux = aux->urm)
    {
        if(aux->info > b  || aux->info < a)
        {   
            (*len)++;
            TLista new_element = AlocCelula(aux->info);
            if(aranjat == NULL)
            {   
                aranjat = new_element;
            }else
            {   
                ant->urm = new_element;
                
            }
            ant = new_element;
        }
    }
    return aranjat;


}
TLista move(TLista *l, int k)
{
    TLista lm = *l;
    *l =  (*l)->urm;
    TLista antl = (*l);
    TLista antlm = lm;
    TLista aux = (*l)->urm;
    int contor = 2;
    for(; aux!=NULL ; aux = aux->urm)
    {
        if(contor % k == 0)
        {
           antlm->urm = aux;
           antlm = antlm ->urm;
        }
        else{
            antl->urm = aux;
            antl = antl->urm;

        }
        contor++;
    }
    antlm->urm = NULL;
    antl->urm = NULL;
    return lm;
}



int main ()
{ TLista x = NULL, x1 = NULL, x2 = NULL;     /* Lista prelucrata */
  int lx;           /* lungime lista */

  for (;;)
  {
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    x = CitireL(&lx);
   if(!x) continue;
   AfisareL(x);
    int a = 4, b = 7, len = 0;
   TLista rezultat = copie(x, a, b, &len);
   AfisareL(rezultat);
   TLista t = move(&x, 6);
   AfisareL(t);
   AfisareL(x);
   DistrugeL(&x);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}