/*  functii-tabHash.c - functii tabela hash */


#include "thash.h"

TH* InitTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}


void DistrTH(TH** ah, TFdezaloc elib_elem)
{
    TLG *p, el, aux;
    int contor = 0;
    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) { // fiecare hash
        /* daca exista elemente corespunzatoare acestui hash
         * eliberam info din celula si apoi eliberam celula */
        //if(p!= NULL)
        {
        for(el = *p; el != NULL; ) { /// in fiecare lista
            aux = el;
            el = el->urm;
            elib_elem(&aux);
            free(aux->info);
            free(aux);
        }
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void AfiTH(TH* ah,TF afi_elem, TFsecond afi_elem_second_list)
{
    TLG p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("pos %d: ",i);
            for(el = p; el != NULL; el = el->urm)
                {
                    afi_elem(el->info);
                    afi_elem_second_list(el->info);
                }
            printf("\n");
        }
    }
}
void AfiTH_case1(TH* ah,TF_first_task afisare_first_task, int frequence, TFverif verif_cel, TFlist_ver list_ver)
{
    TLG p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        int ok = 0;
        p = ah->v[i];
        if(p) {
            if(list_ver(p, frequence) == 0)
            ok = 1;
            if(ok == 0)
            { 
            printf("pos%d: ",i);
            for(el = p; el != NULL; el = el->urm)
                {
                    if(verif_cel(el->info, frequence) == 1)
                    afisare_first_task(el->info, frequence);
                }
            printf("\n");
            }
        }
    }
}

void AfiTH_case2(TH* ah, char *frst_let, int number_let,Tverif2 verif2, TAfis2 afisare2)
{
    int cod = ah->fh(frst_let);
    TLG p = ah->v[cod];
    TLG el = NULL;
    TLG cel_search = verif2(p, number_let);
    if(cel_search != NULL)
    {
        printf("(%d:", number_let);
        afisare2(cel_search);
        printf("\n");
    }
}

/* daca elementul exista functia intoarce 0
 *altfel se incearca inserarea elementului si se intoarce rezultatul inserarii */
int InsTH(TH*a, TFCmp fcmp, void *name, TFinsertsec afinsert, TFcompare firs_list_cmp, TFaloc1 aloc_1)
{
    int cod = a->fh(name);
    //printf(" Asta este codul :%d\n ", cod);
    TLG el;
    for(el = a->v[cod]; el != NULL; el = el->urm) {
        if (fcmp(el->info, name) == 1)
        {   
            afinsert(&el, name);
            return 1;
        }
    }
    TLG rez = Ins_IncLG(a->v+cod, name, firs_list_cmp, aloc_1); /* reminder: a->v+cod <=> &a->v[cod] */
    if(rez == NULL) return 0;
    afinsert(&rez, name);
    return 1;
}
