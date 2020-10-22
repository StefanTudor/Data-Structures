#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Racheta
{
	int id;
	char* misiune;
	int kgTransportate;
	char* destinatie;
};

struct NOD
{
	NOD* next;
	Racheta info;
};

Racheta initRacheta(int id, const char* misiune, int kg, const char* destinatie)
{
	Racheta r;
	r.id = id;
	r.misiune = (char*)malloc(sizeof(char)*(strlen(misiune)+1));
	strcpy(r.misiune, misiune);
	r.kgTransportate = kg;
	r.destinatie = (char*)malloc(sizeof(char)*(strlen(destinatie)+1));
	strcpy(r.destinatie, destinatie);
	return r;
}

NOD* initNOD(NOD* next, Racheta r)
{
	NOD* nod = (NOD*)malloc(sizeof(NOD));
	nod->info = r;
	nod->next = next;
	return nod;
}

NOD* inserareInceputListaSimpla(NOD* lista, Racheta r)
{
	NOD* nou = initNOD(lista, r);
	lista->next = nou;
	return nou;
}

void afisareRacheta(Racheta r)
{
	printf("\nId: %d\tMisiune: %s\tKG Transportate: %d\tDestinatie:%s\n", r.id, r.misiune, r.kgTransportate, r.destinatie);
}

void afisareListaSimpla(NOD* lista)
{
	if (lista)
	{
		NOD* temp = lista;
		while (temp->next != lista)
		{
			afisareRacheta(temp->info);
			temp = temp->next;
		}
	}
}

void main()
{
	Racheta r = initRacheta(1, "Falcon_9", 1500, "Luna");
	Racheta r2 = initRacheta(2, "Falcon_9", 1500, "Luna");
	Racheta r3 = initRacheta(3, "Falcon_9", 1500, "Luna");
	Racheta r4 = initRacheta(4, "Falcon_9", 1500, "Luna");
	//afisareRacheta(r);

	NOD* lista = NULL;
	lista = initNOD(*(&lista), r);
	lista = initNOD(lista, r2);
	lista = initNOD(lista, r3);
	lista = initNOD(lista, r4);
	
	afisareListaSimpla(lista);
}