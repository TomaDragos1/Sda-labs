/*-- testHash.c  */
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>

typedef struct
{
	int number_letters;
	TLG head_list;
} TLetters;

typedef struct
{
	char name[50];
	int frequency;
} TFrequncy;

int codHash(void *element)
{
	char *name = (char *)element;
	if ('A' <= name[0] && name[0] <= 'Z')
		return *name - 'A';
	return *name - 'a';
}

void afisare_cel_number_letters(void *element)
{
	TLetters *el = (TLetters *)element;
	printf("(%d:", el->number_letters);
}
void afisare_element_second_list(void *element)
{
	TLetters *el = (TLetters *)element;
	TLG pars = el->head_list;
	TLG next = pars;
	int contor = 1;
	for (; pars != NULL; pars = pars->urm)
	{
		TFrequncy *info1 = (TFrequncy *)(pars->info);
		next = pars->urm;
		if (next == NULL)
		{
			printf("%s/%d", info1->name, info1->frequency);
		}
		else
			printf("%s/%d, ", info1->name, info1->frequency);
	}
	printf(")");
}

TLG aloc_cel_second_list(void *name)
{
	TLG pars = NULL;
	pars = (TLG)malloc(sizeof(TCelulaG));
	TFrequncy *crt_info = (TFrequncy *)malloc(sizeof(TFrequncy));
	crt_info->frequency = 1;
	strcpy(crt_info->name, (char *)name);
	pars->info = crt_info;
	pars->urm = NULL;
	return pars;
}

int compare_two_cels_second(void *el1, void *el2)
{
	TFrequncy *element1 = (TFrequncy *)el1;
	char *element2 = (char *)el2;
	int nr = strlen(element2);
	if (strcmp(element1->name, element2) == 0)
	{
		element1->frequency++;
		return 1;
	}
	return 0;
}

int cmp_number_letters(void *el1, void *el2)
{
	TLetters *element1 = (TLetters *)el1;
	char *name = (char *)el2;
	int number_let = strlen(el2);
	if (element1->number_letters == number_let)
	{
		return 1;
	}
	else
		return 0;
}
void ord_frequence(TLG *al, TLG element_search)
{
	TLG l = *al;
	TLG ant = NULL;
	TFrequncy *el_search = (TFrequncy *)(element_search->info);
	for (; l != NULL; ant = l, l = l->urm)
	{
		TFrequncy *el_crt = (TFrequncy *)(l->info);
		int val_cmp = strcmp(el_search->name, el_crt->name);
		if (el_search->frequency == el_crt->frequency && val_cmp < 0)
		{
			break;
		}
		else if (el_search->frequency > el_crt->frequency)
		{
			break;
		}
	}
	if (ant == NULL)
	{
		*al = element_search;
		element_search->urm = l;
	}
	else
	{
		ant->urm = element_search;
		element_search->urm = l;
	}
}

void insert_second_list(TLG *el, void *name)
{
	TLetters *info = (TLetters *)((*el)->info);
	int ok = 0;
	if (info->head_list == NULL)
	{
		TLG pars = aloc_cel_second_list(name);
		info->head_list = pars;
	}
	else
	{
		TLG aux = info->head_list;
		TLG ant = NULL;
		for (; aux != NULL && ok == 0; ant = aux, aux = (aux)->urm)
		{
			if (compare_two_cels_second((aux)->info, name) == 1)
			{
				ok = 1;
				if (ant != NULL)
				{
					ant->urm = aux->urm;
					aux->urm = NULL;
				}
				else
				{
					info->head_list = aux->urm;
					aux->urm = NULL;
				}
				ord_frequence(&info->head_list, aux);
			}
		}
		if (ok == 0)
		{
			TLG add = aloc_cel_second_list(name);
			ord_frequence(&info->head_list, add);
		}
	}
}

int cmp_first_list(void *el1, void *el2)
{
	TLetters *element1 = (TLetters *)el1;
	TLetters *element2 = (TLetters *)el2;
	if (element1->number_letters < element2->number_letters)
		return 1;
	return 0;
}

int verif_cel(void *el_crt, int frequence)
{
	TLetters *element = (TLetters *)el_crt;
	TLG parcurgere = element->head_list;
	int contor = 0;
	for (; parcurgere != NULL; parcurgere = parcurgere->urm)
	{
		TFrequncy *info = (TFrequncy *)(parcurgere->info);
		if (info->frequency <= frequence)
			contor++;
	}
	if (contor == 0)
		return 0;
	return 1;
}
void afisare_first_task(void *el_crt, int frequnece)
{
	TLetters *element = (TLetters *)el_crt;
	TLG parcurgere = element->head_list;
	TLG next = parcurgere;
	printf("(%d: ", element->number_letters);
	for (; parcurgere != NULL; parcurgere = parcurgere->urm)
	{
		TFrequncy *info = (TFrequncy *)(parcurgere->info);
		next = parcurgere->urm;
		if (info->frequency <= frequnece && next == NULL)
		{
			printf("%s/%d", info->name, info->frequency);
		}
		else if (info->frequency <= frequnece && next != NULL)
		{
			printf("%s/%d, ", info->name, info->frequency);
		}
	}
	printf(")");
}

