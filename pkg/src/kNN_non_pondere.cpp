//
//  kNN_non_pondere.cpp
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "kNN_non_pondere.h"

kNN_non_pondere::kNN_non_pondere()
{
	nb_split = 0;
	nb_points = 0;
	dimension = 0;
	k_nb = 0;
	H = NULL;
	points_set = NULL;
	Prob_Risque = NULL;
	point_err=NULL;
}

	//initialise
kNN_non_pondere::kNN_non_pondere(point *l, int nb,int d,int k, int p,double *err)
{
	nb_split = p;
	nb_points = nb;
	points_set = l;
	dimension = d;
	k_nb = k;
	H = new HyperGeometrique(nb_points);
	point_err = new double[nb];
	
		//	construit KD tree
	arbre_kd= new KD_tree(dimension,nb_points,0,points_set);
	arbre_kd->search_neighbors_KD(l, k_nb + nb_split - 1);
	calcule_erreur();
	for (int i = 0; i < nb; i++) {
		err[i] = point_err[i];
	}
}


kNN_non_pondere::~kNN_non_pondere()
{
	if (H != NULL) {
		delete H;
		delete arbre_kd;
	}
	if (point_err!=NULL) {
		delete point_err;
	}
}


void kNN_non_pondere::calcule_erreur()
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
		point_err[i] = R ;//* (nb_split * 1.); // risque pour chaque observation
		Prob_Risque = Prob_Risque +  R;
	}
	Prob_Risque = 1./ nb_points * Prob_Risque ;
}


double kNN_non_pondere::erreur_total(int index,double *P_A2)
{
	int nb_0 = 0,nb_1 = 0;
	double e = 0, P_A3;
	for (int i = 0; i < k_nb - 1; i++)
	{
		if (arbre_kd->point_search[index].neighbors[i]->label == 1)
			nb_1 ++;
		else
			nb_0++;
	}
	
	for (int j = k_nb  ; j <= k_nb + nb_split - 1 ; j++)
	{
		if (arbre_kd->point_search[index].neighbors[j - 1]->label == 1)
			nb_1++;
		else
			nb_0++;
		
		if ( k_nb % 2 != 0)
			_k_impaire(index,j,nb_0,nb_1,P_A3);
		else
			_k_paire(index,j,nb_0,nb_1,P_A3);
	
		e = e + P_A2[j - k_nb] * P_A3;
		
	}
	return e;
}

	// si k est impaire
void kNN_non_pondere::_k_impaire(int index,int index_j,int n0,int n1,double &P)
{
		//Cas 1
	if (arbre_kd->point_search[index].Point->label == 0)
	{
			//		P = 1 - H->repartition(n1, index_j - n1, k_nb, k_nb / 2 );
		if (arbre_kd->point_search[index].neighbors[index_j - 1]->label == 0 )
		{
			P = 1 - H->repartition(n1,index_j - 1 - n1, k_nb - 1,k_nb / 2 );
		}
		else
		{
			P = 1 - H->repartition(n1 - 1, index_j - n1, k_nb - 1, k_nb / 2 - 1);
		}
	}
	else
	{
		
			//		P = 1 - H->repartition(n0, index_j - n0, k_nb, k_nb / 2 );
		if (arbre_kd->point_search[index].neighbors[index_j - 1]->label == 0)
		{
			P = 1 - H->repartition(n0 - 1,index_j - n0, k_nb - 1,k_nb / 2 -1);
		}
		else
		{
			P = 1 - H->repartition( n0, index_j - n0 - 1 , k_nb - 1,k_nb / 2  );
		}
	}
}

// si k est paire.
void kNN_non_pondere::_k_paire(int index,int index_j,int n0,int n1,double & p)
{
	if (n0 == n1)
		p = 0.5 * H->calcule(n0, n1, k_nb, k_nb / 2);
	else
	{
		if (arbre_kd->point_search[index].Point->label == 0)
		{
			if (arbre_kd->point_search[index].neighbors[index_j - 1]->label == 0)
				p = 1 - H->repartition(n1, index_j - 1 - n1, k_nb - 1, k_nb / 2);
			else
				p = 1 - H->repartition(n1 - 1, index_j - n1, k_nb - 1, k_nb / 2 - 1);
		}
		else
		{
			if (arbre_kd->point_search[index].neighbors[index_j - 1]->label == 0)
				p = 1 - H->repartition(n0 - 1, index_j - n1, k_nb - 1, k_nb / 2 -1 );
			else
				p = 1 - H->repartition(n0, index_j - n0, k_nb - 1, k_nb / 2);
		}
	}
}
