//
//  EpsilonBootstrap.cpp
//  EpsilonBootstrap
//
//  Created by kai li on 21/10/12.
//  Copyright (c) 2012 kai li. All rights reserved.
//

#include "EpsilonBootstrap.h"
EpsilonBootstrap::EpsilonBootstrap()
{
	Risque = epsilon = 0;
	Binf = Bsup = 0;
	n = 0;
	dimension = 0;
	k = 0;
	point_err = NULL;
	P_N = NULL;
	Phyper = NULL;
	Probas = NULL;
	Les0 = NULL;
	Les1 = NULL;
	M_P = NULL;
}

EpsilonBootstrap::EpsilonBootstrap(double *l,double *label, int *taille,int *d, int *knb, double *e, double *R, double *err)
{
	
	n = *taille;
	dimension = *d;
	k = *knb;
	epsilon = *e;
	Binf = 1;
	Bsup = n - 1;
	point_err = new double[n];
	Les0 = new int[n - 1];
	Les1 = new int[n - 1];
	P_N = new Point_and_neighbors[n];
	Phyper = new HyperGeometrique(n);
	Probas = new Fonctions(n);
		// recherche les n - 1 plus proches voisins pour chaque point dans l'échantillon complet;
	M_P = new make_points(l,label,*taille,*d);
	for (int i = 0; i < n; i++)
	{
		search_neighbors(P_N[i], M_P->Dn,i);
	}
	calcule_Risque();
	*R = Risque;
	for (int i = 0; i < *taille; i++) {
		err[i]=point_err[i];
	}

}

EpsilonBootstrap::~EpsilonBootstrap()
{
	if (P_N != NULL) {
		for (int i = 0; i < n; i++) {
			if (P_N[i].P != NULL)
			{
					//				delete  P_N[i].P;
				delete [] P_N[i].Neighbors;
			}
			delete [] P_N[i].distance;
		}
		delete [] P_N;
	}
	if (point_err != NULL) {
		delete point_err;
	}
	if (Les0 != NULL)
		delete Les0;
	if (Les1 != NULL)
		delete Les1;

}

void EpsilonBootstrap::search_neighbors(Point_and_neighbors &A, point *E, int index)
{
	Heap HEAP(n - 1);
	double d = 0;
	A.P = &E[index];
	A.distance = new double[n - 1];
	A.Neighbors = new point*[n - 1];

	for (int i = 0; i < n; i++)
		if (i != index)
		{
			d = calcule_distance(A.P, &E[i], dimension);
			HEAP.maketas(&E[i], d);
		}
	HEAP.sort();
	for (int i = 0; i < n -1; i++)
	{
		A.Neighbors[i] = HEAP.tas[i].point_test;
		A.distance[i] = HEAP.tas[i].distance;
	}
}

double EpsilonBootstrap::calcule_distance(point *A,point *B,int d)
{
	double distance = 0;
	for (int i = 0; i< d; i++)
	{
		distance += pow(A->X[i] - B->X[i], 2.);
	}
	return sqrt(distance);
}


void EpsilonBootstrap::calcule_Risque()
{
	Risque = calcul_Part_i();
}

void EpsilonBootstrap::calcule_Binf_Bsup()
{
	double cumul = 0;
	long double gauche = 0,droite = 0;
	while (cumul < epsilon)
	{
		gauche = Probas->comb(n, n - Binf) *  Probas->comb(n - 1, Binf) / (Probas->comb(2 * n - 1, n) - 1);
		droite = Probas->comb(n, n - Bsup) *  Probas->comb(n - 1, Bsup) / (Probas->comb(2 * n - 1, n) - 1);
		double LeMin = std::min(gauche, droite);
		cumul += LeMin;
		if (cumul < epsilon )
		{
			if (gauche < droite)
				Binf += 1;
			else
				Bsup -= 1;
		}
	}
}

void EpsilonBootstrap::calcule_Les_1_0(int &i, int *les1, int *les0)
{
	if (P_N[i - 1].Neighbors[0]->label == 1)
	{
		les0[0] = 0;
		les1[0] = 1;
	}
	else
	{
		les0[0] = 1;
		les1[0] = 0;
	}

	for (int index = 1; index < n - 1; index++)
	{
		if (P_N[i - 1].Neighbors[index]->label == 1)
		{
			les1[index] = les1[index - 1] + 1;
			les0[index] = les0[index - 1] + 0;
		}
		else
		{
			les1[index] = les1[index - 1] + 0;
			les0[index] = les0[index - 1] + 1;
		}
	}
}

int EpsilonBootstrap::entier(int &k)
{
	return k % 2 == 0 ? k / 2 : (k + 1) / 2;
}

static double P6 = 0, P5 = 0, P4 = 0, P3 = 0, PT = 0, M = 0;


