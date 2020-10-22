#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Comanda
{
	int id;
	char* nume;
	int nrProduse;
	float* preturi;
};

struct NOD
{
	NOD* stanga;
	NOD* dreapta;
	Comanda info;
};

Comanda initComanda(int id, const char* nume, int nrProduse, float* preturi)
{
	Comanda c;
	c.id = id;
	c.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(c.nume, nume);
	c.nrProduse = nrProduse;
	c.preturi = (float*)malloc(sizeof(float) * nrProduse);
	for (int i = 0; i < c.nrProduse; i++)
	{
		c.preturi[i] = preturi[i];
	}
	return c;
}

NOD* initNOD(NOD* stanga, NOD* dreapta, Comanda c)
{
	NOD* nou = (NOD*)malloc(sizeof(NOD));
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	nou->info = c;
	return nou;
}

void afisareComanda(Comanda c)
{
	printf("\nID: %d, Nume: %s, Nr. Produse: %d, Preturi: ", c.id, c.nume, c.nrProduse);
	for (int i = 0; i < c.nrProduse; i++)
	{
		printf("%5.2f", c.preturi[i]);
		if (i < c.nrProduse - 1)
		{
			printf(", ");
		}
	}
}

int verificaNoduriFrunze(NOD* root, const char* nume)
{
	if (root)
	{
		if (((root->stanga == root->dreapta) != NULL) && (strcmp(root->info.nume, nume) == 0))
		{
			return 1;
		}
		else
		{
			return verificaNoduriFrunze(root->stanga, nume) +
			verificaNoduriFrunze(root->dreapta, nume);
		}
	}
	else
	{
		return 0;
	}
}

int getNrFrunze(NOD* root)
{
	if (root)
	{
		if (root->dreapta == NULL && root->stanga == NULL)
		{
			return 1;
		}
		else
		{
			return getNrFrunze(root->stanga) + getNrFrunze(root->dreapta);
		}
	}
	else
	{
		return 0;
	}
}

int cautaMinim(NOD* root)
{
	if (root)
	{
		if (root->stanga)
		{
			return cautaMinim(root->stanga); //ma duc pe ramura din stanga pana root->stanga == NULL
		}
		else
		{
			return root->info.id; //returnez nodul unde s-a oprit cautaMinim();
		}
	}
}

void afisareNivel(NOD* root, int nivelCurent, int nivelDorit)
{
	if (root)
	{
		if (nivelCurent == nivelDorit)
		{
			afisareComanda(root->info);
		}
		else
		{
			afisareNivel(root->stanga, nivelCurent + 1, nivelDorit);
			afisareNivel(root->dreapta, nivelCurent + 1, nivelDorit);
		}
	}
}

void afisareArboreINORDINE(NOD* root)
{
	if (root)
	{
		afisareArboreINORDINE(root->stanga);
		afisareComanda(root->info);
		afisareArboreINORDINE(root->dreapta);
	}
}

int calculeazaInaltimeArbore(NOD* root)
{
	if (root)
	{
		int hS = calculeazaInaltimeArbore(root->stanga);
		int hD = calculeazaInaltimeArbore(root->dreapta);
		return 1 + (hS > hD ? hS : hD);
	}
	else
	{
		return 0;
	}
}

int calculeazaGradEchilibru(NOD* root)
{
	if (root)
	{
		int hS = calculeazaInaltimeArbore(root->stanga);
		int hD = calculeazaInaltimeArbore(root->dreapta);
		return hS - hD;
	}
	else
	{
		return 0;
	}
}

NOD* rotireLaDreapta(NOD* root)
{
	if (root)
	{
		NOD* pivot = root->stanga;
		root->stanga = pivot->dreapta;
		pivot->dreapta = root;
		return pivot;
	}
	else
	{
		return root;
	}
}

NOD* rotireLaStanga(NOD* root)
{
	if (root)
	{
		NOD* pivot = root->dreapta;
		root->dreapta = pivot->stanga;
		pivot->stanga = root;
		return pivot;
	}
	else
	{
		return root;
	}
}

NOD* insereazaInArbore(NOD* root, Comanda c)
{
	if (root)
	{
		if (root->info.id > c.id)
		{
			root->stanga = insereazaInArbore(root->stanga, c);
		}
		else
		{
			root->dreapta = insereazaInArbore(root->dreapta, c);
		}
		int gradE = calculeazaGradEchilibru(root);
		if (gradE == 2)
		{
			int gradES = calculeazaGradEchilibru(root->stanga);
			if (gradES != 1)
			{
				root->stanga = rotireLaStanga(root->stanga);
			}
			root = rotireLaDreapta(root);
		}
		if (gradE == -2)
		{
			int gradED = calculeazaGradEchilibru(root->dreapta);
				if (gradED != -1)
				{
					root->dreapta = rotireLaDreapta(root->dreapta);
				}
				root = rotireLaStanga(root);
		}
		return root;
	}
	else
	{
		NOD* nou = initNOD(NULL, NULL, c);
	}
}

void main()
{
	NOD* root = NULL;
	root = insereazaInArbore(root, initComanda(8, "Tudor", 3, new float[3] {12, 21, 43}));
	root = insereazaInArbore(root, initComanda(6, "Mihai", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(15, "Cristi", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(5, "Dan", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(7, "Tom", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(9, "Tom", 3, new float[3]{ 12, 21, 43 }));
	//root = insereazaInArbore(root, initComanda(10, "Tom", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(3, "Ion", 3, new float[3]{ 12, 21, 43 }));
	root = insereazaInArbore(root, initComanda(4, "Marcel", 3, new float[3]{ 12, 21, 43 }));
	//root = insereazaInArbore(root, initComanda(1, "Victor", 3, new float[3]{ 12, 21, 43 }));

	afisareArboreINORDINE(root);

	printf("\n\n");
	int no = verificaNoduriFrunze(root,"Tom");
	printf("%d\n\n", no);
	int nr = getNrFrunze(root);
	printf("%d\n\n",nr);
	int n = cautaMinim(root);
	printf("%d\n\n", n);
	int h = calculeazaInaltimeArbore(root);
	printf("%d\n\n", h);
	afisareNivel(root, 0, 4);
	printf("\n\n");

}