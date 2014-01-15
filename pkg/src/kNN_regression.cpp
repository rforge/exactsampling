//
//  kNN_regression.cpp
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "kNN_regression.h"


kNN_regression::kNN_regression()
{
	kd = NULL;
	H = NULL;
	C = NULL;
	k = p = 0;
	Prob_Risque = 0;
	point_err = NULL;
}

kNN_regression::kNN_regression(point *mpt,int t, int d, int k_nb,int p_nb,double *err)
{
	k = k_nb;
	p = p_nb;
	Prob_Risque = 0;
	point_err = new double[t];
	
	kd = new KD_tree(d, t, 0, mpt);
	kd->search_neighbors_KD(mpt, k + p - 1);
	C = new Combinaison_N_P(t);
	H = new HyperGeometrique(t);

	calcul_risque();

	for (int i = 0; i < t; i++) {
		err[i] = point_err[i];
	}

}

kNN_regression::~kNN_regression()
{
	if (kd != NULL) {
		delete kd;
	}
	if (C != NULL) {
		delete C;
	}
	if (H != NULL) {
		delete H;
	}
	if (point_err != NULL) {
		delete point_err;
	}
}

void kNN_regression::calcul_risque()
{
	int n = kd->data->taille;
	double P_H_l[p];
	
		//	 create list de la probabilité de P(H_l = l - k )
	for (int j = k; j <= k + p - 1; j++)
	{
		P_H_l[j - k] = H->calcule(j, n - j - 1, p - 1, j - k);
	}
	
	double somme = 0;
	double Y_l = 0 , Y_l_i_1 = 0, Y_l_m = 0, Y_l_i_2 = 0, Y_l_i_3 = 0;
	double A1 = 0, A2 = 0, A3 = 0;
	double A1_1 = 0, A1_2 = 0;
	double A2_1 = 0, A2_2 = 0, A2_3 = 0;
	double A3_1 = 0, A3_2 =0;
	
	for (int i = 0 ; i < n; i++)
	{
		Y_l = pow(kd->point_search[i].Point->label,2);
		
			// partie A1
		for (int l = 1; l <= k + p - 1; l++)
		{
			Y_l_i_1 = pow(kd->point_search[i].neighbors[l - 1]->label, 2);
			if (l >= k)
				A1_1 = 1. / l * P_H_l[l - k];
			else
				A1_1 = 0;
			for (int j = k; j <= k + p - 1; j++)
			{
				if (j > l )
					A1_2 += 1. / j * H->calcule(j, n - j - 1, p - 1, j - k) * (k - 1.) / ( j - 1.);
				else
					A1_2 += 0;
			}
			A1 += Y_l_i_1 * (A1_1 + A1_2);
			A1_2 = 0;
		}
		A1 = 1. / k * A1;
	
			//partie A2
		for (int j = k; j <= k + p - 1; j++)
		{
			for (int l = 1; l <= k + p - 2; l++)
			{
				Y_l_i_2 = kd->point_search[i].neighbors[l - 1 ]->label;
				for (int m = l + 1; m <= k + p - 1; m++)
				{
					Y_l_m = kd->point_search[i].neighbors[m - 1]->label;
					if ( m == j)
						A2_3 += Y_l_m * (k - 1.) / (j - 1.);
					else
						if (m < j)
							A2_3 += Y_l_m * (k - 1.) * (k - 2.) / ((j - 1.)* (j - 2.));
				}
				A2_2 += Y_l_i_2 * A2_3;
				A2_3 = 0;
			}
			A2_1 +=  1. / j * H->calcule(j, n - j - 1, p - 1, j - k) * A2_2;
			A2_2 = 0;
		}
		A2 = 2. / k * A2_1;
		A2_1 = 0;
		
			//partie A3
		for (int l = 1; l <= k + p - 1; l++)
		{
			Y_l_i_3 = kd->point_search[i].neighbors[l - 1]->label;
			if (l >= k )
				A3_1 = 1. / l * P_H_l[l - k];
			else
				A3_1 = 0;
			for (int j = k; j <= k + p - 1; j++)
			{
				if ( j > l)
					A3_2 += 1. / j * H->calcule(j, n - j - 1, p - 1, j - k)* ( k - 1. ) / (j - 1.);
			}
			A3 += Y_l_i_3 * ( A3_1 + A3_2);
			A3_1 = A3_2 = 0;
		}
		A3 = 2 * kd->point_search[i].Point->label * A3;
		point_err[i] = double (Y_l + A1 + A2 - A3) ; // erreur pour chaque obervation
		somme += Y_l + A1 + A2 - A3;
		
		Y_l = 0 , Y_l_i_1 = 0, Y_l_m = 0, Y_l_i_2 = 0, Y_l_i_3 = 0;
		A1_1 = 0, A1_2 = 0;
		A2_1 = 0, A2_2 = 0, A2_3 = 0;
		A3_1 = 0, A3_2 =0;
		A1 = A2 = A3 = 0;
	}
	
	Prob_Risque = 1. / n * somme;
}
