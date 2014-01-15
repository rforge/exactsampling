	//
	//  HyperGeometrique.cpp
	//  KNN
	//
	//  Created by li kai on 25/06/12.
	//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
	//

#include <iostream>
#include "HyperGeometrique.h"

HyperGeometrique::HyperGeometrique()
{
	Log_n_factoriel = NULL;
}


HyperGeometrique::HyperGeometrique(int N)
{
	Log_n_factoriel = new long double[N];
	Log_n_factoriel[0] = 0; // log(1)
	Log_n_factoriel[1] = logl(2);  // log(2)
	for (int i = 2; i < N ; i++)
	{
		Log_n_factoriel[i] = Log_n_factoriel[i - 1] + logl(i + 1);
	}
	
}

long double HyperGeometrique::calcule(int N, int n, int k,int x)
{
	resultat = 0;
		
	if (N < 0 || n < 0|| k < 0 || x < 0 || (k - x) < 0 || N < x || n < (k - x) || (N + n ) < k)
	{
		return resultat = 0;
	}
	
	long double A = 0,B = 0,C = 0;
		//	Partie A
	if (x == 0 || x == N )
		A = 0;
	else if (x > 0)
		A = Log_n_factoriel[N  - 1] - Log_n_factoriel [x - 1] - Log_n_factoriel[N - x - 1];
	
		// Partie B
	if ((k - x ) == 0 || n == (k - x))
		B = 0;
	else if ((k - x) > 0 )
		B = Log_n_factoriel[n - 1] - Log_n_factoriel[k - x - 1] - Log_n_factoriel[n - (k - x) - 1];
	
		// Partie C
	if (k == 0 || (N + n ) == k)
		C = 0;
	else if (k > 0 )
		C = Log_n_factoriel[n + N - 1] - Log_n_factoriel[k - 1] - Log_n_factoriel[n + N - k - 1];
	resultat = expl( A + B - C);
	return  resultat ;
}


HyperGeometrique::~HyperGeometrique()
{
	if (Log_n_factoriel != NULL)
		delete [] Log_n_factoriel;
};

long double HyperGeometrique::repartition(int N, int n, int k,int x)
{
	resultat_repartition = 0;
	for (int i = 0; i <= x; i++)
	{
		resultat_repartition =  resultat_repartition + calcule(N, n, k, i);
	}
	if (resultat_repartition > 1 )
		resultat_repartition = 1.0;
	return resultat_repartition;
}

