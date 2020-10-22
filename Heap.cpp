#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Angajat
{
	char* nume;
	int id;
};

struct HEAP
{
	Angajat* vector;
	int dim;
};

Angajat initAngajat(int id, const char* nume)
{
	Angajat a;
	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(a.nume, nume);
	a.id = id;
	return a;
}

void afisareAngajat(Angajat a)
{
	printf("\nId: %d, Nume: %s", a.id, a.nume);
}

HEAP initHEAP(int dim)
{
	HEAP h;
	h.dim = dim;
	h.vector = (Angajat*)malloc(sizeof(Angajat)*h.dim);
	return h;
}

void filtrare(HEAP h, int pozitie)
{
	int fiuS = 2 * pozitie + 1;
	int fiuD = 2 * pozitie + 2;
	int max = pozitie;
	if (fiuS<h.dim && h.vector[max].id > h.vector[fiuS].id)
	{
		max = fiuS; //salvez indexul
	}
	if (fiuD<h.dim && h.vector[max].id > h.vector[fiuD].id)
	{
		max = fiuD;
	}
	if (max != pozitie)
	{
		Angajat temp = h.vector[max];
		h.vector[max] = h.vector[pozitie];
		h.vector[pozitie] = temp;

		if (2 * max + 1 < h.dim)
		{
			filtrare(h, max);
		}
	}
}

HEAP inserareHEAP(HEAP& h, Angajat a)
{
	Angajat* temp = (Angajat*)malloc(sizeof(Angajat) + h.dim + 1);
	for (int i = 0; i < h.dim + 1; i++)
	{
		temp[i] = h.vector[i];
	}
	temp[h.dim] = a;
	h.dim++;
	free(h.vector);
	h.vector = temp;

	for (int i = (h.dim -2)/ 2; i >= 0; i--)
	{
		filtrare(h, i);
	}

	return h;
}

void afisareHEAP(HEAP h)
{
	for (int i = 0; i < h.dim; i++)
	{
		afisareAngajat(h.vector[i]);
	}
}

Angajat extragereHEAP(HEAP& h)
{
	if (h.dim > 0)
	{
		Angajat rezultat = h.vector[0];
		Angajat* temp = (Angajat*)malloc(sizeof(Angajat)*h.dim-1);
		for (int i = 0; i < h.dim - 1; i++)
		{
			temp[i] = h.vector[i + 1];
		}
		free(h.vector);
		h.vector = temp;
		h.dim--;
		
		for (int i = (h.dim - 2)/ 2; i >= 0; i--)
		{
			filtrare(h, i);
		}
		return rezultat;
	}
	else
	{
		return initAngajat(-1, "NECUNOSCUT");
	}

}

void afisareDupaUnID(HEAP h, int id)
{
	for (int i = 0; i < h.dim; i++)
	{
		if (h.vector[i].id == id)
		{
			afisareAngajat(h.vector[i]);
		}
	}
}

void main()
{

	HEAP heap = initHEAP(6);
	heap.vector[0] = initAngajat(4, "Tudor");
	heap.vector[1] = initAngajat(8, "Stefan");
	heap.vector[2] = initAngajat(3, "Ionut");
	heap.vector[3] = initAngajat(6, "Robert");
	heap.vector[4] = initAngajat(9, "Cristi");
	heap.vector[5] = initAngajat(2, "Viorel");
	printf("Inainte de filtrare: ");
	afisareHEAP(heap);
	printf("\n\nDupa filtrare:\n");
	for (int i = (heap.dim - 2) / 2; i >= 0; i--)
	{
		filtrare(heap, i);
	}
	afisareHEAP(heap);
	Angajat nou = extragereHEAP(heap);
	printf("\n\n"); afisareAngajat(nou);
	printf("\n\n"); afisareHEAP(heap);
}