//
//  Fonctions.cpp
//  EpsilonBootstrap
//
//  Created by kai li on 21/10/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//
#include <iostream>
#include "Fonctions.h"
using namespace std;
Fonctions::Fonctions()
{
	logcum = NULL;
}

Fonctions::Fonctions(int n)
{
	logcum = new double[2*n];
	logcum[0] = 0.0; //log(1)
	logcum[1] = logl(2); //log(2)
	for (int i = 2; i< 2*n; i++) {
		logcum[i] = logcum[i - 1] + logl(i + 1);
	}
}

Fonctions::~Fonctions()
{
	if (logcum != NULL) {
		delete [] logcum;
	}
}

long double Fonctions::comb(int n, int p)
{
	if (p == 0) {
		return 1.0;
	}
	else if (n < p)
		return 0;
	else
	{
		if (n == p)
		{
//			cout << 1 << endl;
			return 1.0;
		}
		else
		{
			long double a,b;
			a = logcum[n - 1] - logcum[ n - p - 1]; // sum(log(n-p+1):(n))
			b = logcum[p - 1]; //sum(log(1:p))
			return expl(a-b);
		}
	}
}

long double Fonctions::combno(int n, int p)
{
	return comb(n + p - 1, p);
}

long double Fonctions::Pno(int p, int n, int t, double v)
{
	if (t - v < 0 || v != floor(v) || v < 0)
		return 0.0;
	else
	{
		long double a = combno(n, t - v);
		long double b = combno(p, v);
		long double c = combno(p + n, t);
		if (a == 0 || b == 0 || c == 0)
			return 0.0;
		return expl(logl(a) + logl(b) - logl(c));

//		return combno(n, t - v) * combno(p, v) / combno(p + n, t);
	}
}

long double Fonctions::Pno_cum(int p, int n ,int t, double v)
{
	long double P = 0;
	double seuil = 0;
	if (v < 0)
		seuil = 0;
	else
	{
		if (floor(v) != v) {
			seuil = floor(v+1);
		}
		else
			seuil = v;
	}
	if (t >= seuil)
	{
		for (int zz = v; zz <= t; zz++)
			P += Pno(p, n, t, zz);
	}
	return P;
}

long double Fonctions::Phyper(int p, int n, int t, int v)
{
	long double a = comb(p, v);
	long double b = comb(n, t - v);
	long double c = comb(n + p, t);
	if (a == 0 || b == 0 || c == 0)
		return 0.0;
	return expl(logl(a) + logl(b) - logl(c));
}

long double Fonctions::Nhyper(int l, int n)
{
	long double A,B,C;
	A = comb(n, n - l );
	B = comb(n - 1, l);
	C = comb(2 * n - 1,n);
	if (n < 50)
		return A*B/(C- 1);
	else
		return expl(logl(A) + logl(B) - logl(C));
}


