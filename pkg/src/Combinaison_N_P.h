//
//  Combinaison_N_P.h
//  KNN
//
//  Created by li kai on 25/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KNN_Combinaison_N_P_h
#define KNN_Combinaison_N_P_h

#include <iostream>
#include <algorithm>
#include <cmath>

class Combinaison_N_P {
public:
		// bool calcule;
	long double resultat;
	long double *Log_n_factoriel;
	Combinaison_N_P();
	Combinaison_N_P(int);
	~Combinaison_N_P();
	long double Combinaison(int n,int p);
};


#endif
