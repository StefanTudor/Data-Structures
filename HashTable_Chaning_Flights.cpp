#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Zbor
{
	char* destinatie;
	int pasageri;
};

struct Nod
{
	Nod* next;
	Zbor info;
};

struct HashTable
{
	Nod* *lista;
	int dim;
};

Zbor initZbor(const char* dest, int pas)
{
	Zbor a;
	a.destinatie = (char*)malloc(sizeof(char) * (strlen(dest) + 1));
	strcpy(a.destinatie, dest);
	a.pasageri = pas;
	return a;
}

Nod* initNod(Nod* next, Zbor info)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = info;
	nod->next = next;
	return nod;
}

HashTable initHashTable(int dim)
{
	HashTable h;
	h.dim = dim;
	h.lista = (Nod**)malloc(sizeof(Nod) * h.dim);
	for (int i = 0; i < h.dim; i++)
	{
		h.lista[i] = NULL;
	}
	return h;
}

int hashFunction(HashTable h, Zbor z)
{
	int hashCode = 0;
	for (int i = 0; i < strlen(z.destinatie); i++)
	{
		hashCode += z.destinatie[i];
	}
	return hashCode % h.dim;
}

Nod* inserareNod(Nod* lista, Zbor z)
{
	if (lista)
	{
		Nod* nou = initNod(lista, z);
		return nou;
	}
	else
	{
		return initNod(NULL, z);
	}
}

void inserareHashTable(HashTable h, Zbor z)
{
	int hashCode = hashFunction(h, z);
	h.lista[hashCode] = inserareNod(h.lista[hashCode], z);
}

void afisareZbor(Zbor a)
{
	printf("\nDestinatie: %s\nNumar pasageri: %d", a.destinatie, a.pasageri);
}

void afisareLista(Nod* lista)
{
	Nod* temp = lista;
	while (temp)
	{
		afisareZbor(temp->info);
		temp = temp->next;
	}
}

void afisareHashTable(HashTable h)
{
	for (int i = 0; i < h.dim; i++)
	{
		printf("\n------------------Pozitia %d--------------------", i);
		if (h.lista[i] != NULL)
		{
			afisareLista(h.lista[i]);
		}
		else
		{
			printf("\nLista este goala!");
		}
	}
}

Zbor extragereZbor(HashTable h, const char* destinatie)
{
	int hashCode = hashFunction(h, initZbor(destinatie, 0));
	Nod* lista = h.lista[hashCode];

	if(lista)
	{
		if (strcmp(lista->info.destinatie, destinatie) == 0)
		{
			if (lista->next == NULL)
			{
				Zbor tempZbor = initZbor(lista->info.destinatie, lista->info.pasageri);
				h.lista[hashCode] = NULL;
				return tempZbor;
			}
			else
			{
				Zbor tempZbor = initZbor(lista->info.destinatie, lista->info.pasageri);
				h.lista[hashCode] = h.lista[hashCode]->next;
				free(lista);
				return tempZbor;
			}
		}

		while (lista->next && strcmp(lista->next->info.destinatie, destinatie) != 0)
		{
			lista = lista->next;
		}
		if (lista->next)
		{

		}

	}
}

void main()
{
	Zbor z1 = initZbor("Castellon", 220);
	Zbor z2 = initZbor("Bucuresti", 320);
	Zbor z3 = initZbor("New York", 250);
	Zbor z4 = initZbor("Berlin", 230);
	Zbor z5 = initZbor("Bruxelles", 150);
	Zbor z6 = initZbor("Vienna", 290);
	Zbor z7 = initZbor("Los Angeles", 300);

	HashTable h = initHashTable(5);
	inserareHashTable(h, z1);
	inserareHashTable(h, z2);
	inserareHashTable(h, z3);
	inserareHashTable(h, z4);
	inserareHashTable(h, z5);
	inserareHashTable(h, z6);
	inserareHashTable(h, z7);

	afisareHashTable(h);

	printf("\n\n");
	Zbor z8 = extragereZbor(h, "Castellon");
	afisareZbor(z8);
	printf("\n\n");
	afisareHashTable(h);
	
}