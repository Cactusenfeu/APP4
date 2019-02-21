/* ????!?!!?!?!?????????*/

#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];


int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], 
				int *p_lignes, int *p_colonnes, int *p_maxval, 
				struct MetaData *p_metadonnees)
{
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0;
	FILE *flot_entree;
	
	flot_entree = fopen(nom_fichier, "r");
	
	if(flot_entree == NULL){
		printf("Erreur d’ouverture de fichier.\n");
		return -1;
	}
	 
	else{		
		fscanf(flot_entree, "%c", premiere);
		if (premiere[0] == '#'){
			printf("%s", premiere);
			
			for (int i=0; i<MAX_CHAINE; i++){
				fscanf(flot_entree, "%c", &a[i]);
				if (a[i] != '\n'){
					printf("%c", a[i]);
				}
				else{
					i = MAX_CHAINE;
				}
			}
			fscanf(flot_entree, "%[^\n]", p);
			printf("\n%s\n", p);
			if (p[1] != '3'){
				printf("ERREUR3");
				return -3;
			}
		}
		if (premiere[0] == 'P'){
			printf("%s", premiere);
			fscanf(flot_entree, "%[^\n]", p);
			printf("%s\n", p);
			if (p[0] != '3'){
				printf("ERREUR3");
				return -3;
			}
		}
		
			fscanf(flot_entree, "%d %d %d", &b, &c, &d);
			printf("%d %d\n%d\n", b, c, d);
			*p_lignes = b;
			*p_colonnes = c;
			*p_maxval = d;
			if (b>256 || c>256){
				printf("ERREUR2");
				return -2;
			}
			for (int i=0; i<b; i++){
				for (int j=0; j<c; j++){
					fscanf(flot_entree, "%d %d %d", &matrice[i][j].valeurR, &matrice[i][j].valeurG, &matrice[i][j].valeurB);
				}	
			}
	
	}
    return OK;
}


int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens){
	
	struct RGB matrice_temp[MAX_HAUTEUR][MAX_LARGEUR];
	printf("\nORIGINALE: \n");
	
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			printf("%d ", matrice[i][j].valeurR);
			printf("%d ", matrice[i][j].valeurG);
			printf("%d ", matrice[i][j].valeurB);
		}
		printf("\n");
	}
	
	
	if (sens==0){
		printf("\nSENS ANTI-HORAIRE\n");
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[*p_colonnes-j-1][i].valeurR = matrice[i][j].valeurR;
				matrice_temp[*p_colonnes-j-1][i].valeurG = matrice[i][j].valeurG;
				matrice_temp[*p_colonnes-j-1][i].valeurB = matrice[i][j].valeurB;
			}
		}
	}
	
	if (sens==1){
		printf("\nSENS HORAIRE\n");
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[j][*p_lignes-1-i].valeurR = matrice[i][j].valeurR;
				matrice_temp[j][*p_lignes-1-i].valeurG = matrice[i][j].valeurG;
				matrice_temp[j][*p_lignes-1-i].valeurB = matrice[i][j].valeurB;
			}
		}
	}
	
	int temp = *p_lignes;
	*p_lignes = *p_colonnes;
	*p_colonnes = temp;
	
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			matrice[i][j].valeurR = matrice_temp[i][j].valeurR;
			matrice[i][j].valeurG = matrice_temp[i][j].valeurG;
			matrice[i][j].valeurB = matrice_temp[i][j].valeurB;
		}
	}
	printf("\nROTATION: \n");
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			printf("%d ", matrice[i][j].valeurR);
			printf("%d ", matrice[i][j].valeurG);
			printf("%d ", matrice[i][j].valeurB);
		}
		printf("\n");
	}
	return 0;
}

int main()
{
    int lignes, colonnes;
    int maxval;
    struct MetaData metadonnees;
	
	
	ppm_lire("test.ppm", imageRGB1, &lignes, &colonnes, &maxval, &metadonnees);
	
    printf("-> Debut!\n");

	ppm_pivoter90(imageRGB1, &lignes, &colonnes, 0);
	
	printf("\n\nLIGNES: %d\nCOLONNES: %d\n\n", lignes, colonnes);
	
    printf("-> Fin!\n");

    return 0;
}
