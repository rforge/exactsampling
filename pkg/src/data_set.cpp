//
//  data_set.cpp
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "data_set.h"


data_set::data_set()
{
	dimension = 0;
	taille = 0;
	dimension_to_split = 0;
	mypoint = NULL;
}

data_set::data_set(int d,int t,int dts, point *mp)
{
	dimension = d;
	taille = t;
	dimension_to_split = dts; // dimension_to_split: 0--(n-1)
	mypoint = new point*[taille];
	for (int i = 0; i < taille; i++)
		mypoint[i] = &mp[i];
	date_HEAP_SORT set_tas(mypoint,taille,dimension_to_split);
}

data_set::data_set(int d,int t,int dts, point **mp)
{
	dimension = d;
	taille = t;
	dimension_to_split = dts; // dimension_to_split: 0--(n-1)
	mypoint = new point*[taille];
	for (int i = 0; i < taille; i++)
		mypoint[i] = mp[i];
	date_HEAP_SORT set_tas(mypoint,taille,dimension_to_split);
}

data_set::~data_set()
{
	delete mypoint;
}
