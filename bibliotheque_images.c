/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"


int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees){
				 
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0, pv=0, position=0;
	FILE *flot_entree;
		
	flot_entree = fopen(nom_fichier, "r");
	
	if(flot_entree == NULL){
		//printf("Erreur d’ouverture de fichier.\n");
		return -1;
	}
	 
	else{		
		fscanf(flot_entree, "%c", premiere);
		
		if (premiere[0] != 'P' && premiere[0] != '#'){
			return -3;
		}
		if (premiere[0] == '#'){
			//printf("%s", premiere);
			
			for (int i=0; i<MAX_CHAINE; i++){
				fscanf(flot_entree, "%c", &a[i]);
				if (a[i] != ';' && a[i] != '\n'){
					if (pv == 0){
						p_metadonnees->auteur[i]= a[i];
					}
					if (pv == 1){
						p_metadonnees->dateCreation[i-position]= a[i];
					}
					if (pv == 2){
						p_metadonnees->lieuCreation[i-position] = a[i];
					}
					if (pv>2){
						return -1;
					}
				}
				if (a[i] == ';'){
					pv++;
					position = i;
				}
				if (a[i] == '\n' && pv != 2){
					return -1;
				}				
				if (a[i] == '\n' && pv == 2){
					i = MAX_CHAINE;
				}
			}
			
			fscanf(flot_entree, "%[^\n]", p);
			//printf("\n%s\n", p);
			if (p[0] != 'P'){
				return -3;
			}
			if (p[1] != '2'){
				//printf("ERREUR3");
				return -3;
			}
		}
		if (premiere[0] == 'P'){
			//printf("%s", premiere);
			fscanf(flot_entree, "%[^\n]", p);
			//printf("%s\n", p);
			if (p[0] != '2'){
				//printf("ERREUR3");
				return -3;
			}
		}
			fscanf(flot_entree, "%d", &b);
			fscanf(flot_entree, "%d", &c);
			fscanf(flot_entree, "%d", &d);
			//printf("%d %d\n%d\n", b, c, d);
			*p_lignes = b;
			*p_colonnes = c;
			*p_maxval = d;
			if (b>MAX_HAUTEUR || c>MAX_LARGEUR){
				//printf("ERREUR2");
				return -2;
			}
			if (d>255){
				return -3;
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

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees){
	
	FILE *flot_ecrire;
	
	flot_ecrire = fopen(nom_fichier, "w");
	
	if(flot_ecrire == NULL){
		//printf("Erreur d’ouverture de fichier.\n");
	}
	
	else{
		if (metadonnees.auteur[0] !='\0' || metadonnees.dateCreation[0] !='\0' || metadonnees.lieuCreation[0] !='\0'){
			fprintf(flot_ecrire, "#%s;%s;%s\n", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);		
		}
		
		fprintf(flot_ecrire, "P2\n");
		
		fprintf(flot_ecrire, "%d %d \n%d\n", lignes, colonnes, maxval);
		printf("%d %d \n%d\n", lignes, colonnes, maxval);
		
		for (int i=0; i<lignes; i++){
			for (int j=0; j<colonnes; j++){
				fprintf(flot_ecrire, "%d " ,matrice[i][j]);
			}
			//fprintf(flot_ecrire, "\n");
		}	
	}
    return OK;
}

int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens){
	
	if (sens != 0 && sens != 1){
		return ERREUR;
	}
	
	int matrice_temp[MAX_HAUTEUR][MAX_LARGEUR];
	//printf("\nORIGINALE: \n");
	
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			//printf("%d ", matrice[i][j]);
		}
		//printf("\n");
	}
	
	
	if (sens==0){
		//printf("\nSENS ANTI-HORAIRE\n");
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[*p_colonnes-j-1][i] = matrice[i][j];
			}
		}
	}
	
	if (sens==1){
		//printf("\nSENS HORAIRE\n");
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[j][*p_lignes-i-1] = matrice[i][j];
			}
		}
	}
	
	int temp = *p_lignes;
	*p_lignes = *p_colonnes;
	*p_colonnes = temp;
	
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			matrice[i][j] = matrice_temp[i][j];
		}
	}
	//printf("\nROTATION: \n");
	for (int i=0; i<*p_lignes; i++){
		for (int j=0; j<*p_colonnes; j++){
			//printf("%d ", matrice[i][j]);
		}
		//printf("\n");
	}
	return 0;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2){
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

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes){
	
	if (lignes1 > *p_lignes || lignes2 > *p_lignes || *p_lignes > MAX_HAUTEUR || colonnes1 > *p_colonnes || colonnes2 > *p_colonnes || *p_colonnes > MAX_LARGEUR || lignes1 < lignes2 || colonnes1 > colonnes2){
		//printf("erreur1");
		return -1;
	}
	
	
	*p_lignes = lignes2 - lignes1+1;
	*p_colonnes = colonnes2 - colonnes1+1;
	
	int a=0, b=0;
	for (int i=lignes1; i<=lignes2; i++){
		for (int j=colonnes1; j<=colonnes2; j++){
			matrice[a][b] = matrice[i][j];
			b++;
		}
		a++;
	}
	return 0;
}

