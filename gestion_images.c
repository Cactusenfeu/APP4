/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"
#include "AutoValidation.h"


int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
	 //AutoValidation();
     test_pgm_lire();
	 //test_pgm_ecrire();
	 //***test_pgm_copier();
	 //***test_pgm_couleur_preponderante();
	 //***test_pgm_creer_histogramme();
	 //***test_pgm_eclaircir_noircir();
	 //***test_pgm_creer_negatif();
	 //***test_pgm_extraire();
	 //***test_pgm_sont_identiques();
	 //***test_pgm_pivoter90();

	 //test_ppm_lire();
	 // test_ppm_ecrire();
	 //***test_ppm_copier();
	 //***test_ppm_sont_identiques();
	 //***test_ppm_pivoter90();

    return 0;
}

