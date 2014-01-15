//
//  rcpp_ExactSampling.cpp
//  kNN
//
//  Created by kai li on 29/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "rcpp_ExactSampling.h"


	// KNN  classification non pondere
void call_knn_NP_binaire(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	kNN_non_pondere myknn(M_P.Dn,*taille, *dimension, *knb, *pnb,err);
	*Risque = myknn.Prob_Risque;
}

	// // KNN  classification pondere
void call_knn_Pondere_binaire(double *l,double *label,double *weights,int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	V_to_M V_M(weights,*taille,*taille);
	double Seuil=0.;

	*Risque =	kNN_pondere(M_P.Dn,*taille,*dimension,*knb,*pnb,V_M.M,Seuil,err).Prob_Risque;
	}


	// kNN classification pondere avec la puissance
void call_knn_Puissance_binaire(double *l,double *label,double *Alpha, int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	double Seuil = 0.;
	*Risque =	kNN_pondere(M_P.Dn,*taille,*dimension,*knb,*pnb, *Alpha,Seuil,err).Prob_Risque;
}


	// kNN regression non pondere
void call_knn_NP_regression(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	*Risque = kNN_regression(M_P.Dn, *taille, *dimension, *knb, *pnb,err).Prob_Risque;
}


	// kNN regression pondere
void call_knn_P_regression(double *l,double *label,double * weigths,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	V_to_M V_M(weigths,*taille,*taille);
	*Risque = kNN_regression_pondere(M_P.Dn,V_M.M,*taille,*dimension,*knb,*pnb,err).Prob_Risque;
}

	// Bootstrap epsilon
void call_EBootstrap(double *l,double *label, int *taille, int *dimension, int *knb,double *epsilon, double *Risuqe,double *err)
{
	EpsilonBootstrap(l,label,taille,dimension,knb,epsilon,Risuqe, err);
}

	// les indices de plus proches voisins
void call_index(double *l, int *taille, int *dimension, int *knb, int *indexknn,double *ldist)
{
	make_points M_P(l,*taille,*dimension);
  indice(*dimension, *taille, 0 , M_P.Dn, *knb,indexknn,ldist);
}

	//     Domaine de fonctions empiriques

	// KNN  classification non pondere
void call_knn_NP_binaire_emp(double *l,double *label,int *taille,int *dimension,int *knb,double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, NULL, 0.);
	knn_emp.kNN_empirique_calcule_risque_NPC();
	knn_emp.Errors(err);
	*Risque = knn_emp.Prob_Risque;
}

	// // KNN  classification pondere
void call_knn_Pondere_binaire_emp(double *l,double *label,double *weights,int *taille,int *dimension,int *knb,double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	V_to_M V_M(weights,*taille,*taille);
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, V_M.M,0.);
	knn_emp.kNN_empirique_calcule_risque_PC();
	knn_emp.Errors(err);
	*Risque =	knn_emp.Prob_Risque;
}


	// kNN classification pondere avec la puissance
void call_knn_Puissance_binaire_emp(double *l,double *label,double *Alpha, int *taille,int *dimension,int *knb,double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, NULL, *Alpha);
	knn_emp.kNN_empirique_calcule_risque_PC();
	knn_emp.Errors(err);
	*Risque =	knn_emp.Prob_Risque;
}


	// kNN regression non pondere
void call_knn_NP_regression_emp(double *l,double *label,int *taille,int *dimension,int *knb,  double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, NULL,0.);
	knn_emp.kNN_empirique_calcule_risque_NPR();
	knn_emp.Errors(err);
	*Risque =	knn_emp.Prob_Risque;
}


	// kNN regression pondere
void call_knn_P_regression_emp(double *l,double *label,double *weigths,int *taille,int *dimension,int *knb, double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	V_to_M V_M(weigths,*taille,*taille);
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, V_M.M, 0.);
	knn_emp.kNN_empirique_calcule_risque_PR();
	knn_emp.Errors(err);
	*Risque =	knn_emp.Prob_Risque;
}

	// kNN regression pondere avec la puissance
void call_knn_Puissance_regression_emp(double *l,double *label,double *Alpha,int *taille,int *dimension,int *knb, double *Risque,double *err)
{
	make_points M_P(l,label,*taille,*dimension);
	double **weights;
	weights = NULL;
	kNN_empirique knn_emp(M_P.Dn, *taille,*dimension, *knb, weights, *Alpha);
	knn_emp.kNN_empirique_calcule_risque_PR();
	knn_emp.Errors(err);
	*Risque =	knn_emp.Prob_Risque;
}


