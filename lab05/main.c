#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int pid, prio;
} TPunct;

/* insereaza N elemente in coada c - elemente de tip TPunct
   cu valori intre v1 si v2 */
// int GenereazaCoadaPuncte(void* c, size_t N, int v1, int v2)
// { 
//   	int n = 0;
//   	TPunct p;

//   	srand(time(NULL));
//   	for(; N > 0; N--)
//   	{
//     	p.x = rand() % (v2-v1+1) + v1; 
  
// 		if (!IntrQ(c, &p)) 
// 			return n;
// 		n++;
//   	}
//   	return n;
// }

// /* insereaza N elemente in stiva s - elemente de tip TPunct
//    cu valori intre v1 si v2 */
// int GenereazaStivaPuncte(void* s, size_t N, int v1, int v2)
// { 
// 	int n = 0;
//   	TPunct p;

//   	srand(time(NULL));
//   	for(; N > 0; N--)
//   	{
//     	p.x = n; 
// 		if (!Push(s, &p)) 
// 			return n;
// 		n++;
//   	}
//   	return n;
// }

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPunct*)a).pid, (*(TPunct*)a).prio); 
	return 1;
}

int verficiare_stive(void *s, int k)
{
	int ae;
	int contor = 0;
	while(Pop(s, &ae))
	{
		if(ae > k)
			contor++;
	}
	return contor;
}

void *new_stack(void *c, int k, int *contor)
{
	void *s = InitS(sizeof(TPunct), MAX);
	int el;
	while(ExtrQ(c,&el))
	{
		if(el % k == 0)
		{
		Push(s,&el);
		(*contor)++;
		}
	}
	return s;
}

int create_stack_que(void *s, void **new_stack, void **new_que)
{
	*new_stack = InitS(sizeof(TPunct), MAX);
	*new_que = InitQ(sizeof(TPunct), MAX);
	int el;
	int contor = 0;
	int rez;
	while(Pop(s, &el))
	{
		if(contor % 2 == 0)
		{
			rez = Push(*new_stack,&el);
			if(rez == 0)
			return 0;
			
		}
		else
		{
			rez = IntrQ(*new_que, &el);
			if(rez == 0)
			return 0;
		}
		contor++;
	}

	return 1;

}

int operatii(char sir[])
{
	void *s;
	s = InitS(sizeof(TPunct), MAX);
	int contor = strlen(sir);
	while(contor >= 0)
	{
		if( '0' <= sir[contor] && sir[contor] <= '9')
		{
			int numar = sir[contor] - '0';
			Push(s, &numar);
			contor --;
		}
		else
		{
			int nr1 = 0;
			int nr2 = 0;
			Pop(s,&nr1);
			Pop(s,&nr2);
			int rez = 0;
			if(sir[contor] == '/')
			{
				rez = nr1 / nr2;
			}
			if(sir[contor] == '+')
			{
				rez = nr1 + nr2;
			}
			if(sir[contor] == '-')
			{
				rez = nr1 - nr2;
			}
			if(sir[contor] == '*')
			{
				rez = nr1 * nr2;
			}
			Push(s, &rez);
			contor --;

		}
	}

	int rezultat;
	Pop(s,&rezultat);
	return rezultat;	
}

void opr2()
{	
	void *q;
	q = InitQ(sizeof(TPunct), MAX);
	int numar1 = 0, numar2 = 0;
	void *aux = InitQ(sizeof(TPunct), MAX);
	while(scanf("%d %d", &numar1, &numar2) != EOF)
	{
		TPunct elemnt;
		TPunct compare;
		elemnt.pid = numar1;
		elemnt.prio = numar2;
		//printf("%d %d ", numar1, numar2);
		if(VidaQ(q))
		{
		IntrQ(q,&elemnt);
		}
		else
		{
			while(1)	
			{
				
			int rez = PrimQ(q, &compare);
			if(!rez) break;
			if(compare.prio <= elemnt.prio)
			{
			ExtrQ(q, &compare);
			IntrQ(aux, &compare);
			}
			else
			{
				break;
			}
			}
			IntrQ(aux, &elemnt);
			ConcatQ(aux,q);
			ConcatQ(q,aux);
			
		}
	}
	
	AfisareQ(q, AfiPct);

}

int main()
{ 
	void *c, *s;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPunct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPunct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	//lgc = GenereazaCoadaPuncte(c, 8, -5, 5);
  	//lgs = GenereazaStivaPuncte(s, 6, 8, 14);
	int k = 2;
	void *new_stack;
	void *new_que;
	opr2();
	// AfisareS(s, AfiPct);
	// int rez = create_stack_que(s, &new_stack, &new_que);
	// AfisareS(new_stack, AfiPct);
	// AfisareQ(new_que, AfiPct);
	// printf("%d ", rez);
	//printf("da");
	// char sir[50] = "+7*3+53";
	// int rez = operatii(sir);
	// printf("%d ", rez);
	//DistrS(&s);
  	//DistrQ(&c);
  	return 0;
}
