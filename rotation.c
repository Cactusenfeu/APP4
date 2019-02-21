/* ????!?!!?!?!?????????*/

#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];


int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0;
	FILE *flot_entree;
	
	//strcpy(nom_fichier, nom_fichier.txt);
	
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
			if (p[1] != '2'){
				printf("ERREUR3");
				return -3;
			}
		}
		if (premiere[0] == 'P'){
			printf("%s", premiere);
			fscanf(flot_entree, "%[^\n]", p);
			printf("%s\n", p);
			if (p[0] != '2'){
				printf("ERREUR3");
				return -3;
			}
		}
		
			fscanf(flot_entree, "%d %d %d", &b, &c, &d);
			printf("%d %d\n%d\n", b, c, d);
			p_lignes = &b;
			p_colonnes = &c;
			p_maxval = &d;
			if (b>256 || c>256){
				printf("ERREUR2");
				return -2;
			}
			int e=0;
			for (int i=0; i<b; i++){
				for (int j=0; j<c; j++){
					fscanf(flot_entree, "%d", &e);
					matrice[i][j] = e;
			
				}	
			}
	
	}
	
    return OK;
}

int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens){
	
	int matrice_temp[MAX_HAUTEUR][MAX_LARGEUR];
	
	if (sens==0){
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[j][i] = matrice[i][j];
			}
		}
	}
	
	if (sens==1){
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[*p_colonnes-j-1][*p_lignes-i-1] = matrice[i][j];
			}
		}
	}
	
	for (int i=0; i<*p_colonnes; i++){
		for (int j=0; j<*p_lignes; j++){
			printf("%d ", matrice_temp[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int main()
{
    int lignes=2, colonnes=3;
    //int maxval;
    //struct MetaData metadonnees;
    int retour;
	
	int matrice1[MAX_HAUTEUR][MAX_LARGEUR] = {{1,1,1}, {2,2,2}};
	
    printf("-> Debut!\n");

	retour = pgm_pivoter90(matrice1, &lignes, &colonnes, 1);
	
    printf("-> Fin!\n");

    return 0;
}
