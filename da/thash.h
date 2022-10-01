#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void *);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);
typedef void (TFsecond)(void*); /*afisare a doua lista*/
typedef void (*TFinsertsec)(TLG* , void *);
typedef int (*TFcompare)(void *, void *);
typedef void (*TF_first_task)(void*, int);
typedef int (*TFverif)(void *, int);
typedef int (*TFlist_ver)(TLG, int);
typedef void(*TAfis2)(TLG);
typedef TLG (*Tverif2)(TLG, int);
typedef void(TFdezaloc)(TLG*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v; // lista de hash in care pui pui prima litera
} TH;

/* functii tabela hash */
TH* InitTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TFdezaloc elib_el);
void AfiTH(TH*a, TF afiEl, TFsecond afiEl2);
int InsTH(TH*a, void*ae, TFCmp f, void *name, TFinsertsec afinsert, TFcompare irs_list_cmp);
void AfiTH_case1(TH*a, TF_first_task afisare_first_task, int frequence, TFverif verif_cel, TFlist_ver list_ver);
void AfiTH_case2(TH*a, char* frst_let, int nmbr_let,Tverif2 verif2, TAfis2 afisare2);

#endif