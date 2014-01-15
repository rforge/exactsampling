//
//  kNN_pondere.cpp
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "kNN_pondere.h"
#include "kNN_pondere_Weights.h"
#include <fstream>
kNN_pondere::kNN_pondere()
{
	nb_split = 0;
	nb_points = 0;
	dimension = 0;
	k_nb = 0;
	H = NULL;
	points_set = NULL;
	Prob_Risque = NULL;
	point_err = NULL;
}

	// méthode avec la puissance
kNN_pondere::kNN_pondere( point *l, int nb, int dim, int k, int p, double Alpha, double seuil, double *err)
{
	nb_split = p;
	nb_points = nb;
	points_set = l;
	dimension = dim;
	k_nb = k;
	point_err = new double[nb];
	
	H = new HyperGeometrique(nb_points);
	W = new double*[nb];
	for (int i = 0; i < nb; i++)
		W[i] = new double[nb];
	for (int i = 0; i < nb; i++)
		for (int j = 0; j < nb; j++)
			W[i][j] = 1. / Puissance(Distance(l[i], l[j], dimension), Alpha);
	s = seuil;
	
	// change la signe de l'éléments dans la matrice de poids si label est 0
	for (int i = 0; i < nb_points; i++)
		if (points_set[i].label == 0)
			for (int j = 0; j < nb_points; j++)
				W[j][i] = -W[j][i];
	
	//	construit KD tree
	arbre_kd= new KD_tree(dimension,nb_points,0,points_set);
	arbre_kd->search_neighbors_KD(l, k_nb + nb_split - 1);
  double *newW = new double[k_nb + nb_split - 1];
  for (int i = 0; i < nb_points; i++)
  {
    for (int j = 0; j < k_nb + nb_split - 1; j++)
      newW[j] = W[i][arbre_kd->point_search[i].neighbors[j]->index];
    for (int j = 0; j < k_nb + nb_split - 1; j++)
      W[i][j] = newW[j];
  }
  delete[] newW;
	calcule_erreur();
	for (int i = 0; i < nb; i++) {
		err[i] = point_err[i];
	}
}

	//initialise  méthode sans la puissance
kNN_pondere::kNN_pondere( point *l, int nb,int dim,int k, int p, double **weights, double seuil,double *err)
{
	nb_split = p;
	nb_points = nb;
	points_set = l;
	dimension = dim;
	k_nb = k;
	point_err = new double[nb];

	H = new HyperGeometrique(nb_points);
	W = new double*[nb];
	for (int i = 0; i < nb; i++)
		W[i] = new double[nb];
	for (int i = 0; i < nb; i++)
		for (int j = 0; j < nb; j++)
			W[i][j] = weights[i][j];
	s = seuil;

		// change la signe de l'éléments dans la matrice de poids si label est 0
	for (int i = 0; i < nb_points; i++)
		if (points_set[i].label == 0)
			for (int j = 0; j < nb_points; j++)
				W[j][i] = -W[j][i];

		//	construit KD tree
	arbre_kd= new KD_tree(dimension,nb_points,0,points_set);
	arbre_kd->search_neighbors_KD(l, k_nb + nb_split - 1);
  double *newW = new double[k_nb + nb_split - 1];
  for (int i = 0; i < nb_points; i++)
  {
    for (int j = 0; j < k_nb + nb_split - 1; j++)
      newW[j] = W[i][arbre_kd->point_search[i].neighbors[j]->index];
    for (int j = 0; j < k_nb + nb_split - 1; j++)
      W[i][j] = newW[j];
  }
  delete[] newW;
  
	calcule_erreur();
	for (int i = 0; i < nb; i++) {
		err[i] = point_err[i];
	}

}


kNN_pondere::~kNN_pondere()
{
	if (H != NULL) {
		delete H;
		delete arbre_kd;
	}
	if (W!=NULL){
		for (int i = 0; i < nb_points; i++) {
			delete [] W[i];
		}
		delete [] W;
	}
	if (point_err != NULL) {
		delete point_err;
	}
}

	// calcule le taux d'erreur sans la puissance
void kNN_pondere::calcule_erreur()
{
    // Prob_A1 = P(i € valide)  ; Prob_i_v = sum de P ( Vj = j | i € V ) de j = k à k + p - 1
	Prob_Risque = 0;
	double R;
	double P_A2[nb_split];
	int index = 0;
	for (int j = k_nb ; j <= k_nb + nb_split - 1 ; j++)
	{
		double u1 =  1. / j;
		double u2 = u1 * k_nb;
		P_A2[index] = H->calcule(j , nb_points - j  - 1, nb_split - 1 ,j - k_nb) * u2 ;
		index++;
	}

	for (int i = 0; i < nb_points; i++)
	{
		R = erreur_total(i,P_A2);
		point_err[i] = R ;//* (1. * nb_split) / nb_points;
		Prob_Risque = Prob_Risque +  R;
	}
	Prob_Risque = 1./ nb_points * Prob_Risque ;
}

  // calcule le taux d'erreur sans la puissance
double kNN_pondere::erreur_total(int index,double *P_A2)
{
	double seuil = 0;
	double e = 0, P_A3;
	for (int j = k_nb - 1  ; j <= k_nb + nb_split - 2 ; j++)
	{
		kNN_pondere_Weights kNNPW(j, k_nb - 1, W, seuil - W[index][j]);
		long double NbW = kNNPW.NumComb_GeneralWeightsGreaterThan(index);
    long double NBW2 = kNNPW.NumComb_GeneralWeightsEqual(index);
    // EQUAL cases are taken into account here.
		long double P_A3_pos = (NbW + 0.5 * NBW2) / kNNPW.Binom(j, k_nb - 1);
    P_A3 = P_A3_pos * (1 - points_set[index].label) + (1 - P_A3_pos ) * points_set[index].label;
		e = e + P_A2[j - k_nb + 1] * P_A3;
		
	}
	return e;
}


