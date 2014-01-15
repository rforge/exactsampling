//
//  Candidat.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_Candidat_h
#define KD_tree_Candidat_h

#include "point.h"

// Candidat est la classe utilié dans la classe Heap.
// point_test est le candidat de plus proches voisins de point propre.
// distance est la distance entre le candidat et le point propre.
// initialise est la fonction qui copie et colle des données de point à point_test.
// swap est la fonction qui échange les donnée entre le point entré et le point_test.

struct Candidat
{
  point *point_test;
	double distance;
	Candidat();
	~Candidat();
	void initialise(point *, double);
	void swap(Candidat &);
};

#endif
