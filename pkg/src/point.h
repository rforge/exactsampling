//
//  point.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_point_h
#define KD_tree_point_h
#include "KD_tree.h"

class KD_tree;

	// label est la classe de point
	// index est l'indice de point dans l'échantillon complet, il prend la valeur entre 1 et la taille de l'échantillon complet
	// my_node stock l'adresse de feuille dans l'arbre kd où ce point se situe
	// X sont les coordonnes de ce point.

struct point
{ 
	double label;
	int index;
	KD_tree *my_node;
	double *X;
	double error;
};




#endif
