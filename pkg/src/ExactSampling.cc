	//
	//  ExactSampling.cc
	//  kNN
	//
	//  Created by kai li on 29/08/12.
	//  Copyright (c) 2012 kai li. All rights reserved.
	//

#include "rcpp_ExactSampling.h"
 
extern "C"
{
		// KNN  classification non pondere
	void knn_NP_binaire(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
	{
		call_knn_NP_binaire(l,label,taille,dimension,knb,pnb,Risque,err);
	}
		// // KNN  classification pondere
	void knn_Pondere_binaire(double *l,double *label,double *weights,int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err)
	{
		call_knn_Pondere_binaire(l,label,weights,taille,dimension,knb,pnb,Risque,err);
	}

		// kNN classification pondere avec la puissance
	void knn_Puissance_binaire(double *l,double *label, double *Aplha,int *taille,int *dimension,int *knb, int *pnb,double *Risque,double *err)
	{
		call_knn_Puissance_binaire(l,label,Aplha, taille,dimension,knb,pnb,Risque,err);
	}

		// kNN regression non pondere
	void knn_NP_regression(double *l,double *label,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
	{
		call_knn_NP_regression(l,label,taille,dimension,knb,pnb,Risque,err);
	}

		// kNN regression pondere
	void knn_P_regression(double *l,double *label,double * weigths,int *taille,int *dimension,int *knb, int *pnb, double *Risque,double *err)
	{
		call_knn_P_regression(l,label,weigths,taille,dimension,knb,pnb,Risque,err);
	}

		// Bootstrap Epsion
	void EBootstrap(double *l, double *label, int *taille, int *dimension, int *knb,double *eps, double *Risuqe, double *err)
	{
		call_EBootstrap(l,label,taille,dimension,knb,eps,Risuqe,err);
	}

		// affichage les index knn
	void knn_index(double *l, int *taille, int *dimension, int *kn, int *lindex,double *ldist)
	{
		call_index(l, taille, dimension,kn,lindex,ldist);
	}



		// domaine des fonctions empiriques
		// KNN  classification non pondere empirique
	void knn_NP_binaire_emp(double *l,double *label,int *taille,int *dimension,int *knb, double *Risque,double *err)
	{
		call_knn_NP_binaire_emp(l,label,taille,dimension,knb,Risque,err);
	}

		// // KNN  classification pondere empirique
	void knn_Pondere_binaire_emp(double *l,double *label,double *weights,int *taille,int *dimension,int *knb, double *Risque,double *err)
	{
		call_knn_Pondere_binaire_emp(l,label,weights,taille,dimension,knb,Risque,err);
	}

		// kNN classification pondere avec la puissance empirique
	void knn_Puissance_binaire_emp(double *l,double *label, double *Aplha,int *taille,int *dimension,int *knb,double *Risque,double *err)
	{
		call_knn_Puissance_binaire_emp(l,label,Aplha, taille,dimension,knb,Risque,err);
	}

		// kNN regression non pondere empirique
	void knn_NP_regression_emp(double *l,double *label,int *taille,int *dimension,int *knb,  double *Risque, double *err)
	{
		call_knn_NP_regression_emp(l,label,taille,dimension,knb,Risque,err);
	}

		// kNN regression pondere empirique
	void knn_P_regression_emp(double *l,double *label,double * weigths,int *taille,int *dimension,int *knb,double *Risque,double *err)
	{
		call_knn_P_regression_emp(l,label,weigths,taille,dimension,knb,Risque,err);
	}

		// kNN regression pondere empirique avec la puissance
 	void knn_Puissance_regression_emp(double *l,double *label,double *Alpha,int *taille,int *dimension,int *knb,double *Risque,double *err)
	{
		call_knn_Puissance_regression_emp(l,label,Alpha,taille,dimension,knb,Risque,err);
	}

}

