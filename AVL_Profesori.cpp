#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Profesor
{
	int id;
	char* nume;
	int grad;
};

struct NOD
{
	NOD* st;
	NOD* dr;
	Profesor info;
};

Profesor initProfesor(int id, const char* nume, int grad)
{
	Profesor p;
	p.id = id;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.grad = grad;
	return p;
}

NOD* initNOD(NOD* st, NOD* dr, Profesor p)
{
	NOD* nod = (NOD*)malloc(sizeof(NOD));
	nod->st = st;
	nod->dr = dr;
	nod->info = p;
	return nod;
}

int inaltimeArbore(NOD* rad)
{
	if (rad)
	{
		int st = inaltimeArbore(rad->st);
		int dr = inaltimeArbore(rad->dr);
		return 1 + (st > dr ? st : dr);
	}
	else
	{
		return 0;
	}
}

int gradEchilibru(NOD* rad)
{
	if (rad)
	{
		int gSt = inaltimeArbore(rad->st);
		int gDr = inaltimeArbore(rad->dr);
		return gSt - gDr;
	}
	else
	{
		return 0;
	}
}

NOD* rotireDreapta(NOD* rad)
{
	if (rad)
	{
		NOD* temp = rad->st;
		rad->st = temp->dr;
		temp->dr = rad;
		return temp;
	}
	else
	{
		return rad;
	}
}

NOD* rotireStanga(NOD* rad)
{
	if (rad)
	{
		NOD* pivot = rad->dr;
		rad->dr = pivot->st;
		pivot->st = rad;
		return pivot;
	}
	else
	{
		return rad;
	}
}

NOD* inserareArbore(NOD* rad, Profesor p)
{
	if (rad)
	{
		if (rad->info.grad > p.grad)
		{
			rad->st = inserareArbore(rad->st, p);
		}
		else
		{
			rad->dr = inserareArbore(rad->dr, p);
		}
		int gE = gradEchilibru(rad);
		if (gE == 2)
		{
			int gES = gradEchilibru(rad->st);
			if (gES != 1)
			{
				rad->st = rotireStanga(rad->st);
			}
			rad = rotireDreapta(rad);
		}
		if (gE == -2)
		{
			int gED = gradEchilibru(rad->dr);
			if (gED != -1)
			{
				rad->dr = rotireDreapta(rad->dr);
			}
			rad = rotireStanga(rad);
		}

		return rad;
	}
	else
	{
		return initNOD(NULL, NULL, p);
	}
}

Profesor profesorDupaID(NOD* rad, int id)
{
	if (rad)
	{
		if (rad->info.id == id)
		{
			return rad->info;
		}
		else
		{
			if (rad->info.id > id)
			{
				return profesorDupaID(rad->st, id);
			}
			else
			{
				return profesorDupaID(rad->dr, id);
			}
		}
	}
	else
	{
		return initProfesor(-1, "NECUNOSCUT", -1);
	}
}

void afisareProfesor(Profesor p);

void cautaProfesorDupaNume(NOD* rad, const char* nume)
{
	if (rad)
	{
		if (strcmp(rad->info.nume, nume) == 0)
		{
			afisareProfesor(rad->info);
		}
		cautaProfesorDupaNume(rad->st, nume);
		cautaProfesorDupaNume(rad->dr, nume);
	}
	else
	{
		//return initProfesor(-1, "NECUNOSCUT", -1);
	}
}

int nrNoduri(NOD* root, const char* nume)
{
	if (root)
	{
		if (strcmp(root->info.nume, nume) == 0)
		{
			int nS = nrNoduri(root->st, nume);
			int nD = nrNoduri(root->dr, nume);
			return 1 + nS + nD;
		}
		else
		{
			return nrNoduri(root->st, nume) + nrNoduri(root->dr, nume);
		}
	}
	else
	{
		return 0;
	}
}

int* adaugaVector(NOD* root, const char* nume, int* &vector, int &iterator)
{
	if (root)
	{
		if (strcmp(root->info.nume, nume) == 0)
		{
			vector[iterator] = root->info.id;
			iterator++;

		}
		adaugaVector(root->st, nume, vector, iterator);
		adaugaVector(root->dr, nume, vector, iterator);
		return vector;
	}
	else
	{
		return vector;
	}
}

void afisareProfesor(Profesor p)
{
	printf("\nID: %d\tNume: %s\tGrad: %d\n", p.id, p.nume, p.grad);
}

void afisareINORDINE(NOD* radacina)
{
	if (radacina)
	{
		afisareINORDINE(radacina->st);
		afisareProfesor(radacina->info);
		afisareINORDINE(radacina->dr);
	}
}

void afisareFrunze(NOD* root)
{
	if (root)
	{
		if (root->st == NULL && root->dr == NULL)
		{
			afisareProfesor(root->info);
		}
		afisareFrunze(root->st);
		afisareFrunze(root->dr);
	}
}

void main()
{
	Profesor p1 = initProfesor(18, "Ion", 6);
	Profesor p2 = initProfesor(7, "Ion", 24);
	Profesor p3 = initProfesor(34, "Vasile", 4);
	Profesor p4 = initProfesor(15, "Vasile", 1);
	Profesor p5 = initProfesor(13, "Ion", 3);
	Profesor p6 = initProfesor(19, "Vasile", 9);
	Profesor p7 = initProfesor(17, "Vasile", 7);
	Profesor p8 = initProfesor(16, "Vasile", 8);


	NOD* rad = NULL;
	rad = inserareArbore(rad, p1);
	rad = inserareArbore(rad, p2);
	rad = inserareArbore(rad, p3);
	rad = inserareArbore(rad, p4);
	rad = inserareArbore(rad, p5);
	rad = inserareArbore(rad, p6);
	rad = inserareArbore(rad, p7);
	rad = inserareArbore(rad, p8);
	afisareINORDINE(rad);
	printf("\n\nInaltime arbore: %d", inaltimeArbore(rad));
	printf("\n");
	cautaProfesorDupaNume(rad, "Ion");
	printf("\nNr. noduri: %d\n", nrNoduri(rad, "Vasile"));
	int numara = nrNoduri(rad, "Vasile");
	int iterator = 0;
	int* vector = (int*)malloc(sizeof(int) * numara);
	adaugaVector(rad, "Vasile", vector, iterator);
	for (int i = 0; i < numara; i++)
	{
		printf(" %d", vector[i]);
	}
	printf("\n\n");
	afisareFrunze(rad);
}