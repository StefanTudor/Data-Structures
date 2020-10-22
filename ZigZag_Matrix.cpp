#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Avion
{
	int nrMotoare;
	int nrLocuriPasageri;
	char* model;
};

Avion initializareAvion(int nrMotoare, int nrLocuri, const char* m)
{
	Avion a;
	a.nrMotoare = nrMotoare;
	a.nrLocuriPasageri = nrLocuri;
	a.model = (char*)malloc(strlen(m) * (sizeof(char) + 1));
	strcpy(a.model, m);
	return a;
}

void afisareAvion(Avion a)
{
	printf("Model: %s\t", a.model);
	printf("Nr. motoare: %d\t", a.nrMotoare);
	printf("Nr. locuri: %d\n", a.nrLocuriPasageri);
}

Avion citireAvion()
{
	Avion a;
	char buffer[30];
	printf("\nModel: ", buffer); scanf("%s", &buffer);
	a.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(a.model, buffer);
	printf("Introdu nr. motoare: "); scanf("%d", &a.nrMotoare);
	printf("Introdu nr. pasageri: "); scanf("%d", &a.nrLocuriPasageri);

	return a;
}

//citire & afisare vector de avioane

Avion* citireVectorAvioane(int &nrAv)
{
	Avion *a;
	printf("Introdu nr. elemente din vector: "); scanf("%d", &nrAv);
	a = (Avion*)malloc(nrAv * sizeof(Avion));
	for (int i = 0; i < nrAv; i++)
	{
		printf("\nAvionul nr. %d", i + 1);
		a[i] = citireAvion();
	}
	return a;
}

void afisareVectorAvioane(Avion* a, int nrAv)
{
	printf("\n");
	for (int i = 0; i < nrAv; i++)
		afisareAvion(a[i]);
}

//zigzag matrix

Avion** citireMatriceAvioane(int* nrLinii, int**nrColoane)
{
	Avion** a;
	printf("\nNr. linii: "); scanf("%d", nrLinii); 
	a = (Avion**)malloc((*nrLinii) * sizeof(Avion));
	*nrColoane = (int*)malloc((*nrLinii) * sizeof(int));
	for (int i = 0; i < *nrLinii; i++)
	{
		printf("\nNr. coloane linia %d: ", i + 1);
		scanf("%d", &(*nrColoane)[i]);
		a[i] = (Avion*)malloc((*nrColoane)[i] * sizeof(Avion));
		for (int j = 0; j < (*nrColoane)[i]; j++)
		{
			printf("\nAvionul de pe coloana %d(linia %d): ", j + 1, i + 1);
			a[i][j] = citireAvion();
		}
	}

	return a;
}

void afisareMatrice(Avion** matrice, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; i++)
	{
		printf("\nAvioanele de pe linia %d:\n", i + 1);
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afisareAvion(matrice[i][j]);
			printf("\n");
		}
	}
}

void main()
{
	Avion a = initializareAvion(4, 250, "Boeing");
	afisareAvion(a);
	/*Avion b = citireAvion();
	afisareAvion(b);*/

	/*Avion* aV;
	int nrAv;
	aV = citireVectorAvioane(nrAv);
	afisareVectorAvioane(aV,nrAv);*/

	Avion **aM;
	int nrL = 0;
	int *nrC = NULL;
	aM = citireMatriceAvioane(&nrL, &nrC);
	afisareMatrice(aM, nrL, nrC);

	//dezlocare
	for (int i = 0; i < nrL; i++)
	{
	 for (int j = 0; j < nrC[i]; j++)
	 {
	 free(aM[i][j].model); //sterge model
	 }
	 free (aM[i]); //sterge avioane de pe linii
	 }
	 free(aM);
	 free(nrC);
	 free(a.model);
	 //free(b.model);

}
