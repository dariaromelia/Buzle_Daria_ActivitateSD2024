#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserareLocuinta(struct Locuinta** vector, int* dim, struct Locuinta l)
{
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++) {
		copie[i] = *vector[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL) 
	{
		free((*vector));
	}
	(*vector) = copie;


}

//o functie care sa citeasca cateva locuinte din fisier
void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r"); //numele si modul de deschidere
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token=strtok(buffer,delimitator);
				struct Locuinta locuinta;
				//pasul 1 ne creeam locuinta, dupa care adaugam in ea
				locuinta.id = atoi(token); //abscii to int = ATOI
				token = strtok(NULL, delimitator);
				//token cauta daca a mai fost apelat anterior!!!
				locuinta.strada = (char*)malloc(sizeof(char)*(strlen(token) + 1));
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				//noi avem acum LOCUINTA, pasul 2 trebuie sa il punem in vector
				//o functie de inserare intr-un fisier a unei locuinte
				inserareLocuinta(vector, dim, locuinta);

			}
			fclose(f);
		}
		
	}

}

void afisareLocuinta(struct Locuinta l) {
	printf("ID-ul: %d\t%s numarul %d\n", l.id, l.strada, l.numar);
}

void afisareVectorLocuinte(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++)
		afisareLocuinta(vector[i]);
}

void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((vector)[i]->id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) { //avem o locuinta de sters
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * ((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		if ((*vector) != NULL) {
			free((*vector));
		}
		(*vector) = copie;
	}
}

void main() {
	struct Locuinta *locuinte = NULL;
	int dim = 3;
	citesteFisier("locuinte.txt", &locuinte, &dim);
	afisareVectorLocuinte(locuinte, dim);
	//printf("Initial  \n\n");
	
	//printf("\n\nUlterior  \n\n");
	//stergeLocuinta(&locuinte, &dim, 22);
	//afisareVectorLocuinte(locuinte, dim);

}

//https://online.ase.ro/course/view.php?id=41166