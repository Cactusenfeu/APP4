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
				struct MetaData *p_metadonnees);

int ppm_ecrire(char nom_fichier[], struct RGB 
			matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, 
			int maxval, struct MetaData metadonnees){
	
	FILE *flot_ecrire;
	
	flot_ecrire = fopen(nom_fichier, "w");
	
	if(flot_ecrire == NULL){
		printf("Erreur d’ouverture de fichier.\n");
	}
	
	else{
		if (metadonnees.auteur[0] !='\0' || metadonnees.dateCreation[0] !='\0' || metadonnees.lieuCreation[0] !='\0'){
			fprintf(flot_ecrire, "#%s ;%s ;%s\n", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
		}		
		
		fprintf(flot_ecrire, "P3\n");
		
		fprintf(flot_ecrire, "%d %d \n%d\n", lignes, colonnes, maxval);
		
		for (int i=0; i<lignes; i++){
			for (int j=0; j<colonnes; j++){
				fprintf(flot_ecrire, "%d ", matrice[i][j].valeurR);
				fprintf(flot_ecrire, "%d ", matrice[i][j].valeurG);
				fprintf(flot_ecrire, "%d ", matrice[i][j].valeurB);
			}
			fprintf(flot_ecrire, "\n");
		}
		
	}
	
    return OK;
}




int main()
{
    int lignes1=256, colonnes1=192;
    int maxval;
    struct MetaData metadonnees;
    int retour;

    printf("-> Debut!\n");

	retour = ppm_lire("Sherbrooke_Frontenac_nuit.ppm", imageRGB1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);                
    
	retour = ppm_ecrire("test.ppm", imageRGB1, lignes1, colonnes1, 
						maxval, metadonnees);
	
    printf("-> Fin!\n");

    return 0;
}

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], 
				int *p_lignes, int *p_colonnes, int *p_maxval, 
				struct MetaData *p_metadonnees)
{
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0, pv=0, position=0;
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
				if (a[i] != ';' && a[i] != '\n'){
					if (pv == 0){
						p_metadonnees->auteur[i]= a[i];
					}
					if (pv == 1){
						p_metadonnees->dateCreation[i-position-1]= a[i];
					}
					if (pv == 2){
						p_metadonnees->lieuCreation[i-position-1] = a[i];
					}
					if (pv>2){
						return -1;
					}
				}
				if (a[i] == ';'){
					pv++;
					position = i;
				}				
				if (a[i] == '\n'){
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
