//
//  Combinaison_N_P_N_P.cpp
//  KNN
//
//  Created by li kai on 25/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Combinaison_N_P.h"



Combinaison_N_P::Combinaison_N_P()
{
	resultat = 0;
}

Combinaison_N_P::Combinaison_N_P(int N)
{
	Log_n_factoriel = new long double[N];
	Log_n_factoriel[0] = 0; // log(1)
	Log_n_factoriel[1] = logl(2.);  // log(2)
	for (int i = 2; i < N ; i++)
		Log_n_factoriel[i] = Log_n_factoriel[i - 1] + logl(static_cast<double>(i + 1));
}


Combinaison_N_P::~Combinaison_N_P()
{
	delete [] Log_n_factoriel;
}


long double Combinaison_N_P::Combinaison(int n,int p)
{
	if (n < p || n < 0 || p < 0)
	{
		resultat = 0;
		return resultat;
	}
	if (n == p || p == 0)
	{
		resultat = 1;
		return resultat;
	}
	if (p == 1 || n - p == 1) 
	{
		resultat = n;
		return resultat;
	}
	if (p == 0)
	{
		resultat = 1;
		return resultat;
	}
	resultat = expl(static_cast<double>(Log_n_factoriel[n - 1] - Log_n_factoriel[p - 1] - Log_n_factoriel[n - p - 1]));
	return  resultat;
}

