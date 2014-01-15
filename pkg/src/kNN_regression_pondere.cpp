//
//  kNN_regression_pondere.cpp
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "kNN_regression_pondere.h"

#include "kNN_regression_pondere.h"


kNN_regression_pondere::kNN_regression_pondere()
{
	k = p = 0;
	kd = NULL;
	C = NULL;
	H = NULL;
	Matrix_weights = NULL;
	Prob_Risque = 0;
	point_err = NULL;
}

kNN_regression_pondere::kNN_regression_pondere(point *mpt, double **matrix_poids,int taille,int dimension,int k_nb, int p_nb, double *err)
{
	k = k_nb;
	p = p_nb;
	point_err = new double[taille];
	Matrix_weights = matrix_poids;
	kd = new KD_tree( dimension, taille, 0, mpt);
	kd->search_neighbors_KD( mpt, k + p - 1);
	C = NULL;
	H = new HyperGeometrique(taille);

	calcul_Risque();

	for (int i = 0; i < taille; i++) {
		err[i] = point_err[i];
	}

}

kNN_regression_pondere::~kNN_regression_pondere()
{
	if (kd != NULL) {
		delete kd;
	}
	if (point_err != NULL) {
		delete point_err;
	}
	if (H != NULL) {
		delete H;
	}
}

void kNN_regression_pondere::calcul_Risque()
{
	int n = kd->data->taille;
	double A1 = 0, A2 = 0, A3 = 0, A4 = 0, somme = 0;
	double A2_1, A2_2, A2_3;
	double A3_1, A3_2, A3_3, A3_3_1,A3_3_2;
	double A4_1, A4_2_1,A4_2_2;
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		A1 = 0, A2 = 0, A3 = 0, A4 = 0;
		
			//	partie A1
		A1 = pow(kd->point_search[i].Point->label,2);
		
			//		partie A2
		for (int l = 1; l <= k + p - 1; l++)
		{
			index = kd->point_search[i].neighbors[l - 1]->index;
			A2_1 = pow(kd->point_search[i].neighbors[l - 1]->label, 2) * pow(Matrix_weights[i][index], 2);//pow(Matrix_weights[i][kd->point_search[i].neighbors[l - 1]->index], 2)
			if (l >= k )
				A2_2 = 1. / l * H->calcule(l, n - 1 - l, p - 1, l - k );
			else
				A2_2 = 0;
			for (int j = k; j <= k + p - 1 ; j++)
			{
				if (j > l)
					A2_3 += 1. / j * H->calcule(j, n - 1 - j, p - 1, j - k) * ( k - 1.) / (j - 1.);
				else
					A2_3 += 0;
			}
			A2 += A2_1 * (A2_2 + A2_3);
			A2_1 = A2_2 = A2_3 = 0;
		}
		A2 = A2 * k;
		
			//		parite 3
		for (int j = k; j <= k + p - 1; j++)
		{
			A3_1 = 1. / j * H->calcule(j, n - 1 - j, p - 1, j - k);
			for (int l = 1; l <= k + p - 2; l++)
			{
				for (int m = l + 1; m <= k + p - 1; m++)
				{
					if (m == j)
						A3_3_1 = (k - 1.) / (j - 1.);
					else
						A3_3_1 = 0;
					if (m < j)
						A3_3_2 = (k - 1.) * (k - 2.) / ((j - 1.) * (j - 2.));
					else
						A3_3_2 = 0;
					index = kd->point_search[i].neighbors[m - 1]->index;
					A3_3 += kd->point_search[i].neighbors[m - 1]->label * Matrix_weights[i][index] * ( A3_3_1 + A3_3_2);//Matrix_weights[i][kd->point_search[i].neighbors[m - 1]->index] * ( A3_3_1 + A3_3_2);
				}
				index = kd->point_search[i].neighbors[l - 1]->index;
				A3_2 += kd->point_search[i].neighbors[l - 1]->label * Matrix_weights[i][index] * A3_3;// Matrix_weights[i][kd->point_search[i].neighbors[l - 1]->index] * A3_3;
				A3_3 = 0;
			}
			A3 += A3_1 * A3_2;
			A3_3_1 = A3_3_2 = A3_1 = A3_2 = 0;
		}
		A3 = 2 * k * A3;
			//		 partie 4
		for (int l = 1; l <= k + p - 1; l++)
		{
			index = kd->point_search[i].neighbors[l - 1]->index;
			A4_1 = kd->point_search[i].neighbors[l - 1]->label * Matrix_weights[i][index];//Matrix_weights[i][kd->point_search[i].neighbors[l - 1]->index];//;
			if (l >= k)
				A4_2_1 = 1. / l * H->calcule(l, n - 1 - l, p - 1, l - k);
			else
				A4_2_1 = 0;
			for (int j = k; j <= k + p - 1; j++)
			{
				if (j > l)
					A4_2_2 += 1. / j * H->calcule(j, n - 1 - j, p - 1, j - k) * (k - 1.) / (j - 1.);
				else
					A4_2_2 += 0;
			}
			A4 += A4_1 * ( A4_2_1 + A4_2_2);
			A4_2_1 = A4_2_2 = 0;
		}
		A4 = 2. * k * kd->point_search[i].Point->label * A4;
		point_err[i] =  A1 + A2 + A3 - A4; // risque pour chaque observation
		somme += A1 + A2 + A3 - A4;
	}
	Prob_Risque = 1. / n * somme;
}
