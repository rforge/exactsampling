/*
 *  kNN_pondere_Weights.cpp
 *  kNN_pondere_Weights
 *
 *  Created by Michel Koskas on 26/10/12.
 *  Copyright 2012 kai li. All rights reserved.
 *
 */

#include "kNN_pondere_Weights.h"
#include "GeneralFunctions.h"


kNN_pondere_Weights::kNN_pondere_Weights()
{
  W = NULL;
	Logs = NULL;
}

kNN_pondere_Weights::kNN_pondere_Weights(int mm, int kk, double **WW, double ss)
{
  m = mm;
  k = kk;
	W = WW;
  s = ss;
  Logs = new long double[100000];
  Logs[0] = 0;
  for (int i = 1; i < 100000; i++)
    Logs[i] = Logs[i - 1] + log(i);
}





unsigned long int kNN_pondere_Weights::Binom(int a, int b)
{
  if (a <= 0)
    return 0;
  if (b < 0)
    return 0;
  if (b > a)
    return 0;
  if (b == 0)
    return 1;
  if (b == a)
    return 1;
  return round(exp(Logs[a] - Logs[b] - Logs[a - b]));
}



unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsGreaterThan(int NumPoint)
{
	return NumComb_positiveWeightsGeneralComparison(NumPoint, true, true);
}

unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsGreaterThanOrEqual(int NumPoint)
{
	return NumComb_positiveWeightsGeneralComparison(NumPoint, true, false);
}

unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsLowerThan(int NumPoint)
{
	return NumComb_positiveWeightsGeneralComparison(NumPoint, false, true);
}

unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsLowerThanOrEqual(int NumPoint)
{
	return NumComb_positiveWeightsGeneralComparison(NumPoint, false, false);
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsGreaterThan(int NumPoint)
{
	return NumComb_GeneralWeightsGeneralComparison(NumPoint, true, true);
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsGreaterThanOrEqual(int NumPoint)
{
	return NumComb_GeneralWeightsGeneralComparison(NumPoint, true, false);
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsLowerThan(int NumPoint)
{
	return NumComb_GeneralWeightsGeneralComparison(NumPoint, false, true);
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsLowerThanOrEqual(int NumPoint)
{
	return NumComb_GeneralWeightsGeneralComparison(NumPoint, false, false);
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsGeneralComparison(int NumPoint, bool GreaterThan, bool strict)
{
	if (!GreaterThan)
		return Binom(m, k) - NumComb_GeneralWeightsGeneralComparison(NumPoint, !GreaterThan, !strict);
	
	// Terminal Cases
  if (k == 1)
  {
    unsigned long int Answer = m;
		if (strict)
		{
			for (int i = 0; i < m; i++)
				if (W[NumPoint][i] <= s)
					Answer--;
		}
		else
			for (int i = 0; i < m; i++)
				if (W[NumPoint][i] < s)
					Answer--;
    return Answer;
  }
  if (m == k)
  {
    long double TotalWeight = 0;
    for (int i = 0; i < m; i++)
      TotalWeight += W[NumPoint][i];
		if (strict)
			if (TotalWeight <= s)
				return 0;
			else
				return 1;
		else
			if (TotalWeight < s)
				return 0;
			else
				return 1;
  }
  
	// General Cases
  if (unsorted<double>(W[NumPoint], W[NumPoint] + m))
    std::sort(W[NumPoint], W[NumPoint] + m);
  if (W[NumPoint][0] >= 0) // All weights are non negative
    return NumComb_positiveWeightsGeneralComparison(NumPoint, GreaterThan, strict);
  if (W[NumPoint][m - 1] <= 0) // All weights are negatice
  {
    unsigned long int Result;
    s = -s;
		for (int i = 0; i < m; i++)
			W[NumPoint][i] = -W[NumPoint][i];
    Result = Binom(m, k) - NumComb_positiveWeightsGeneralComparison(NumPoint, GreaterThan, !strict);
		for (int i = 0; i < m; i++)
			W[NumPoint][i] = -W[NumPoint][i];
    s = -s;
    return Result;
  }
	
  
  unsigned long int Result = 0;
  s -= W[NumPoint][m - 1];
  m--;
  k--;
  Result += NumComb_GeneralWeightsGeneralComparison(NumPoint, GreaterThan, strict);
  k++;
  s += W[NumPoint][m];
  Result += NumComb_GeneralWeightsGeneralComparison(NumPoint, GreaterThan, strict);
  m++;
  return Result;
}



unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsGeneralComparison(int NumPoint, bool GreaterThan, bool strict)
{
	if (!GreaterThan)
		return Binom(m, k) - NumComb_positiveWeightsGeneralComparison(NumPoint, !GreaterThan, !strict);
  if (unsorted<double>(W[NumPoint], W[NumPoint] + m))
    std::sort(W[NumPoint], W[NumPoint] + m);
  
	// Terminal cases
  if (k == 1)
  {
    unsigned long int Answer = m;
    for (int i = 0; i < m; i++)
      if (strict)
      {
        if (W[NumPoint][i] <= s)
          Answer--;
      }
      else
        if (W[NumPoint][i] < s)
          Answer--;
    return Answer;
  }
  if (m == k)
  {
    long double TotalW = 0;
    for (int i = 0; i < m; i++)
      TotalW += W[NumPoint][i];
    if (strict)
      if (TotalW <= s)
        return 0;
      else
        return 1;
		else
			if (TotalW < s)
				return 0;
			else
				return 1;
  }
  int BreakIndex = -1;
  double PartialWeight = 0;
  if (!strict)
    while ((BreakIndex < m) && (PartialWeight < s))
    {
      BreakIndex++;
      PartialWeight += W[NumPoint][BreakIndex];
    }
  else
    while ((BreakIndex < m) && (PartialWeight <= s))
    {
      BreakIndex++;
      PartialWeight += W[NumPoint][BreakIndex];
    }
  
  if (BreakIndex < k)
    return Binom(m, k);
  if (BreakIndex == m)
    return 0;
  
  
	// Non terminal Cases
  unsigned long int Result = 0;
  for (int i = BreakIndex; i < m; i++)
  {
    k--;
    s -= W[NumPoint][i];
    int Ex_m = m;
    m = i;
    Result += NumComb_positiveWeightsGeneralComparison(NumPoint, GreaterThan, strict);
    m = Ex_m;
    s += W[NumPoint][i];
    k++;
  }
  return Result;
}

unsigned long int kNN_pondere_Weights::NumComb_positiveWeightsEqual(int NumPoint)
{
	if (m < k) return 0;
	if (s < 0) return 0;
	if (k == 1)
  {
    unsigned long int Answer = 0;
		for (int i = 0; i < m; i++)
			if (W[NumPoint][i] == s)
				Answer++;
			//	std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids positifs  = " << Answer << std::endl;
		return Answer;
	}
	if (k == m)
	{
		long double TotalWeight = 0;
		for (int i = 0; i < m; i++)
			TotalWeight += W[NumPoint][i];
		if (TotalWeight == s)
		{
				//		std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids positifs  = 1" << std::endl;
			return 1;
		}
		else
		{
				//			std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids positifs  = 0" << std::endl;
			return 0;
		}
	}
	// General Cases
  if (unsorted<double>(W[NumPoint], W[NumPoint] + m))
    std::sort(W[NumPoint], W[NumPoint] + m);
  unsigned long int Result = 0;
  s -= W[NumPoint][m - 1];
  m--;
  k--;
	if (s >= 0)
		Result += NumComb_positiveWeightsEqual(NumPoint);
  k++;
  s += W[NumPoint][m];
  Result += NumComb_positiveWeightsEqual(NumPoint);
  m++;
		//	std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids positifs  = " << Result << std::endl;
  return Result;
}

unsigned long int kNN_pondere_Weights::NumComb_GeneralWeightsEqual(int NumPoint)
{
	if (m < k) return 0;
	if (k == 1)
	{
		unsigned long int Answer = 0;
		for (int i = 0; i < m; i++)
			if (W[NumPoint][i] == s)
				Answer++;
			//		std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids quelconques = " << Answer << std::endl;
		return Answer;
	}
	if (k == m)
	{
		long double TotalWeight = 0;
		for (int i = 0; i < m; i++)
			TotalWeight += W[NumPoint][i];
		if (TotalWeight == s)
		{
				//			std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids quelconques  = 1" << std::endl;
			return 1;
		}
		else
		{
				//		std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids quelconques  = 0" << std::endl;
			return 0;
		}
	}
  if (unsorted<double>(W[NumPoint], W[NumPoint] + m))
    std::sort(W[NumPoint], W[NumPoint] + m);
	if (W[NumPoint][0] >= 0)
		return NumComb_positiveWeightsEqual(NumPoint);
	if (W[NumPoint][m - 1] <= 0)
	{
		for (int i = 0; i < m; i++)
			W[NumPoint][i] = -W[NumPoint][i];
		s = -s;
		unsigned long int Result = NumComb_positiveWeightsEqual(NumPoint);
		s = -s;
		for (int i = 0; i < m; i++)
			W[NumPoint][i] = -W[NumPoint][i];
			//		std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids negatifs " << Result << std::endl;
		return Result;
	}
  unsigned long int Result = 0;
  m--;
  Result += NumComb_GeneralWeightsEqual(NumPoint);
  k--;
  s -= W[NumPoint][m];
  Result += NumComb_GeneralWeightsEqual(NumPoint);
  k++;
  s += W[NumPoint][m];
  m++;
		//	std::cerr << "NumPoint = " << NumPoint << ", m = " << m << ", egalite seuil pour poids generaux  = " << Result << std::endl;

  return Result;
}

