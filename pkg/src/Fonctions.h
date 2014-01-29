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
	double *logcum; //le vecteur des sommes cumulees du log n!
	
public:
	Fonctions();
	Fonctions(int n);
	~Fonctions();
	
  long double comb(int n, int p);				//computes n choose p
	long double combno(int n, int p);			//computes  (n+p-1) choose p
	long double Pno(int p, int n, int t, double v);	// p/(v+p)P(X=v) if X follows hyper-geometric distribution with parameters K=v+p, N=n+t+p-1 and n=t
	long double Pno_cum(int p, int n ,int t, double v);
	long double Phyper(int p,int n,int t, int v); // P(X=v) if X follows hyper-geometric distribution with parameters K=p, N=n+p and n=t
	long double Nhyper(int l, int n);
};

#endif
