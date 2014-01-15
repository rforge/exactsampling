/*
 *  GeneralFunctions.h
 *  ExactSampling
 *
 *  Created by Michel Koskas on 24/12/12.
 *  Copyright 2012 INRA, INA. All rights reserved.
 *
 */
#ifndef GenralFunctions_h
#define GenralFunctions_h

#include "point.h"

double Distance(point &P, point &Q, int dimension);
double Puissance(double x, int n);

template <typename T>
bool unsorted(T* Begin, T* End)
{
  for (T *Cur = Begin; Cur + 1 < End; Cur++)
    if (*Cur > *(Cur + 1))
      return true;
  return false;
}

template <typename T>
bool sorted(T* Begin, T* End)
{
  return !unsorted<T>(Begin, End);
}

#endif
