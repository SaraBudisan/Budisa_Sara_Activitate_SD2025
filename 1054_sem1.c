// se lucreaza in c 
//extensia fisierului sa fie .c neaparat
#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer ;//OCUPA 8 o pe 64x si 4 o pe 84x
	float kilometriiParcursi;
	char initialaProducatorului;
};

struct Masina initializare(int id, int anFabricatie ,const char* sofer, float kilometriiParcursi, char initialaProducatorului) //similara constructorului cu parametrii
{ //punem const ca sa nu modificam parametrul
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	m.sofer = (char*)malloc(strlen(sofer) + 1);//facem un cast explicit  //malloc este pointer la void , pointer la orice//
	strcpy_s(m.sofer, strlen(sofer) + 1, sofer);//strcpy copiaza cu buffer overflow. iar _s iti da o zona specifica de caractere pe care le poate copia
	m.kilometriiParcursi = kilometriiParcursi;
	m.initialaProducatorului = initialaProducatorului;
	return m;
}

void afisare(struct Masina m) {
	printf("ID : %d \n", m.id);
	printf("AN fabricatie : %d \n", m.anFabricatie);
	printf("Sofer : %s \n ", m.sofer);
	printf("Km : %f \n", m.kilometriiParcursi);
	printf("Initiala Producator: %c \n", m.initialaProducatorului);
	//functie cunumar variabil de parametrii min 1 , scanf la fel //intre parantezze avem marcatori
}

void modifica_Sofer(struct Masina* m, const char* nouSofer ) {
	if (strlen(nouSofer) > 2)
	{
		if (m->sofer == NULL)
		{
			free(m->sofer);
		}
	}
	m->sofer = (char*)malloc(strlen(nouSofer) + 1);
	strcpy_s(m->sofer, strlen(nouSofer)+1, nouSofer);
}

void dezalocare(struct Masina* m) {
	if (m->sofer != NULL)
	{
		free(m->sofer);
		m->sofer = NULL;
	}
}

int main() {
	struct Masina masina;//in c trevbuie sa declaram compilatorului ca folosim o clasa de tip struct
	masina = initializare(1, 2004, "Sara", 250000, 'w');
	afisare(masina);
	modifica_Sofer(&masina,"Alex");
	afisare(masina);
	dezalocare(&masina);
	return 0;
}