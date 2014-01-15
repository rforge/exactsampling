//
//  kNN_regression_pondere.h
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef kNN_kNN_regression_pondere_h
#define kNN_kNN_regression_pondere_h


#include <cstdio>
#include <cmath>
#include "KD_tree.h"
#include "HyperGeometrique.h"
#include "Combinaison_N_P.h"

class kNN_regression_pondere
{
public:
  KD_tree *kd;
	Combinaison_N_P *C;
	HyperGeometrique *H;
	int k;
	int p;
	double **Matrix_weights;
	double Prob_Risque;
	double *point_err;
	kNN_regression_pondere();
	kNN_regression_pondere(point *mpt, double **matrix_poids,int taille,int dimension,int k, int p, double *err);
  ~kNN_regression_pondere();
  void calcul_Risque();
};


#endif
