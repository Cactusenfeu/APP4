/* ????!?!!?!?!?????????*/

#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, 
			   int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2){
	if (lignes1 > MAX_HAUTEUR || colonnes1 > MAX_LARGEUR){
		return -2;
	}
	
	*p_lignes2 = lignes1;
	*p_colonnes2 = colonnes1;
	
	for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			matrice2[i][j] = matrice1[i][j];
		}
	}
	return 0;
}

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees){
	
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
			//printf("%s", premiere);
			
			for (int i=0; i<MAX_CHAINE; i++){
				fscanf(flot_entree, "%c", &a[i]);
				if (a[i] != '\n'){
					//printf("%c", a[i]);
				}
				else{
					i = MAX_CHAINE;
				}
			}
			fscanf(flot_entree, "%[^\n]", p);
			//printf("\n%s\n", p);
			if (p[1] != '2'){
				printf("ERREUR3");
				return -3;
			}
		}
		if (premiere[0] == 'P'){
			//printf("%s", premiere);
			fscanf(flot_entree, "%[^\n]", p);
			//printf("%s\n", p);
			if (p[0] != '2'){
				printf("ERREUR3");
				return -3;
			}
		}
		
			fscanf(flot_entree, "%d %d %d", &b, &c, &d);
			//printf("%d %d\n%d\n", b, c, d);
			*p_lignes = b;
			*p_colonnes = c;
			*p_maxval = d;
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




int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    struct MetaData metadonnees;
    int retour;

    printf("-> Debut!\n");

	retour = pgm_lire("Sherbrooke_Frontenac_nuit.pgm", image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
                      
    retour = pgm_copier(image1, lignes1, colonnes1, image2, &lignes2, &colonnes2);
    
    for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			printf("%d", image2[i][j]);
		}
	}
					
    printf("-> Fin!\n");

    return 0;
}



