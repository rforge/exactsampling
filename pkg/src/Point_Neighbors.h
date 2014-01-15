//
//  Point_Neighbors.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_Point_Neighbors_h
#define KD_tree_Point_Neighbors_h
#include "point.h"

struct point;

	// Point stock le pointeur de point propre
	// neighbors stock les k plus Proches voisins de Point propre en forma pointeur
	// distance associé àux neighbors et Point propre en l'ordre croissante.
struct Point_Neighbors
{
	point *Point;
	point **neighbors;
	double *distance;
};


#endif
