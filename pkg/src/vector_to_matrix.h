//
//  vector_to_matrix.h
//  kNN
//
//  Created by kai li on 28/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

// vector_to_matrix prend un vecteur et reforme ce vecteur en une matrix de taille associe à  l'échantillon complet, chaque ligne present les coordonnées d'un point.

#ifndef kNN_vector_to_matrix_h
#define kNN_vector_to_matrix_h
#include <cstdio>

class V_to_M
{
public:
  double **M;
	int size;
  V_to_M();
	V_to_M(double *l,int n,  int dimension);
	~V_to_M();
};


#endif
