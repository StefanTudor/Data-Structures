#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Moneda
{
	char codMoneda[3];
	char* emitent;
	char* denumire;
	int sold;
};

struct HashTable
{
	Moneda* *vector;
	int dim;
};

Moneda* adaugareMoneda(const char cod[3], const char* emitent, const char* denumire, int sold)
{
	Moneda* m = (Moneda*)malloc(sizeof(Moneda));
	strcpy(m->codMoneda, cod);
	m->emitent = (char*)malloc(sizeof(char)*(strlen(emitent) + 1));
	strcpy(m->emitent, emitent);
	m->denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(m->denumire, denumire);
	m->sold = sold;
	return m;
}

int hashFunction(HashTable h, Moneda* m)
{
	int s = 0;
	for (int i = 0; i < strlen(m->codMoneda); i++)
	{
		s += m->codMoneda[i];
	}
	return s % h.dim;
}

HashTable initHashtable(int dim)
{
	HashTable h;
	h.dim = dim;
	h.vector = (Moneda**)malloc(sizeof(Moneda*)*h.dim);
	for (int i = 0; i < h.dim; i++)
	{
		h.vector[i] = NULL;
	}
	return h;
}

void afisareMoneda(Moneda* m)
{
	printf("%s --- %s --- %s --- %d\n", m->codMoneda, m->emitent, m->denumire, m->sold);
}

void afisareHashTable(HashTable h)
{
	if (h.dim > 0)
	{
		for (int i = 0; i < h.dim; i++)
			if (h.vector[i])
				afisareMoneda(h.vector[i]);
	}
}

int inserareHashTable(Moneda* m, HashTable h)
{
	if (h.dim > 0)
	{
		int hashCode = hashFunction(h, m);
		if (h.vector[hashCode])
		{
			int index = (hashCode + 1) % h.dim;
			while (hashCode != index && h.vector[index] != NULL)
			{
				index = (index + 1) % h.dim;
			}
			if (index == hashCode)
			{
				return -1;//tabela este plina
			}
			else
			{
				h.vector[index] = m;
				return hashCode;
			}

		}
		else
		{
			h.vector[hashCode] = m;
			return hashCode;
		}
	}
	else
		return -2; //tabela este goala
}


void comparare(HashTable h, int valoare)
{
	int nr = 0;
	for (int i = 0; i < h.dim; i++)
	{
		if (h.vector[i]->sold > valoare)
			nr++;
	}

	Moneda** nou = (Moneda**)malloc(sizeof(Moneda*)*nr);
	for (int i = 0; i < h.dim; i++)
	{
		int j = 0;
		if (h.vector[i]->sold > valoare)
		{
			nou[j] = h.vector[i];
			j++;
			afisareMoneda(h.vector[i]);
		}
	}
}

void inlocuireValoare(HashTable h, const char* denumire, int valoare)
{
	if (h.dim > 0)
	{
		int poz;
		int hashCode = hashFunction(h, h.vector[0]);
		for (int i = 0; i < h.dim; i++)
		{
			if (h.vector[hashCode] && strcmp(h.vector[hashCode]->denumire, denumire) == 0)
			{
				h.vector[hashCode]->sold = valoare;
			}
			else
			{
				hashCode = (hashCode + 1) % h.dim;
			}
		}

	}

}

void main()
{
	HashTable h = initHashtable(5);
	Moneda* m1 = adaugareMoneda("RON", "Banca Nationala Roamana", "LEU", 10000);
	inserareHashTable(m1, h);
	Moneda* m2 = adaugareMoneda("EUR", "Banca Europeana Centrala", "EURO", 4000);
	inserareHashTable(m2, h);
	Moneda* m3 = adaugareMoneda("GBP", "Banca Reginei Angliei", "LIRA STERLINA", 5000);
	inserareHashTable(m3, h);
	Moneda* m4 = adaugareMoneda("CHF", "La Casa de Papel", "FRANC ELVETIAN", 2000);
	inserareHashTable(m4, h);
	Moneda* m5 = adaugareMoneda("USD", "United States of America", "DOLAR", 8000);
	inserareHashTable(m5, h);
	afisareHashTable(h);
	printf("\n\n");
	comparare(h, 6000);
	printf("\n\n");
	inlocuireValoare(h,"DOLAR" , 1111);
	afisareHashTable(h);

}
