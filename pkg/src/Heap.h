//
//  Heap.h
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KD_tree_Heap_h
#define KD_tree_Heap_h
#include "point.h"

struct Candidat;

// classe Heap est 'applicaiton de recherche k plus proches voisins dans le processus de KD tree.
// tas est un taleau de taille k, qui stock les k candidats de plus proches voisins
// nb_elements compte le nombre de points stockés dans le tableau tas. nb_elements ne doit pas être supérieur à k.
// Max_elements est égal à k.
//  maketas() est la fonction qui remplit le point situé dans la tête de tas par les nouveaux éléments  quand le tableau est plein.
// add() est la fonction qui ajoute les éléments quand le tableau n'est pas plein.
class Heap
{
	public :
	Candidat *tas;
	int nb_elements;
	int MAX_elements;
	Heap();
	Heap(int );
	~Heap( );
	void add () ;
	void maketas(point *,double) ;
	void sort();	
} ;




#endif
