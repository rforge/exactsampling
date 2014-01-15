//
//  make_point.h
//  kNN
//
//  Created by kai li on 28/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef __kNN__make_point__
#define __kNN__make_point__

#include <iostream>
#include "point.h"
#include "vector_to_matrix.h"
class make_points
{
public:
  point *Dn;
	V_to_M *VM;
	int size;
	int dimension;
	make_points();
	make_points(double *l, double *label,int n, int d);
		make_points(double *l, int n, int d);
	~make_points();
};


#endif /* defined(__kNN__make_point__) */
