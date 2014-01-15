//
//  data_set.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_data_set_h
#define KD_tree_data_set_h


#include "point.h"
#include "date_Heap_Sort.h"

struct point;
	//create l'échantillon des données
  // le dimension est le nombre d'axes de points
 // taille est la taille de l'échantillon complet
 // dimension_to_split sur lequel on divise les points en deux sous espaces
 // mypoint est l'ensemble de pointeurs de points

class data_set
{ 
public:
	int dimension;
	int taille;
	int dimension_to_split;
	point **mypoint;
	
	data_set();
//	Dans l'arbre KD, le premier constructeur est de initialiser les donnée dans  le noeud root.
	data_set(int dimension,int taille,int dimension_to_split,point *mypoint);
// le deuxieme constructeur est de stocker les donnée aux branches et les feuilles dans l'arbre KD
	data_set(int dimension,int taille,int dimension_to_split,point **mypoint);
	~data_set();
	void data_sort();
};


#endif
