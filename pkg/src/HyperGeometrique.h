	//
	//  HyperGeometrique.h
	//  KNN
	//
	//  Created by li kai on 25/06/12.
	//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
	//

#ifndef KNN_HyperGeometrique_h
#define KNN_HyperGeometrique_h

#include "Combinaison_N_P.h"
#include<cmath>

	//const double Pi = 4 * atan(1);

class HyperGeometrique
{
public:
	double long *Log_n_factoriel;
	long double resultat;
	long double resultat_repartition;
	
	HyperGeometrique();
	HyperGeometrique(int N);
	~HyperGeometrique();
	long double calcule(int N, int n, int k,int x);
	long double repartition(int N, int n, int k,int x);
};
#endif