double EpsilonBootstrap::calcul_Part_i()
{
	calcule_Binf_Bsup();
	double P_i = 0.0;
	for (int i = 1; i <= n; i++)
	{
		calcule_Les_1_0(i,Les1,Les0);
		point_err[i - 1] = calcul_Part_l(i);
		P_i += point_err[i - 1];
	}


	return P_i;
}

double EpsilonBootstrap::calcul_Part_l(int &i)
{
	double P_l = 0;
	for (int ll = Binf; ll <= Bsup; ll++)
	{
		P6 = Probas->Nhyper(ll, n);
		P5 = (double)ll / n;
		P4 = (n - ll) / (n - 1.0);
		P_l += calcul_Part_j(i, ll);
	}
	return P_l;
}

double EpsilonBootstrap::calcul_Part_j(int &i, int &ll)
{
	double P_j = 0;
	for (int jj = 1; jj <= n - 1; jj++)
	{
		if (jj + ll > k - 1)
			P_j += calcul_Part_t(i, ll, jj);
	}
	return P_j;
}

double EpsilonBootstrap::calcul_Part_t(int &i, int &ll, int &jj)
{
	double P_t = 0;
	for (int tt = 0 ; tt <= min(jj - 1, ll - 1); tt++)
	{
		if ((tt > jj + ll - n - 1) && (tt < jj + ll - k + 1))
		{
			P3 = Probas->Phyper(jj - 1, n - jj - 1, ll - 1, tt);
		
			if (jj == 1)
				PT = Probas->Pno_cum(jj - tt, n - ll - jj + tt, ll, k - jj + tt);
			else
				PT = Probas->Pno_cum(jj - tt, n - ll - jj + tt, ll, k - jj + tt) - Probas->Pno_cum(jj - tt - 1, n - ll - jj + tt + 1, ll, k -  jj +tt + 1);
	
			int n1ij = Les1[jj - 1];
			int n0ij = Les0[jj - 1];
			double PR = 0.;
			M = 0.;
			if (k - jj + tt == 0)
			{
				for (int rr = max(0,(int)(tt - n0ij + 1 - P_N[i - 1].Neighbors[jj - 1]->label)); rr <= min(tt, (int)(n1ij - P_N[i - 1].Neighbors[jj - 1]->label)); rr++)
				{

					double Pond = Probas->Phyper(n1ij - P_N[i - 1].Neighbors[jj - 1]->label, n0ij -1 + P_N[i - 1].Neighbors[jj - 1]->label, tt, rr);

					if (k % 2 != 0)
					{
						if (n1ij - rr < k / 2.0)
							PR = P_N[i - 1].P->label;
						else if (n1ij - rr > k / 2.0)
							PR = 1 - P_N[i - 1].P->label;
					}
					else
					{
						if (n1ij - rr < k / 2.0)
							PR = P_N[i - 1].P->label;
						else if (n1ij - rr > k / 2.0)
							PR = 1 - P_N[i - 1].P->label;
						else if (n1ij - rr == k / 2.0)
							PR = 0.5;
					}
					M += PR * Pond / (double)(ll);
				}
			}
			else
			{
				for (int rr = max(0,(int)(tt - n0ij + 1 - P_N[i - 1].Neighbors[jj - 1]->label)); rr <= min(tt, (int)(n1ij - P_N[i - 1].Neighbors[jj - 1]->label)); rr++)
				{
					double Pond = Probas->Phyper(n1ij - P_N[i - 1].Neighbors[jj - 1]->label, n0ij - 1 + P_N[i - 1].Neighbors[jj - 1]->label, tt, rr);
					if (k % 2 == 1)
					{
						if (P_N[i - 1].P->label == 1)
							PR = 1 - Probas->Pno_cum(n1ij - rr, n0ij - tt + rr, k - jj + tt, entier(k)- n1ij + rr);
						else
							PR = Probas->Pno_cum(n1ij - rr, n0ij - tt + rr, k - jj + tt, entier(k) - n1ij + rr);
					}
					else
					{
						if (P_N[i - 1].P->label == 1)
							PR = 1 - Probas->Pno_cum(n1ij - rr, n0ij - tt + rr, k - jj + tt, entier(k)- n1ij + rr);
						else
							PR = Probas->Pno_cum(n1ij - rr, n0ij - tt + rr, k - jj + tt, entier(k) - n1ij + rr);
						PR += 0.5 * Probas->Pno(n1ij - rr, n0ij - tt + rr, k - jj + tt, k / 2 - n1ij + rr);
					}
					M += PR * Pond / (double)(ll);
				}
			}
	
			P_t += P6 * P5 * P4 * P3 * PT * M;
		}
	}
	return P_t;
}






