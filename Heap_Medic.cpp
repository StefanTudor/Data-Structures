#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Pacient
{
	int cod;
	char* nume;
	char* problema;
	float varsta;
	int prioritate;
};

struct HEAP
{
	int dim;
	Pacient* vector;
};

Pacient initPacient(int cod, const char* nume, const char* problema, float varsta, int prioritate)
{
	Pacient p;
	p.cod = cod;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.problema = (char*)malloc(sizeof(char) * (strlen(problema) + 1));
	strcpy(p.problema, problema);
	p.varsta = varsta;
	p.prioritate = prioritate;
	return p;
}

HEAP initHEAP(Pacient* p, int dim)
{
	HEAP h;
	h.dim = dim;
	h.vector = (Pacient*)malloc(sizeof(Pacient) * h.dim);
	return h;
}

void filtrare(HEAP h, int pozitie)
{
	int fiuS = 2 * pozitie + 1;
	int fiuD = 2 * pozitie + 2;
	int max = pozitie;

	if (fiuS < h.dim && h.vector[max].prioritate < h.vector[fiuS].prioritate)
	{
		max = fiuS;
	}
	if (fiuD < h.dim && h.vector[max].prioritate < h.vector[fiuD].prioritate)
	{
		max = fiuD;
	}
	if (max != pozitie)
	{
		Pacient temp = h.vector[max];
		h.vector[max] = h.vector[pozitie];
		h.vector[pozitie] = temp;

		if (2 * max + 1 < h.dim)
		{
			filtrare(h, max);
		}
	} 
}

void inserare(HEAP& h, Pacient p)
{
	Pacient* temp = (Pacient*)malloc(sizeof(Pacient) * (h.dim + 1));
	for (int i = 0; i < h.dim; i++)
	{
		temp[i] = h.vector[i];
	}
	temp[h.dim] = p;
	h.dim++;
	free(h.vector);
	h.vector = temp;
	for (int i = (h.dim - 2)/ 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
}

void extragere(HEAP& h)
{
	Pacient* temp = (Pacient*)malloc(sizeof(Pacient) * (h.dim - 1));
	for (int i = 0; i < h.dim - 1; i++)
	{
		temp[i] = h.vector[i + 1];
	}

	h.dim--;
	free(h.vector);
	h.vector = temp;

	for (int i = (h.dim - 2) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
}

void afisarePacient(Pacient p)
{
	printf("\nCod: %d\tNume: %s\tProblema: %s\tVarsta: %2.1f\tPrioritate: %d\n", p.cod, p.nume, p.problema, p.varsta, p.prioritate);
}

void afisareHEAP(HEAP h)
{
	for (int i = 0; i < h.dim; i++)
	{
		afisarePacient(h.vector[i]);
	}
}

void afisareDupaPrioritate(HEAP h, int prioritate)
{
	for (int i = 0; i < h.dim; i++)
	{
		if (h.vector[i].prioritate == prioritate)
		{
			afisarePacient(h.vector[i]);
		}
	}
}

void afisarePrioritateMaiMare(HEAP h, int prioritate)
{
	for (int i = 0; i < h.dim; i++)
	{
		if (h.vector[i].prioritate >= prioritate)
		{
			afisarePacient(h.vector[i]);
		}
	}
}


void main()
{

	HEAP h = initHEAP(NULL, 5);
	h.vector[0] = initPacient(1, "Ionut", "Raceala", 25.3, 1);
	h.vector[1] = initPacient(2, "Cristi", "Astm", 45, 5);
	h.vector[2] = initPacient(3, "Mihai", "Rujeola", 14, 4);
	h.vector[3] = initPacient(4, "Vlad", "Tuse", 55, 2);
	h.vector[4] = initPacient(5, "George", "Migrena", 20, 2);
	


	afisareHEAP(h);
	
	for (int i = (h.dim - 2) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}

	printf("\n\nDupa filtrare: \n");
	afisareHEAP(h);

	inserare(h, initPacient(6, "Boc", "Tensiune", 45, 3));
	printf("\n\nDupa inserare: \n");
	afisareHEAP(h);

	extragere(h);
	printf("\n\nDupa extragere: \n");
	afisareHEAP(h);

	printf("\n"); afisarePrioritateMaiMare(h, 3);
	printf("\n"); afisareDupaPrioritate(h, 2);
	
}