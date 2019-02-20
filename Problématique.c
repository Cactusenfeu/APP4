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
	char premiere[MAX_CHAINE];
	int b=0, c=0, d=0;
	char hashtag = {'#'};
	char p2 = {'P', '2'};
	char p3 = {'P','3'};
	FILE *flot_entree;
	
	strcpy(nom_fichier, "test.txt");
	
	flot_entree = fopen(nom_fichier, "r");
	
	if(flot_entree == NULL){
		printf("Erreur d’ouverture de fichier.\n");
	}
	 
	else{
		fscanf(flot_entree, "%c", premiere);
		if (strcmp(premiere,&hashtag) != 0){
			printf("#METADONNEES");
		}
		if (strcmp(premiere,&p2) != 0 || strcmp(premiere,&p3) != 0){
			printf("%s\n", premiere);
		}
		
			fscanf(flot_entree, "%d %d %d", &b, &c, &d);
			printf("%d %d\n%d\n", b, c, d);
			p_lignes = &b;
			p_colonnes = &c;
			p_maxval = &d;
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
    int maxval;
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;
    int retour;

    printf("-> Debut!\n");

	retour = pgm_lire(nom, image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
	
    printf("-> Fin!\n");

    return 0;
}

