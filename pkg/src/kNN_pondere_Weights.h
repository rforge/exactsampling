
/*
 *  kNN_pondere_Weights.h
 *  kNN_pondere_Weights
 *
 *  Created by Michel Koskas on 26/10/12.
 *  Copyright 2012 kai li. All rights reserved.
 *
 */

#ifndef Bootstrap_non_ponde_re_Bootstrap_non_pondere_h
#define Bootstrap_non_ponde_re_Bootstrap_non_pondere_h

#include <iostream>
#include <cmath>
#include "HyperGeometrique.h"
#include "Point_Neighbors.h"
#include "Heap.h"
#include "Combinaison_N_P.h"

unsigned long int Binom(int a, int b);


class kNN_pondere_Weights
{
public:
    // Vectoir Length
  int m;
    // k, number of considered weights;
  int k;
    // The weights
  double **W;
    // the threshold
  double s;
  kNN_pondere_Weights();
  kNN_pondere_Weights(int mm, int kk, double **WW, double ss);
	
	// La fonction suivante evalue le nombre de combinaison de poids (tous positifs) dont la somme est > au seuil
	unsigned long int NumComb_positiveWeightsGreaterThan(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (tous positifs) dont la somme est >= au seuil
	unsigned long int NumComb_positiveWeightsGreaterThanOrEqual(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (tous positifs) dont la somme est < au seuil
	unsigned long int NumComb_positiveWeightsLowerThan(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (tous positifs) dont la somme est <= au seuil
	unsigned long int NumComb_positiveWeightsLowerThanOrEqual(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (quelconques) dont la somme est > au seuil
	unsigned long int NumComb_GeneralWeightsGreaterThan(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (quelconques) dont la somme est >= au seuil
	unsigned long int NumComb_GeneralWeightsGreaterThanOrEqual(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (quelconques) dont la somme est < au seuil
	unsigned long int NumComb_GeneralWeightsLowerThan(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (quelconques) dont la somme est <= au seuil
	unsigned long int NumComb_GeneralWeightsLowerThanOrEqual(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (tous positifs) dont la somme est = au seuil
	unsigned long int NumComb_positiveWeightsEqual(int NumPoint);
	// La fonction suivante evalue le nombre de combinaison de poids (quelconques) dont la somme est = au seuil
	unsigned long int NumComb_GeneralWeightsEqual(int NumPoint);

  unsigned long int Binom(int a, int b);

private:
	long double *Logs;
	unsigned long int NumComb_GeneralWeightsGeneralComparison(int NumPoint, bool GreaterThan, bool strict);
	unsigned long int NumComb_positiveWeightsGeneralComparison(int NumPoint, bool GreaterThan, bool strict);
  
};

#endif
