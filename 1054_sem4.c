//liste simplu inlantuite 
// ultimul nod din lista pointeaza catre null
//ne trebuie adresa primului nod

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod
{
	Masina info;
	struct Nod* next;
};
typedef struct Nod N;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(N* Nod ) /*lista de masini*/ 
//afiseaza toate elemente de tip masina din lista simplu inlantuita
//prin apelarea functiei afisareMasina()
{
	
	while (Nod)
	{
		afisareMasina(Nod->info);
		Nod = Nod->next;
	}
}

void adaugaMasinaInLista(N** Lista, Masina masinaNoua)/*lista de masini*/ 
//adauga la final in lista primita o noua masina pe care o primim ca parametru
{
	N* nodNou;
	nodNou = (N*)malloc(sizeof(N));
	nodNou->info = masinaNoua;//shallow copy , si masina me SI ELEMENTUL DIN LISTA POINTEAZA CATRE ACEASI ZONA DE MEM , IAR TUNCI CAND STERG DIN LISTA , STERG SI DIN MEMORIE
	nodNou->next = NULL;

	if ((*Lista)==NULL)// * lista de pointer la pointer si trebuie dereferentiat , verificam existenta primului nod
	{
		(*Lista) = nodNou;
	}
	else
	{//nu ne putem deplass cu lista pentru ca ajungand la ultimul nod vom pierde elem anterioare
		N* aux = (*Lista);
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}

}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

N* citireListaMasiniDinFisier(const char* numeFisier)//functia era void* pointer generic la void 
//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
{
	FILE* f;
	f = fopen(numeFisier, "r");
	N* lista=NULL;//trebuie initializata cu null pentru ca altfel va primi o valoare reziduala si vom avea eroare in Adauga Masina In Lista
	while (!feof(f))
	{
		Masina m;//ne declaram o masina noua 
		m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista,m);
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(N** Lista) /*lista de masini*/
//sunt dezalocate toate masinile si lista de elemente
{
	while ((*Lista))
	{
		N* p = *Lista;//*Lista dereferentiata
		(*Lista) = (*Lista)->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);

	}
}
	

float calculeazaPretMediu(N* lista)
//calculeaza pretul mediu al masinilor din lista.
{
	float suma = 0;
	int contor = 0;
	while (lista)
	{
		suma += lista->info.pret;
		contor++;
	}
	if (contor == 0)
	{
		return 0;
	}
	return suma / contor;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(N* lista, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.

	float suma = 0;
	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return 0;

}

int main() 
{
	N* nod;
	nod=citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(nod);
	dezalocareListaMasini(nod);

	printf("/n");
	float medie = calculeazaPretMediu(nod);
	printf("Media este : %.2f", medie);
	return 0;
}