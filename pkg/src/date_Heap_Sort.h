//
//  date_Heap_Sort.h
//  KNN
//
//  Created by li kai on 29/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KNN_date_Heap_Sort_h
#define KNN_date_Heap_Sort_h
#include "point.h"
struct point;

// date_HEAP_SORT est de l'algorithme de HEAP sort. Dans notre package, cette classe aide arranger les points sur chaque noeud dans l'arbre KD selon l'axe associé en l'ordre croissante.
// Cela permet de trouver la médiane dans les points plus rapide.

class date_HEAP_SORT
{
public:
	point **date_list;  // copy le tableau de points dans le noeud courant.
	point **tas;        // le tableau de Tas de taille associé à la taille de points dans le noeud courant
	int dimension_split; // c'est le dimension sur lequel on divise les points en deux sous espaces.
	int max_nb;         // le nombre de points dans le noeud courant
	
	date_HEAP_SORT();
	date_HEAP_SORT(point **,int,int);
	~date_HEAP_SORT();
	void tas_add();
	void tas_sort();
	void copy_point(point **);
};

#endif
