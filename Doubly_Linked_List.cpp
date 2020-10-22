#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Produs
{
	char* nume;
	float pret;
};

struct Nod
{
	Produs info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla
{
	Nod* prim;
	Nod* ultim;
};

Produs creareProdus(const char* nume, float pret)
{
	Produs p;
	p.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.pret = pret;
	return p;
}

Nod* creareNod(Produs p, Nod* prev, Nod* next)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = p;
	nodNou->prev = prev;
	nodNou->next = next;
	return nodNou;
}

ListaDubla inserareInceput(ListaDubla lista, Produs p)
{
	Nod* nodNou = creareNod(p, NULL, NULL);
	if (lista.prim)
	{
		lista.prim->prev = nodNou;
		nodNou->next = lista.prim;
		lista.prim = nodNou;
	}
	else
	{
		lista.prim = nodNou;
		lista.ultim = nodNou;
	}
	return lista;
}

ListaDubla inserareSfarsit(ListaDubla lista, Produs p)
{
	Nod* nodNou = creareNod(p, NULL, NULL);
	if (lista.ultim)
	{
		nodNou->prev = lista.ultim;
		lista.ultim->next = nodNou;
		lista.ultim = nodNou;
	}
	else
	{
		lista.prim = nodNou;
		lista.ultim = nodNou;
	}
	return lista;
}

ListaDubla inserareAscendenta(ListaDubla& lista, Produs p) 
{
	if (lista.prim)
	{
		Nod* temp = lista.prim;
		if (temp->info.pret > p.pret)
		{
			lista = inserareInceput(lista, p);
			return lista;
		}

		while (temp->next && temp->next->info.pret < p.pret)
		{
			temp = temp->next;
		}

		if (temp->next == NULL)
		{
			lista = inserareSfarsit(lista, p);
			return lista;
		}
		else
		{
			Nod* nodNou = creareNod(p,temp, temp->next);
			temp->next->prev = nodNou;
			temp->next = nodNou;
			return lista;
		}
	}
	else
	{
		Nod* nodNou = creareNod(p, NULL, NULL);
		lista.prim = nodNou;
		lista.ultim = nodNou;
		return lista;
	}
}

void afisareProdus(Produs p)
{
	printf("Produsul %s are pretul de %3.2f RON.\n", p.nume, p.pret);
}

void afisareLista(ListaDubla lista)
{
	while (lista.prim)
	{
		afisareProdus(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void main()
{
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	
	lista = inserareAscendenta(lista, creareProdus("Tastatura", 150));
	lista = inserareAscendenta(lista, creareProdus("Tastatura", 3));
	
	
	afisareLista(lista);
}