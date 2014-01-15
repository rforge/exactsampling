//
//  KD_tree.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_KD_tree_h
#define KD_tree_KD_tree_h
#include <iostream>
#include <cmath>

#include "data_set.h"
#include "Point_Neighbors.h"
#include "point.h"
#include "Heap.h"
#include "Candidat.h"

class data_set;
struct point;
struct Point_Neighbors;

class KD_tree 
{
public:
		// partie de construire l'arbre KD 
	data_set *data;
	KD_tree *parents;
	KD_tree *left;
	KD_tree *right; 
	double seuil;
	int split_index;
	bool is_left;
	
	KD_tree();
	KD_tree(int d,int t,int dts,point *mpt); // create le noeude parents;
	
	KD_tree(int d,int t,int dts,point **p,KD_tree *,bool); // create les branches.
	~KD_tree();
	void split_tree(data_set *); // scinde l'arbre;
	
		// partie de chercher plus proche voisins
	Point_Neighbors *point_search;
	int k_neighbors;
	void search_neighbors_KD(point *mpt,int k);
		// Cherche la feuille contient le point à checher ses plus proche voisins
	void search_neigbors(Point_Neighbors &);
	double distance(point , point, int );
  int *FirstNeighbors(int k, int NumPoint);
};

#endif
