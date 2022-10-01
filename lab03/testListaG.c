#include <ctype.h>
#include <stdio.h>
#include "tlg.h"

#define MAX 2/* număr maxim de elemente din lista */

// TLG CitireL_Int()     /* construieste lista cu elemente întregi - MAX elemente */
// { TLG L = NULL, u, aux;
//   int *elem, nr = 0;

//   printf("\nConstructie lista generică cu %i elemente întregi\n", MAX);
//   for(nr = 0; nr < MAX; nr++)
//   {
//     int* elem = (int*)malloc(sizeof(int));
//     if(!elem) return L;

//     scanf("%i", elem);

//     aux = Aloc_CelulaG(elem);           /* incearca inserarea valorii citite */
//     if(!aux) {	/* alocare esuata => sfarsit citire */
// 	free(elem); 
// 	return L;
//     }       
       
//     if(L == NULL) L = aux;
//     else u->urm = aux;
//     u = aux;
//   }
  
//   return L;                     /* intoarce lista rezultat */
// }

TCD aloc_cd()
{   
    TCD cd_new = (TCD)malloc(sizeof(cd));
    char buffer[30];
    scanf("%s", buffer);
    cd_new->nume = (char*)malloc(strlen(buffer));
    strcpy(cd_new->nume, buffer);
    scanf("%d", &cd_new->nr_interpreti);
    cd_new->interpreti = (char**)malloc(cd_new->nr_interpreti * sizeof(char*));
    for(int i = 0 ; i < cd_new->nr_interpreti; i++)
    {
        scanf("%s", buffer);
        cd_new->interpreti[i] = (char*)malloc(strlen(buffer));
        strcpy(cd_new->interpreti[i], buffer);
    }
    scanf("%d", &cd_new->an);
    return cd_new;

}

TLG CitireL_Int()     /* construieste lista cu elemente întregi - MAX elemente */
{ TLG L = NULL, u, aux;
  int *elem, nr = 0;

  printf("\nConstructie lista generică cu %i elemente întregi\n", MAX);
  for(nr = 0; nr < MAX; nr++)
  {
    TCD cd = NULL;
    cd = aloc_cd();
    //printf("%d ", cd->an);
    aux = Aloc_CelulaG(cd);           /* incearca inserarea valorii citite */
    if(!aux) {	/* alocare esuata => sfarsit citire */
	free(elem); 
	return L;
    }       
       
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
  }
  
  return L;                     /* intoarce lista rezultat */
}

/*void afi_int(void* el)
{
	printf("%i ", *(int*)el);
}*/

void afi_cd(void *el)
{      
    printf("%s ", ((TCD)el)->nume);
    printf("%d ", ((TCD)el)->nr_interpreti);
    for(int i = 0 ; i < ((TCD)el)->nr_interpreti; i++)
    {
        printf("%s ", ((TCD)el)->interpreti[i]);
    }
    printf("%d ", ((TCD)el)->an);
}

int chech(void *element)
{
    if(*(int*)element% 2 == 0)return 1;
    else return 0;
}

int nr_conditie(TLG lista, int (*check)(void*))
{
    TLG p = NULL;
    int suma = 0;
    for( p = lista ; p!=NULL ; p = p->urm)
    {
        suma+=chech(p->info);
    }
    return suma;
}

int verif_an(int an,int an_curent)
{   
    if(an_curent == an) return 1;
    else return 0;
}

void distruge_cd(void *el)
{
    TCD cd = ((TCD)el);
    free(((TCD)el)->nume);
    for(int i = 0 ; i < ((TCD)el)->nr_interpreti; i++)
    {
        free(((TCD)el)->interpreti[i]);
    }
    free(((TCD)el)->interpreti);
    //free(((TCD)el)->nr_interpreti);
    //free(((TCD)el)->an);
}

void distruge_element(TLG p, void (distruge_cd(void*)))
{
    distruge_cd(p->info);
    free(p);
}

void elimin(TLG *list, int anu, int(*verif_an)(int, int))
{
    TLG p = NULL;
    TLG ant = NULL;
    p = *list;
    for(ant = NULL;p!=NULL ;ant = p,p = p->urm)
    {   
        TCD cd = (TCD)p->info;
        if(verif_an(cd->an, anu))
        {
           if(ant == NULL)
           {
               *list = p->urm;
               distruge_element(p, distruge_cd);
               p = *list;
           }
           else
            {
            ant->urm = p->urm;
            distruge_element(p, distruge_cd);
            p = ant;
            }
        }
    }
    /*while(p!=NULL)
    {
        TCD cd = (TCD)p->info;
        if(verif_an(cd->an, anu))
        {
            aux = p->urm;
            DistrugeLG(&p, distruge_cd);
            p = aux;
        }
        else
            p = p->urm;
    }*/

}

int main ()
{ 
  TLG L = NULL;     
  
  L = CitireL_Int();  /* construiește lista generica cu elemente întregi */
  //int nr = nr_conditie(L,chech);
  int an = 1990;
  elimin(&L, an, verif_an);
  AfisareLG(L, afi_cd);
  //printf("%d\n", nr);
  /* apeluri functii implementate */


  DistrugeLG(&L, free);
}