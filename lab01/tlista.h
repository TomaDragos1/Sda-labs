#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef LISTA_SIMPLU_INLANTUITA
#define LISTA_SIMPLU_INLANTUITA

typedef struct celula
{ int info;
  struct celula * urm;
} TCelula, TLista; 

#define VidaL(L) ((L) == NULL)

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (TLista*);       /* elimina toate celulele din lista */

void AfisareL (TLista L);

#endif