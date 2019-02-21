#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

#define LM 3
#define CM 3

int mr[MAX_HAUTEUR][MAX_LARGEUR]={{1,2,3},{4,5,6},{7,8,9}};

int pgm_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
int lignes, int colonnes, int maxval){
	
			for (int l=0;l<lignes;l++){
				for (int c=0;c<colonnes;c++){
					matrice[l][c]=maxval-matrice[l][c];
					if(matrice[l][c]>maxval){
						return maxval;
					}
					printf( "%d\t", matrice[l][c]);
				}
			printf("\n");	
			}
			return OK;
}
	

int main(){
	int retour=pgm_negatif(mr,3, 3, 255);
	printf("%d", retour);
	return 0;
}

