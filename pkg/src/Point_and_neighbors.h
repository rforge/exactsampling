//
//  point_and_neighbors.h
//  Bootstrap_non_pondère
//
//  Created by kai li on 17/08/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#ifndef Bootstrap_non_ponde_re_point_and_neighbors_h
#define Bootstrap_non_ponde_re_point_and_neighbors_h

#include "point.h"

struct Point_and_neighbors
{
  point *P;
	point **Neighbors;
	double *distance;
};


#endif
