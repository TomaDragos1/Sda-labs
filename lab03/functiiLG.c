#include "tlg.h"

TLG Aloc_CelulaG(void* x)
{
	TLG aux;
  	aux = (TLG)malloc(sizeof(TCelulaG));
   	if(!aux) return NULL;
   	
	aux->info = x;
	aux->urm = NULL;
	return aux;
}

int Ins_IncLG(TLG* aL, void* ae)
{
	TLG aux = Aloc_CelulaG(ae);
	if(!aux)
	    return 0;

	aux->urm = *aL;
	*aL = aux;

	return 1;
}

void DistrugeLG(TLG* aL, void (*free_elem)(void*)) /* distruge lista */
{
	TLG aux;
	while(*aL != NULL)
    	{
        		aux = *aL;     /* adresa celulei eliminate */
        		if (!aux)
            		return;

        		free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        		*aL = aux->urm;    /* deconecteaza celula din lista */
        		free(aux);   /* elibereaza spatiul ocupat de celula */
    	}
}


void AfisareLG(TLG L, void (*afiEL)(void*))
{
        if(!L) {
           printf("Lista vida\n");
           return;
        }

	printf("Lista: [");
	for(; L; L = L->urm) 
		afiEL(L->info);
    
	printf("]\n");
}