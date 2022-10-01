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

int codHash(void * element)
{
	TCarte * carte = (TCarte *) element;
	char * autor = carte->autor;
	return *autor - 'A';
}

void afisareCarte(void * element)
{
	TCarte * carte = (TCarte *) element;
	printf("%s - %s - %s\n", carte->autor, carte->titlu, carte->editura);
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
		char * autor = strtok(line, ":");
		char * titlu = strtok(NULL, ":");
		char * editura = strtok(NULL, ":");

		if (editura[strlen(editura) - 1] == '\n')
			editura[strlen(editura) - 1] = '\0';

		TCarte * carte = malloc(sizeof(TCarte));
		if (carte == NULL)
			return L;

		strcpy(carte->autor, autor);
		strcpy(carte->titlu, titlu);
		strcpy(carte->editura, editura);
		Ins_IncLG(&L, (void *) carte);
    }
	fclose(f);
	return L;
}

int cmpCarte(void * e1, void * e2)
{
	TCarte * carte1 = (TCarte *) e1;
	TCarte * carte2 = (TCarte *) e2;

	if (strcmp(carte1->titlu, carte2->titlu) != 0)
		return 0;

	if (strcmp(carte1->autor, carte2->autor) != 0)
		return 0;

	if (strcmp(carte1->editura, carte2->editura) != 0)
		return 0;

	return 1;
}

TH * GenerareHash(TLG listaCarti)
{
    TH *h = NULL;
	TLG p;
    TCarte * carte;
	int rez;

	/* calcul dimensiuni maxime pt tabela hash */
	size_t M = ('Z'-'A');

	/* initializare tabela hash */
	h = (TH *) InitTH(M, codHash);
	if(h == NULL)
		return NULL;

	for(p = listaCarti; p != NULL; p = p->urm) {
        carte = (TCarte *) malloc(sizeof(TCarte));
        if(carte == NULL)
						return h;

        memcpy(carte, p->info, sizeof(TCarte));
		rez = InsTH(h, carte, cmpCarte);
        if(!rez) {
						free(carte);
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

	printf("=========== LISTA CARTI ===========\n");
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