int list_verif(TLG first_list, int frequence)
{
	TLG l = first_list;
	int contor = 0;
	for (; l != NULL; l = l->urm)
	{
		TLetters *info1 = (TLetters *)(l->info);
		TLG par_sublist = info1->head_list;
		for (; par_sublist != NULL; par_sublist = par_sublist->urm)
		{
			TFrequncy *info2 = (TFrequncy *)(par_sublist->info);
			if (info2->frequency <= frequence)
				contor++;
		}
	}
	if (contor == 0)
		return 0;
	return 1;
}

void afisare2(TLG el)
{
	TLetters *info = (TLetters *)(el->info);
	TLG l = info->head_list;
	TLG next = l;
	//printf("(");
	for (; l != NULL; l = l->urm)
	{
		TFrequncy *info2 = (TFrequncy *)(l->info);
		next = l->urm;
		if (next == NULL)
		{
			printf("%s/%d", info2->name, info2->frequency);
		}
		else
		{
			printf("%s/%d, ", info2->name, info2->frequency);
		}
	}
	printf(")");
}

TLG verif_case_2(TLG list, int nr_let)
{
	TLG l = list;
	for (; l != NULL; l = l->urm)
	{
		TLetters *info = (TLetters *)(l->info);
		if (info->number_letters == nr_let)
			return l;
	}
	return NULL;
}
void eliberare_second_list(TLG *element)
{
	TLetters *info1 = (TLetters *)((*element)->info);
	TLG l = info1->head_list;
	TLG aux = NULL;
	for (; l != NULL;)
	{
		aux = l;
		l = l->urm;
		TFrequncy *info2 = (TFrequncy *)(aux->info);
		free(aux->info);
		free(aux);
	}
	info1->head_list = NULL;
}

TLG aloc1(void *elem)
{
	char *name = (char *)elem;
	TLG element = (TLG)malloc(sizeof(TCelulaG));
	TLetters *info = (TLetters *)malloc(sizeof(TLetters));
	info->number_letters = strlen(name);
	info->head_list = NULL;
	element->info = info;
	return element;
}
TH *GenerareHash(FILE *f)
{
	TH *h = NULL;
	size_t M = ('z' - 'a') + 1;
	size_t len = 0;
	TLG p;
	int rez;
	h = (TH *)InitTH(M, codHash);
	if (h == NULL)
		return NULL;
	char line[1000];
	while (fgets(line, 1000, f))
	{
		char *word = strtok(line, " ,.\n\r");
		if (strcmp(word, "insert") == 0)
		{
			word = strtok(NULL, " ,.\n\r");
			while (word != NULL)
			{
				if (strlen(word) >= 3)
				{
					rez = InsTH(h, cmp_number_letters, word, insert_second_list, cmp_first_list, aloc1);
					if (rez == 0)
						return NULL;
				}
				word = strtok(NULL, " ,.\n\r");
			}
		}
		else if (strcmp(word, "print") == 0)
		{
			char *first_info;
			char *second_info;
			first_info = strtok(NULL, " ,.\n\r");
			second_info = strtok(NULL, " ,.\n\r");
			if (first_info == NULL && second_info == NULL)
			{
				AfiTH(h, afisare_cel_number_letters, afisare_element_second_list);
			}
			else if (first_info != NULL && second_info == NULL)
			{
				int frequnce = atoi(first_info);
				AfiTH_case1(h, afisare_first_task, frequnce, verif_cel, list_verif);
			}
			else if (first_info != NULL && second_info != NULL)
			{
				int nr_let = atoi(second_info);
				//printf("\n%s %d\n", first_info, nr_let);
				AfiTH_case2(h, first_info, nr_let, verif_case_2, afisare2);
			}
		}
	}
	//free(crt_word_cel);
	fclose(f);
	return h;
}
int main(int argc, char *argv[])
{
	TH *h = NULL;
	FILE *input;
	input = fopen(argv[1], "r");
	h = GenerareHash(input);
	if (h == NULL)
	{
		printf("Tabela hash nu a putut fi generata\n");
		return 0;
	}
	DistrTH(&h, eliberare_second_list);
	free(h);
	return 0;
}
