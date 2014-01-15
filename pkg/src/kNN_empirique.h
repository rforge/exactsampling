/*
 *  kNN_empirique.h
 *  test_code
 *
 *  Created by Michel Koskas on 19/02/13.
 *  Copyright 2013 kai li. All rights reserved.
 *
 */

#ifndef kNN_empirique_h
#define kNN_empirique_h

#include "point.h"
#include "KD_tree.h"
#include "GeneralFunctions.h"


class kNN_empirique
{
public:
	KD_tree *arbre_kd;
  int k_nb;
	int dimension;
	int nb_points;  // combinaision nb_split parmi nb_points
	double seuil;
	double **W;
	double Prob_Risque; // le risque
	double alpha;
	
	
	kNN_empirique();
	kNN_empirique (point *l, int nb,int dimension, int k, double **weights,double Alpha = 0);
	~kNN_empirique();

		// domaine des fonctions
		// classification non pondère
	void	kNN_empirique_calcule_risque_NPC();
		// classification pondère
	void	kNN_empirique_calcule_risque_PC();
		// Regression non pondère
	void	kNN_empirique_calcule_risque_NPR();
		// Regression pondère
	void	kNN_empirique_calcule_risque_PR();
    // Recopie les erreurs
  void Errors(double *err);
};

#endif

