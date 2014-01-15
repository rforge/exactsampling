//
//  kNN_non_pondere.h
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef kNN_kNN_pondere_h
#define kNN_kNN_pondere_h

#include "point.h"
#include "KD_tree.h"
#include "Combinaison_N_P.h"
#include "HyperGeometrique.h"
#include "GeneralFunctions.h"

class Combinaison_N_P;

class kNN_pondere
{
public:
	point *points_set;
	KD_tree *arbre_kd;
	HyperGeometrique *H;
	
	int k_nb;
	int dimension;
	int nb_split;  // combinaision nb_split parmi nb_points
	int nb_points;
	double seuil;
	double **W;
	double s;
	double Prob_Risque; // le risque
	double *point_err;
	
	kNN_pondere();
	
	kNN_pondere( point *l, int nb, int dimension, int k, int p, double **weights, double seuil, double *err);
	
	kNN_pondere( point *l, int nb, int dimension, int k, int p, double Alpha, double seuil, double *err);
	
	int **Search(int NbN); // NbNeighbours, X numeriques
	int *Empiric(bool Classification, double **W = NULL, double alpha = 0, double seuil = 0); // Sinon classification alors regression
	long double *CV(int p, bool Classification, double **W = NULL, double alpha = 0, double seuil = 0); // Taux d'erreur puis tax d'erreur par individu
	long double boot(int k, double epsilon); // Classification = true, epsilon in 0,1 taux d'erreur par bootstrap puis par individu puis min et max si epsilon > 0 
	

	~kNN_pondere();
	
		//	calcule l'erreur
	void calcule_erreur();
	double erreur_total(int index, double *);
		//	verifier le resultat
};




#endif
