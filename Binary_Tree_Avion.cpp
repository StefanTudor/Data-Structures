#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Avion
{ 
	char* nume;
	int nrBilete;
	int* bilete;
};

struct NOD
{
	Avion info;
	NOD* stanga;
	NOD* dreapta;
};

Avion initAvion(const char* nume, int nrBilete, int* bilete)
{
	Avion a;
	a.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(a.nume, nume);
	a.nrBilete = nrBilete;
	a.bilete = (int*)malloc(sizeof(int)*nrBilete);
	for (int i = 0; i < nrBilete; i++)
	{
		a.bilete[i] = bilete[i];
	}
	return a;
}

NOD* initNOD(NOD* stanga, NOD* dreapta, Avion a)
{
	NOD* nou = (NOD*)malloc(sizeof(NOD));
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	nou->info = a;
	return nou;
}

Avion citireArtistDinFisier(FILE* f)
{
	Avion a;
	char buffer[30];
	fscanf(f, "%s", buffer);
	a.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(a.nume, buffer);
	fscanf(f, "%d", &a.nrBilete);
	a.bilete = (int*)malloc(sizeof(int)*a.nrBilete);
	for (int i = 0; i < a.nrBilete; i++)
	{
		fscanf(f, "%d", &a.bilete[i]);

	}
	return a;
}

void afisareAvion(Avion a)
{
	printf("\nNume: %s, Nr. bilete: %d, Bilete: ", a.nume, a.nrBilete);
	for (int i = 0; i < a.nrBilete; i++)
	{
		printf("%d", a.bilete[i]);
		if (i < a.nrBilete - 1) { printf(", "); }
	}
}


NOD* inserareAvion(NOD* radacina, Avion a)
{
	if (radacina)
	{
		if (radacina->info.nrBilete > a.nrBilete)
		{
			radacina->stanga = inserareAvion(radacina->stanga, a);
		}
		else
		{
			radacina->dreapta = inserareAvion(radacina->dreapta, a);
		}
		return radacina;
	}
	else
	{
		return initNOD(NULL, NULL, a);
	}
}

int inaltimeArbore(NOD* radacina)
{
	if (radacina)
	{
		int st = inaltimeArbore(radacina->stanga);
		int dr = inaltimeArbore(radacina->dreapta);
		return 1 + (st > dr ? st : dr);
	}
	else
	{
		return 0;
	}
}

void afisareArboreBinarINORDINE(NOD* radacina)
{
	if (radacina)
	{
		afisareArboreBinarINORDINE(radacina->stanga);
		afisareAvion(radacina->info);
		afisareArboreBinarINORDINE(radacina->dreapta);
	}
}
void afisareArboreBinarPREORDINE(NOD* radacina)
{
	if (radacina)
	{
		afisareAvion(radacina->info);
		afisareArboreBinarPREORDINE(radacina->stanga);
		afisareArboreBinarPREORDINE(radacina->dreapta);
	}
}
void afisareArboreBinarPOSTORDINE(NOD* radacina)
{
	if (radacina)
	{
		afisareArboreBinarPOSTORDINE(radacina->stanga);
		afisareArboreBinarPOSTORDINE(radacina->dreapta);
		afisareAvion(radacina->info);
	}
}

Avion cautaDupaNrLocuri(NOD* radacina, int nrBilete)
{
	if (radacina)
	{
		if (radacina->info.nrBilete == nrBilete)
		{
			return radacina->info;
		}
		else
		{
			if (radacina->info.nrBilete > nrBilete)
			{
				return cautaDupaNrLocuri(radacina->stanga, nrBilete);
			}
			else
			{
				return cautaDupaNrLocuri(radacina->dreapta, nrBilete);
			}
		}
	}
	else
	{
		return initAvion("NECUNOSCUT", -1, NULL);
	}
}

void afisarePeNivel(NOD* radacina, int nivelDorit, int nivelCurent)
{
	if (radacina)
	{
		if (nivelDorit == nivelCurent)
		{
			afisareAvion(radacina->info);
		}
		else
		{
			afisarePeNivel(radacina->stanga, nivelDorit, nivelCurent + 1);
			afisarePeNivel(radacina->dreapta, nivelDorit, nivelCurent + 1);
		}
	}
}

int* afisareLocuriDupaModel(NOD* radacina, int* &vector, const char* model, int& gasit)
{
	if (radacina)
	{
		if (strcmp(radacina->info.nume, model) == 0)
		{
			if (gasit > 0)
			{
				int* temp = (int*)malloc(sizeof(int) * (gasit + 1));
				for (int i = 0; i < gasit; i++)
				{
					temp[i] = vector[i];
				}
				temp[gasit] = radacina->info.nrBilete;
				free(vector);
				vector = temp;
			}
			else
			{
				vector[gasit] = radacina->info.nrBilete;
			}
			gasit++;
		}
		afisareLocuriDupaModel(radacina->stanga, vector, model, gasit);
		afisareLocuriDupaModel(radacina->dreapta, vector, model, gasit);
		return vector;
	}
}

void main()
{

	NOD* radacina = NULL;
	FILE* f = fopen("Avioane.txt", "r");
	if (f)
	{
		int nrAvioane;
		fscanf(f, "%d", &nrAvioane);
		
		for (int i = 0; i < nrAvioane; i++)
		{
			radacina = inserareAvion(radacina, citireArtistDinFisier(f));
		}

	}
	fclose(f);

	printf("\n\nINORDINE:\n");
	afisareArboreBinarINORDINE(radacina);
	printf("\n\nPREORDINE:\n");
	afisareArboreBinarPREORDINE(radacina);
	printf("\n\nPOSTORDINE:\n");
	afisareArboreBinarPOSTORDINE(radacina);
	printf("\n");
	afisareAvion(cautaDupaNrLocuri(radacina,5));
	printf("\nInaltime arbore: %d", inaltimeArbore(radacina));
	printf("\n");
	afisarePeNivel(radacina, 2, 0);
	printf("\n");
	int* vector = (int*)malloc(sizeof(int));
	int gasite = 0;
	vector = afisareLocuriDupaModel(radacina, vector, "B737", gasite);
	for (int i = 0; i < gasite; i++)
	{
		printf("%d ", vector[i]);
	}
	printf("\n\n");
}