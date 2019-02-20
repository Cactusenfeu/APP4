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

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, 
				int lignes2, int colonnes2, int *p_lignes, int *p_colonnes){
	if (lignes1 > MAX_HAUTEUR || lignes2 > MAX_HAUTEUR || colonnes1 > MAX_LARGEUR || colonnes2 > MAX_LARGEUR){
		printf("erreur1");
		return -2;
	}
	if (lignes1 > lignes2 || colonnes1 > colonnes2){
		printf("erreur2");
		return -2;
	}
	
	int hauteur = lignes2 - lignes1;
	int largeur = colonnes2 - colonnes1;
		
	*p_lignes = hauteur;
	*p_colonnes = largeur;
	
	for (int i=lignes1; i<lignes2; i++){
		for (int j=colonnes1; j<colonnes2; j++){
			matrice[i-lignes1][j-colonnes1] = matrice[i][j];
		}
	}
	for (int i=hauteur; i<MAX_HAUTEUR; i++){
		for (int j=0; j<MAX_LARGEUR; j++){
			matrice[i][j] = '\0';
		}
	}
	for (int j=largeur; j<MAX_LARGEUR; j++){
		for (int i=0; i<MAX_HAUTEUR; i++){
			matrice[i][j] = '\0';
		}
	}
	
	for (int i=0; i<hauteur; i++){
		for (int j=0; j<largeur; j++){
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

int main()
{
    int lignes10, colonnes10, lignes20, colonnes20, lignes1, colonnes1;
    int lignese, colonnese;
    int maxval;
    struct MetaData metadonnees;
    int retour;

    printf("-> Debut!\n");

	retour = pgm_lire("test.txt", image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
                      
	lignes20 = 5;
	colonnes20 = 10;
	lignes10 = 10;
	colonnes10 = 20;
	
	
	retour = pgm_extraire(image1, lignes20, colonnes20, lignes10, colonnes10,
						  &lignese, &colonnese);
						  
	printf("%d %d", lignese, colonnese);
	
    printf("-> Fin!\n");

    return 0;
}

