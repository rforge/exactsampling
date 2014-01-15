//
//  rcpp_ExactSampling.h
//  kNN
//
//  Created by kai li on 29/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef kNN_rcpp_ExactSampling_h
#define kNN_rcpp_ExactSampling_h


#include "kNN_non_pondere.h"
#include "kNN_pondere.h"
#include "kNN_regression.h"
#include "kNN_regression_pondere.h"
#include "kNN_empirique.h"
#include "vector_to_matrix.h"
#include "point.h"
#include "make_point.h"
#include "EpsilonBootstrap.h"
#include "indice.h"

	// KNN  classification non pondere
void call_knn_NP_binaire(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err);

	// // KNN  classification pondere
void call_knn_Pondere_binaire(double *l,double *label,double *weights,int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err);


	// kNN classification pondere avec la puissance
void call_knn_Puissance_binaire(double *l,double *label,double *Alpha,int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err);


	// kNN regression non pondere
void call_knn_NP_regression(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err);


	// kNN regression pondere
void call_knn_P_regression(double *l,double *label,double * weigths,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err);

	// Méthode Bootstrap
void call_EBootstrap(double *l,double *label, int *taille, int *dimension, int *knb,double *epsilon, double *Risuqe,double *err);

  // affiche les indice de plus proches voisins
void call_index(double *l, int *taille, int *dimension, int *knb,int *indexknn,double *ldist);

	// fonctions empiriques
	// KNN  classification non pondere
void call_knn_NP_binaire_emp(double *l,double *label,int *taille,int *dimension,int *knb,  double *Risque,double *err);

	// // KNN  classification pondere
void call_knn_Pondere_binaire_emp(double *l,double *label,double *weights,int *taille,int *dimension,int *knb, double *Risque,double *err);

	// kNN classification pondere avec la puissance
void call_knn_Puissance_binaire_emp(double *l,double *label,double *Alpha,int *taille,int *dimension,int *knb, double *Risque,double *err);


	// kNN regression non pondere
void call_knn_NP_regression_emp(double *l,double *label,int *taille,int *dimension,int *knb,  double *Risque,double *err);


	// kNN regression pondere
void call_knn_P_regression_emp(double *l,double *label,double * weigths,int *taille,int *dimension,int *knb,  double *Risque,double *err);

	// kNN regression avec la puissance
void call_knn_Puissance_regression_emp(double *l,double *label,double *Alpha,int *taille,int *dimension,int *knb, double *Risque,double *err);


#endif
