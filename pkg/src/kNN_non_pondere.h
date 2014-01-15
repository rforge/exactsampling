//
//  kNN_non_pondere.h
//  kNN
//
//  Created by kai li on 20/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef kNN_kNN_non_pondere_h
#define kNN_kNN_non_pondere_h

#include "point.h"
#include "KD_tree.h"
#include "Combinaison_N_P.h"
#include "HyperGeometrique.h"
#include <fstream>

class Combinaison_N_P;

class kNN_non_pondere
{
public:
	point *points_set;
	KD_tree *arbre_kd;
	HyperGeometrique *H;
	
	int k_nb;
	int dimension;
	int nb_split;  // combinaision nb_split parmi nb_points
	int nb_points;
	double Prob_Risque; // le risque
	double *point_err;
	
	kNN_non_pondere();
	kNN_non_pondere( point *l, int nb,int dimension,int k, int p,double *err);
	~kNN_non_pondere();
	
		//	calcule l'erreur
	void calcule_erreur();
	double erreur_total(int index,double *);
	void _k_impaire(int index, int index_j, int n0, int n1, double & P);
	void _k_paire(int index,int index_j,int n0,int n1,double & P);
		//	verifier le resultat
};



#endif
