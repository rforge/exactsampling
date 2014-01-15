//
//  EpsilonBootstrap.h
//  EpsilonBootstrap
//
//  Created by kai li on 21/10/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef EpsilonBootstrap_EpsilonBootstrap_h
#define EpsilonBootstrap_EpsilonBootstrap_h

#include <cmath>
#include <algorithm>
#include "Point_and_neighbors.h"
#include "Heap.h"
#include "HyperGeometrique.h"
#include "Fonctions.h"
#include "make_point.h"

using namespace std;
class EpsilonBootstrap {
  double Risque;
	double epsilon;
	double *point_err;
	int n;
	int dimension;
	int k;
	int Binf;
	int Bsup;
	int *Les1, *Les0;
	make_points *M_P;
	Point_and_neighbors *P_N;
	HyperGeometrique *Phyper;
	Fonctions *Probas;
public:
	EpsilonBootstrap();
	EpsilonBootstrap(double *l,double *label, int *taille,int *dimension, int *knb, double *epsilon, double *Risque, double *err);
	~EpsilonBootstrap();
	void search_neighbors(Point_and_neighbors &A,point *E, int index);
	double calcule_distance(point *A,point *B,int d);
	void calcule_Risque();
	void calcule_Binf_Bsup();
	void calcule_Les_1_0(int &,int *,int *);

	int entier(int &k);
	double calcul_Part_i();
	double calcul_Part_l(int&i);
	double calcul_Part_j(int&i, int&jj);
	double calcul_Part_t(int&i, int&ll,int&jj);
};


#endif
