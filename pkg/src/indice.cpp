//
//  indice.cpp
//  test_code
//
//  Created by kai li on 03/03/13.
//  Copyright (c) 2013 kai li. All rights reserved.
//

#include "indice.h"

indice::indice()
{
	index = NULL;
	kd = NULL;
}

indice::indice(int d, int t, int dts, point *mpt, int k,int *ind,double *ldist)
{
	kd = new KD_tree(d,t,0,mpt);
	kd->search_neighbors_KD(mpt, k);
	index = new int[t * k];
	copyindex(d,t,k,ind,ldist);
}

indice::~indice()
{
	if (kd != NULL) {
		delete kd;
		delete index;
	}
}

void indice::copyindex(int d, int t, int k,int *ind,double *ldist)
{
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < k ; j++)
		{
			index[i*k + j] = kd->point_search[i].neighbors[j]->index;
			ind[i*k + j] = kd->point_search[i].neighbors[j]->index;
			ldist[i*k + j] = kd->point_search[i].distance[j];
		}
	}
}
