#include <stdio.h>
#include <string.h>

#define MAX_HAUTEUR 3
#define MAX_LARGEUR 3

int main(){
	int maxval=255;
	int matrice[MAX_HAUTEUR][MAX_LARGEUR];
	char matrice_donnee[128], matrice_copiee[128];
	FILE *flot_entree, *flot_sortie;
	
	strcpy(matrice_donnee, "matrice.txt");
	strcpy(matrice_copiee, "matriceC.txt");
	
	flot_entree = fopen(matrice_donnee, "r");
	flot_sortie = fopen(matrice_copiee, "w");
	
	if (flot_entree==NULL || flot_sortie==NULL){
		printf("Erreur d'ouverture de fichier.\n");
	}
	else{
		while (!feof(flot_entree)){
			for (int l=0;l<MAX_HAUTEUR;l++){
				for (int c=0;c<MAX_LARGEUR;c++){
					fscanf(flot_entree, "%d", &matrice[l][c]);
					matrice[l][c]=maxval-matrice[l][c];
					fprintf(flot_sortie, "%d\t", matrice[l][c]);
				}
			fprintf(flot_sortie, "\n");	
			}
		}
	}
	return (0);
	fclose(flot_entree);
	fclose(flot_sortie);
	return 0;
}

