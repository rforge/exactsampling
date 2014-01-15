//
//  Candidat.cpp
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Candidat.h"

Candidat::Candidat()
{
	point_test = NULL;
	distance = 0;
}

void Candidat::initialise(point *a,double d)
{
	point_test = a;
	distance = d;
}
void Candidat::swap(Candidat &a)
{
	point *swap;
	double b;
	swap = a.point_test;
	b = a.distance;
	a.point_test = point_test;
	a.distance = distance;
	point_test = swap;
	distance = b;
}

Candidat::~Candidat()
{
}
