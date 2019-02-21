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
	//printf("%d %d %d", matrice.valeurR, matrice.valeurG, matrice.valeurB);
    return OK;
}



int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], 
						int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR]
						[MAX_LARGEUR], int lignes2, int colonnes2){

	if (lignes1 != lignes2 || colonnes1 != colonnes2){
		printf("erreur");
		return -1;
	}
	
	for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			if (matrice1[i][j].valeurR != matrice2[i][j].valeurR || matrice1[i][j].valeurG != matrice2[i][j].valeurG
			|| matrice1[i][j].valeurB != matrice2[i][j].valeurB){
				printf("diff");
				return 0;
			}
		}
	}
	printf("pareil");
	return 1;
	
}

int main()
{
    int lignes1, colonnes1, lignes2, colonnes2;
    int maxval1, maxval2;
    struct MetaData metadonnees;
    int retour;
	
	retour = ppm_lire("Sherbrooke_Frontenac_nuit.ppm", imageRGB1, 
                      &lignes1, &colonnes1, 
                      &maxval1, &metadonnees);
                      
	retour = ppm_lire("ecrire.ppm", imageRGB2, 
                      &lignes2, &colonnes2, 
                      &maxval2, &metadonnees);
                      
    printf("-> Debut!\n");

	ppm_sont_identiques(imageRGB1, lignes1, colonnes1, imageRGB2, 
							lignes2, colonnes2);
	
    printf("-> Fin!\n");

    return 0;
}
