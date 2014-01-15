//
//  vector_to_matrix.cpp
//  kNN
//
//  Created by kai li on 28/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "vector_to_matrix.h"
#include <iostream>
V_to_M::V_to_M()
{
	size = 0;
	M = NULL;
}

V_to_M::V_to_M(double *l, int n, int dimension)
{
	M = new double*[n];
	size = n;
	for (int i = 0; i < size; i++)
	{
		M[i] = new double[dimension];
		for (int j = 0; j < dimension; j++)
			M[i][j] = l[i * dimension + j];
	}
}

V_to_M::~V_to_M()
{
	if (M != NULL)
	{
		for (int i = 0 ; i < size; i++)
			delete M[i];
		delete M;
	}
}
