#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; 	/* tipurile Celula, Lista generice */

typedef struct 
{
    char *nume;
    int nr_interpreti;
    char **interpreti;
    int an;
}cd,*TCD;

/* functii lista generica */
TLG Aloc_CelulaG(void* x);

int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/

void DistrugeLG(TLG* aL, void (*fe)(void*)); /* distruge lista */

/* afiseaza elementele din lista, folosind o functie de Afișare element specific*/
void AfisareLG(TLG, void (*afi_el)(void*));

#endif