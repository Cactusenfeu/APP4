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
             int *p_maxval, struct MetaData *p_metadonnees){
	
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0;
	FILE *flot_entree;
	
	//strcpy(nom_fichier, "test.txt");
	
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

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
			  int lignes, int colonnes, int maxval, struct MetaData metadonnees){
	
	FILE *flot_ecrire;
	
	flot_ecrire = fopen(nom_fichier, "w");
	
	if(flot_ecrire == NULL){
		printf("Erreur d’ouverture de fichier.\n");
	}
	 
	else{
		fprintf(flot_ecrire, "# %s\n", metadonnees);		
		
		fprintf(flot_ecrire, "P2\n");
		
		fprintf(flot_ecrire, "%d %d \n%d\n", lignes, colonnes, maxval);
		
		for (int i=0; i<lignes; i++){
			for (int j=0; j<colonnes; j++){
				fprintf(flot_ecrire, "%d ", matrice[i][j]);
			}
			fprintf(flot_ecrire, "\n");
		}
		
	}
	
    return OK;
}




int main()
{
    int lignes1, colonnes1;
    int maxval;
    struct MetaData metadonnees;
    int retour;

    printf("-> Debut!\n");

	retour = pgm_lire("Sherbrooke_Frontenac_nuit.pgm", image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
                      
    
	retour = pgm_ecrire("ecrire.txt", image1, 
                      lignes1, colonnes1, 
                      maxval, metadonnees);
	
    printf("-> Fin!\n");

    return 0;
}

