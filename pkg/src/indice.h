//
//  indice.h
//  test_code
//
//  Created by kai li on 03/03/13.
//  Copyright (c) 2013 kai li. All rights reserved.
//

#ifndef test_code_indice_h
#define test_code_indice_h

#include "KD_tree.h"
#include "point.h"


class indice {
public:
  KD_tree *kd;
  int *index;
	
	indice();
	indice(int d, int t, int dts, point *mpt,int k,int *ind,double *ldist);
	~indice();
	void copyindex(int d,int t, int k, int *ind,double *ldist);
};




#endif