int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2){
	if (lignes1 != lignes2 || colonnes1 != colonnes2){
		//printf("erreur");
		return -1;
	}
	
	for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			if (matrice1[i][j] != matrice2[i][j]){
				//printf("diff");
				return 1;
			}
		}
	}
	//printf("pareil");
	return 0;
	
}

int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR],int lignes, int colonnes){

	int occurence[MAX_VALEUR];
	int valeur_prep=0;
	
	for(int valeur=0; valeur<=MAX_VALEUR+1; valeur++){
		occurence[valeur]=0;
		for (int l=0;l<lignes;l++){
			for (int c=0;c<colonnes;c++){
				if(matrice[l][c]==valeur){
					occurence[valeur]+= 1;
					if (occurence[valeur] > occurence[valeur_prep]){
						occurence[valeur_prep] = occurence[valeur];
						valeur_prep=valeur;
					}
				}
			}
		}
	}
	//printf("%d\n", histogramme[valeur_prep]);
	return valeur_prep;
}

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur){
	if (lignes>MAX_HAUTEUR || colonnes>MAX_LARGEUR){
		return -1;
	}
	for (int l=0;l<lignes;l++){
		for (int c=0;c<colonnes;c++){
			matrice[l][c]=matrice[l][c]+valeur;
			if(matrice[l][c]>maxval){
				matrice[l][c] = maxval;
			}
			if(matrice[l][c]<0){
				matrice[l][c] = 0;
			}
			//printf( "%d\t", matrice[l][c]);
		}
	//printf("\n");	
	}
	return OK;
}

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1]){
	
	int occurence[MAX_VALEUR];
	int valeur_prep=0;
	
	for(int valeur=0; valeur<=MAX_VALEUR+1; valeur++){
		occurence[valeur]=0;
		for (int l=0;l<lignes;l++){
			for (int c=0;c<colonnes;c++){
				if(matrice[l][c]==valeur){
					histogramme[valeur]+= 1;
					occurence[valeur]+= 1;
					if (occurence[valeur] > occurence[valeur_prep]){
						occurence[valeur_prep] = occurence[valeur];
						valeur_prep=valeur;
						if (histogramme[valeur]!=occurence[valeur]){
							return ERREUR;
						}	
					}
				}
			}
		}
	}
	//printf("%d\n", histogramme[valeur_prep]);
	return 0;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval){
	
	for (int l=0;l<lignes;l++){
		for (int c=0;c<colonnes;c++){
			matrice[l][c]=maxval-matrice[l][c];
			if(matrice[l][c]>maxval){
				return ERREUR;
			}
			//printf( "%d\t", matrice[l][c]);
		}
		//printf("\n");	
	}
			return OK;
}



