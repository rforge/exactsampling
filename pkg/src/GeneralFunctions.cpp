/*
 *  GeneralFunctions.cpp
 *  ExactSampling
 *
 *  Created by Michel Koskas on 24/12/12.
 *  Copyright 2012 INRA, INA. All rights reserved.
 *
 */

#include "GeneralFunctions.h"

double Distance(point &P, point &Q, int dimension)
{
	double Carre = 0;
	for (int i = 0; i < dimension; i++)
		Carre += (P.X[i] - Q.X[i]) * (P.X[i] - Q.X[i]);
	return sqrt(Carre);
}

double Puissance(double x, int n)
{
	if (n == 0)
		return 1;
	if (n < 0)
  {
    if (x == 0)
		{
				//		std::cerr << "Can NOT compute 0 to a negative exponent!" << std::endl;
				//	std::cerr << "Exiting NOW with errcode 837 " << std::endl;
				//exit(837);
		}
		else
			return Puissance(1/x, -n);
  }
	double Result = 1;
	while (n != 0)
	{
		if ((n % 2) != 0)
			Result *= x;
		x *= x;
		n /= 2;
	}
	return Result;
}

double Puissance(double x, double p)
{
  if (x == 0) return 1;
  return exp(p * log(x));
}

