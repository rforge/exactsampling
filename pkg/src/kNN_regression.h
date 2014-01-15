//
//  kNN_regression.h
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef kNN_kNN_regression_h
#define kNN_kNN_regression_h


#include "KD_tree.h"
#include "Combinaison_N_P.h"
#include "HyperGeometrique.h"
#include "cmath"

	// méthode knn regression non pondère
class kNN_regression
{
public:
  KD_tree *kd;
	HyperGeometrique *H;
	Combinaison_N_P *C;
	int nb_points;
	int k;
	int p;
	double Prob_Risque;
	double *point_err;
	
	kNN_regression();
	kNN_regression(point *mpt,int t, int d, int k,int p,double *err);
	~kNN_regression();
	void calcul_risque();
};


#endif