int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees){
	char premiere[MAX_CHAINE], a[MAX_CHAINE], p[3];
	int b=0, c=0, d=0, pv=0, position=0;
	FILE *flot_entree;
	
	flot_entree = fopen(nom_fichier, "r");
	
	if(flot_entree == NULL){
		//printf("Erreur d’ouverture de fichier.\n");
		return -1;
	}
	 
	else{		
		fscanf(flot_entree, "%c", premiere);
		if (premiere[0] != 'P' && premiere[0] != '#'){
			return -3;
		}
		if (premiere[0] == '#'){
			//printf("%s", premiere);
			
			for (int i=0; i<MAX_CHAINE; i++){
				fscanf(flot_entree, "%c", &a[i]);
				if (a[i] == ';'){
					pv++;
					position = i+1;
				}				
				if (a[i] == '\n'){
					i = MAX_CHAINE;
				}
				if (a[i] != ';' && a[i] != '\n'){
					if (pv == 0){
						p_metadonnees->auteur[i]= a[i];
					}
					if (pv == 1){
						p_metadonnees->dateCreation[i-position]= a[i];
					}
					if (pv == 2){
						p_metadonnees->lieuCreation[i-position] = a[i];
					}
					if (pv>2){
						return -1;
					}
				}
			}
			
			fscanf(flot_entree, "%[^\n]", p);
			//printf("\n%s\n", p);
			if (p[1] != '3'){
				//printf("ERREUR3");
				return -3;
			}
		}
		if (premiere[0] == 'P'){
			//printf("%s", premiere);
			fscanf(flot_entree, "%[^\n]", p);
			//printf("%s\n", p);
			if (p[0] != '3'){
				//printf("ERREUR3");
				return -3;
			}
		}
		
			fscanf(flot_entree, "%d %d %d", &b, &c, &d);
			printf("%d %d\n%d\n", b, c, d);
			*p_lignes = b;
			*p_colonnes = c;
			*p_maxval = d;
			if (b>MAX_HAUTEUR || c>MAX_LARGEUR){
				//printf("ERREUR2");
				return -2;
			}
			if (d>255){
				//printf("ERREUR3");
				return -3;
			}
			for (int i=0; i<b; i++){
				for (int j=0; j<c; j++){
					fscanf(flot_entree, "%d %d %d", &matrice[i][j].valeurR, &matrice[i][j].valeurG, &matrice[i][j].valeurB);
					//printf("%d %d %d", matrice[i][j].valeurR, matrice[i][j].valeurG, matrice[i][j].valeurB);
				}	
			}
	
	}
    return OK;
}

int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2){

	if (lignes1 != lignes2 || colonnes1 != colonnes2){
		//printf("erreur");
		return -1;
	}
	
	for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			if (matrice1[i][j].valeurR != matrice2[i][j].valeurR || matrice1[i][j].valeurG != matrice2[i][j].valeurG
			|| matrice1[i][j].valeurB != matrice2[i][j].valeurB){
				//printf("diff");
				return 1;
			}
		}
	}
	//printf("pareil");
	return 0;
	
}

int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees){
	
	FILE *flot_ecrire;
	
	flot_ecrire = fopen(nom_fichier, "w");
	
	if(flot_ecrire == NULL){
		//printf("Erreur d’ouverture de fichier.\n");
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

int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens){
	if (sens != 0 && sens != 1){
		return -1;
	}
	struct RGB matrice_temp[MAX_HAUTEUR][MAX_LARGEUR];
	
	if (sens==0){
		//printf("\nSENS ANTI-HORAIRE\n");
		for (int i=0; i<*p_lignes; i++){
			for (int j=0; j<*p_colonnes; j++){
				matrice_temp[*p_colonnes-j-1][i].valeurR = matrice[i][j].valeurR;
				matrice_temp[*p_colonnes-j-1][i].valeurG = matrice[i][j].valeurG;
				matrice_temp[*p_colonnes-j-1][i].valeurB = matrice[i][j].valeurB;
			}
		}
	}
	
	if (sens==1){
		//printf("\nSENS HORAIRE\n");
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
	return 0;
}

int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2){

	if (lignes1 > MAX_HAUTEUR && colonnes1 > MAX_LARGEUR){
		return -2;
	}
	
	*p_lignes2 = lignes1;
	*p_colonnes2 = colonnes1;
	
	for (int i=0; i<lignes1; i++){
		for (int j=0; j<colonnes1; j++){
			matrice2[i][j].valeurR = matrice1[i][j]. valeurR;
			matrice2[i][j].valeurG = matrice1[i][j]. valeurG;
			matrice2[i][j].valeurB = matrice1[i][j]. valeurB;
		}
	}
			
	return 0;
}
