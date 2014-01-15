//
//  make_point.cpp
//  kNN
//
//  Created by kai li on 28/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "make_point.h"
make_points::make_points()
{
	Dn = NULL;
	VM = NULL;
	size = 0;
	dimension = 0;
}

make_points::make_points(double *l, double *label,int n, int d)
{
	size = n;
	dimension = d;
	Dn = new point[size];
	VM = new V_to_M(l,n,d);
	for (int i = 0; i < size; i++)
	{
		Dn[i].X = VM->M[i];
		Dn[i].label = label[i];
		Dn[i].index = i ; // attention l'index dans le pondere binaire
	}
}

make_points::make_points(double *l,int n, int d)
{
	size = n;
	dimension = d;
	Dn = new point[size];
	VM = new V_to_M(l,n,d);
	for (int i = 0; i < size; i++)
	{
		Dn[i].X = VM->M[i];
		Dn[i].index = i + 1; // attention l'index dans le pondere binaire
	}
}


make_points::~make_points()
{
	if (Dn != NULL)
		delete Dn;
	if (VM != NULL)
		delete VM;
}
