//
//  Fonctions.h
//  EpsilonBootstrap
//
//  Created by kai li on 21/10/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef EpsilonBootstrap_Fonctions_h
#define EpsilonBootstrap_Fonctions_h
#include <cmath>
#include <algorithm>

class Fonctions
{
private:
	double *logcum;
	
public:
	Fonctions();
	Fonctions(int n);
	~Fonctions();
	
  long double comb(int n, int p);
	long double combno(int n, int p);
	long double Pno(int p, int n, int t, double v);
	long double Pno_cum(int p, int n ,int t, double v);
	long double Phyper(int p,int n,int t, int v);
	long double Nhyper(int l, int n);
};

#endif
