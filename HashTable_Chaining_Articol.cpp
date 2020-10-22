#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Articol
{
	int id;
	char* titlu;
	char* categorie;
	int nrPag;
	int nrAutori;
	char** autori;
};

struct Nod
{
	Articol info;
	Nod* next;
};

struct HashTable
{
	Nod* *lista;
	int dim;
};

Articol initArticol(int id, const char* titlu, const char* categorie, int nrPag, int nrAutori, const char** autori)
{
	Articol a;
	a.id = id;
	a.titlu = (char*)malloc(sizeof(char)*(strlen(titlu) + 1));
	strcpy(a.titlu, titlu);
	a.categorie = (char*)malloc(sizeof(char)*(strlen(categorie) + 1));
	strcpy(a.categorie, categorie);
	a.nrPag = nrPag;
	a.nrAutori = nrAutori;
	a.autori = (char**)malloc(sizeof(char*) * nrAutori);
	for (int i = 0; i < nrAutori; i++)
	{
		a.autori[i] = (char*)malloc(sizeof(char)*(strlen(autori[i])+1));
		strcpy(a.autori[i], autori[i]);
	}
	return a;
}

Nod* initNod(Nod* lista, Articol a)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = a;
	nodNou->next = lista;
	return nodNou;
}

Nod* inserareNod(Nod* lista, Articol a)
{
	if (lista)
	{
		Nod* nodNou = initNod(lista, a);
		return nodNou;
	}
	else
	{
		Nod* nodNou = initNod(NULL, a);
	}
}

HashTable initHashTable(int dim)
{
	HashTable h;
	h.dim = dim; 
	h.lista = (Nod**)malloc(sizeof(Nod*) * dim); //atent
	for (int i = 0; i < dim; i++)
	{
		h.lista[i] = NULL;
	}
	return h;
}

int hashFunction(HashTable h, Articol a)
{
	int hashCode = 0;
	for (int i = 0; i < strlen(a.categorie); i++)
	{
		hashCode += a.categorie[i];
	}
	return hashCode % h.dim;
}

void inserareHashTable(HashTable h, Articol a)
{
	int hashCode = hashFunction(h, a);
	h.lista[hashCode] = inserareNod(h.lista[hashCode], a);
}

void afisareArticol(Articol a)
{
	printf("\nID: %d\nTitlu: %s\nCategorie: %s\nNr. pagini: %d\nNr. autori: %d\nAutori: ",a.id,a.titlu,a.categorie,a.nrPag,a.nrAutori);
	for (int i = 0; i < a.nrAutori; i++)
	{
		printf("%s", a.autori[i]);
		if (i < a.nrAutori - 1) { printf(", "); }
	}
	printf("\n");
}

void afisareHashTable(HashTable h)
{
	for (int i = 0; i < h.dim; i++)
	{
		printf("\n-----------------Pozitia %d----------------", i);
		Nod* temp = h.lista[i];
		while (temp)
		{
			afisareArticol(temp->info);
			temp = temp->next;
		}
	}
}

void afisareLista(Nod* lista)
{
	Nod* temp = lista;
	while (temp)
	{
		afisareArticol(temp->info);
		temp = temp->next;
	}
}

int totalAutoriLista(Nod* lista)
{
	if (lista)
	{
		int sum = 0;
		Nod* temp = lista;
		while (temp)
		{
			sum += temp->info.nrAutori;
			temp = temp->next;
		}
		return sum;
	}
	else return 0;
}

int totalPaginiLista(Nod* lista)
{
	if (lista)
	{
		int sum = 0;
		Nod* temp = lista;
		while (temp)
		{
			sum += temp->info.nrPag;
			temp = temp->next;
		}
		return sum;
	}
	else return 0;
}


void plusOPaginaLista(Nod* lista)
{
	if (lista)
	{
		Nod* temp = lista;
		while (temp)
		{
			temp->info.nrPag++;
			temp = temp->next;
		}
	}
}

int totalAutoriHashTable(HashTable h)
{
	int sum = 0;
	for (int i = 0; i < h.dim; i++)
	{
		sum += totalAutoriLista(h.lista[i]);
	}
	return sum;
}

Nod* afiseazaCategorie(HashTable h, const char* categorie)
{
	int hashCode = hashFunction(h, initArticol(0, "necunoscut", categorie, 0, 0, NULL));
	return h.lista[hashCode];
}

void deleteNod(Nod* nod)
{
	if (nod)
	{
		for (int i = 0; i < nod->info.nrAutori; i++)
		{
			free(nod->info.autori[i]);
		}
		free(nod->info.autori);
		free(nod->info.categorie);
		free(nod->info.titlu);
		free(nod->next);
		free(nod);
		nod = NULL;
	}
}

HashTable plusOPagina(HashTable h)
{
	for (int i = 0; i < h.dim; i++)
	{
		plusOPaginaLista(h.lista[i]);
	}
	return h;
}

int* getNrPagini(HashTable h)
{
	int* vector = (int*)malloc(sizeof(int)*h.dim);
	for (int i = 0; i < h.dim; i++)
	{
		vector[i] = totalPaginiLista(h.lista[i]);
	}
	return vector;
}

//void deleteFromTable(HashTable h, const char* categorie, int id)
//{
//	int hashCode = hashFunction(h, initArticol(0, "necunoscut", categorie, 0, 0, NULL));
//	if (h.lista[hashCode])
//	{
//		Nod* temp = h.lista[hashCode];
//		if (temp->next) //inseamna ca sunt mai multe noduri
//		{
//			if (temp->info.id == id) //inseamna ca primul nod e cel cautat
//			{
//				h.lista[hashCode] = h.lista[hashCode]->next;
//				deleteNod(temp);
//			}
//		}
//		else //inseamna ca e doar un nod
//		{
//			if (temp->info.id == id)
//			{
//				deleteNod(temp);
//				temp = NULL;
//			}
//		}
//	}
//}

void main()
{
	const char** autori = (const char**)malloc(sizeof(char*) * 2);
	autori[0] = "Smeureanu Ion";
	autori[1] = "Boja Catalin";
	Articol a1 = initArticol(1, "POO", "Informatica", 210, 2, autori);
	Articol a2 = initArticol(2, "PAW", "Windows", 210, 2, autori);
	Articol a3 = initArticol(3, "SDD", "Data Structures", 210, 2, autori);
	Articol a4 = initArticol(4, "PEAG", "AI", 210, 2, autori);
	Articol a5 = initArticol(5, "PEAG", "AI", 210, 2, autori);
	Articol a6 = initArticol(6, "PEAG", "AI", 210, 2, autori);

	HashTable h = initHashTable(6);
	inserareHashTable(h, a1);
	inserareHashTable(h, a2);
	inserareHashTable(h, a3);
	inserareHashTable(h, a4);
	inserareHashTable(h, a5);
	inserareHashTable(h, a6);

	afisareHashTable(h);
	printf("\n\nTotal autori: %d\n\n", totalAutoriHashTable(h));
	afisareLista(afiseazaCategorie(h, "AI"));
	//deleteFromTable(h, "AI", 6);
	//afisareHashTable(h);

	afisareHashTable(plusOPagina(h));

	int* vector;
	vector = getNrPagini(h);
	printf("\nPagini/categorie: ");
	for (int i = 0; i < h.dim; i++)
	{
		printf("%d ", vector[i]);
	}
	
}