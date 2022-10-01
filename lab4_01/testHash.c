/*-- testHash.c  */
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>

typedef struct {
	char titlu[50];
	char autor[30];
	char editura[30];
} TCarte;

typedef struct 
{
	char nume[50];
	int varsta;
}TPers;


// int codHash(void * element)
// {
// 	TCarte * carte = (TCarte *) element;
// 	char * autor = carte->autor;
// 	return *autor - 'A';
// }

int codHash(void * element)
{
	TPers * carte = (TPers *) element;
	char * autor = carte->nume;
	return *autor - 'A';
}

// void afisareCarte(void * element)
// {
// 	TCarte * carte = (TCarte *) element;
// 	printf("%s - %s - %s\n", carte->autor, carte->titlu, carte->editura);
// }

void afisareCarte(void * element)
{
	TPers * pers = (TPers *) element;
	printf("%s - %d\n", pers->nume, pers->varsta);
}

// TLG citesteListaCarti(char * numeFisier) {
// 	FILE *f;
// 	char * line = NULL;
// 	size_t len = 0;
// 	TLG L = NULL;

// 	f = fopen(numeFisier, "rt");
// 	if (f == NULL)
// 		return NULL;

// 	while (getline(&line, &len, f) != -1) {
// 		char * autor = strtok(line, ":");
// 		char * titlu = strtok(NULL, ":");
// 		char * editura = strtok(NULL, ":");

// 		if (editura[strlen(editura) - 1] == '\n')
// 			editura[strlen(editura) - 1] = '\0';

// 		TCarte * carte = malloc(sizeof(TCarte));
// 		if (carte == NULL)
// 			return L;

// 		strcpy(carte->autor, autor);
// 		strcpy(carte->titlu, titlu);
// 		strcpy(carte->editura, editura);
// 		Ins_IncLG(&L, (void *) carte);
//     }
// 	fclose(f);
// 	return L;
// }

void daaa(TLG *al, void *pers)
{	
	TPers *persoana = (TPers*)pers;
	TLG l = *al;
	TLG ant = NULL;
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelulaG));
	aux->info = pers;
	for(; l != NULL;ant = l, ant = l, l = l->urm)
	{	
		TPers *persoana2 = (TPers*)l->info;
		if(persoana2->varsta < persoana->varsta)
		break;
		ant = l;
	}
	if(ant == NULL)
	{
		*al = aux;
		aux->urm = l;
	}
	else
	{
		ant->urm = aux;
		aux->urm = l;
	}

}

TLG citesteListaCarti(char * numeFisier) {
	FILE *f;
	char * line = NULL;
	size_t len = 0;
	TLG L = NULL;

	f = fopen(numeFisier, "rt");
	if (f == NULL)
		return NULL;

	while (getline(&line, &len, f) != -1) {
		char * nume = strtok(line, ":");
		char * varsta = strtok(NULL, ":");

		if (varsta[strlen(varsta) - 1] == '\n')
			varsta[strlen(varsta) - 1] = '\0';
		TPers * pers = malloc(sizeof(TPers));
		if (pers == NULL)
			return L;

		strcpy(pers->nume, nume);
		pers->varsta = atoi(varsta);
		daaa(&L, (void*)pers);
		//Ins_IncLG(&L, (void *) pers);
    }
	fclose(f);
	return L;
}

// int cmpCarte(void * e1, void * e2)
// {
// 	TCarte * carte1 = (TCarte *) e1;
// 	TCarte * carte2 = (TCarte *) e2;

// 	if (strcmp(carte1->titlu, carte2->titlu) != 0)
// 		return 0;

// 	if (strcmp(carte1->autor, carte2->autor) != 0)
// 		return 0;

// 	if (strcmp(carte1->editura, carte2->editura) != 0)
// 		return 0;

// 	return 1;
// }

int cmpCarte(void * e1, void * e2)
{
	TPers * pers1 = (TPers *) e1;
	TPers * pers2 = (TPers *) e2;

	if(strcmp(pers1->nume ,pers2->nume) !=0)
	return 0;

	return 1;
}

TH * GenerareHash(TLG listaCarti)
{
    TH *h = NULL;
	TLG p;
    TPers * pers;
	int rez;

	/* calcul dimensiuni maxime pt tabela hash */
	size_t M = ('Z'-'A');

	/* initializare tabela hash */
	h = (TH *) InitTH(M, codHash);
	if(h == NULL)
		return NULL;

	for(p = listaCarti; p != NULL; p = p->urm) {
        pers= (TPers *) malloc(sizeof(TPers));
        if(pers == NULL)
						return h;

        memcpy(pers, p->info, sizeof(TPers));
		rez = InsTH(h, pers, cmpCarte);
        if(!rez) {
						free(pers);
						return h;
		}
	}

	return h;
}


int main()
{
	/* Citeste o lista de carti din fisier */
	TLG listaCarti = citesteListaCarti("carti.txt");
	if (listaCarti == NULL) {
		printf("Lista nu a putut fi generata\n");
        return 0;
	}

	printf("=========== LISTA PERS ===========\n");
	Afisare(&listaCarti, afisareCarte);

	TH * h = NULL;
	h = GenerareHash(listaCarti);
	if (h == NULL) {
		printf("Tabela hash nu a putut fi generata\n");
        return 0;
	}

	printf("\n\n=========== TABELA HASH ===========\n");
	AfiTH(h, afisareCarte);


  	DistrugeLG(&listaCarti, free);
	DistrTH(&h, free);
  	return 0;
}
