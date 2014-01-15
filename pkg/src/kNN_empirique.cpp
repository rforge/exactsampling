/*
 *  kNN_empirique.cpp
 *  test_code
 *
 *  Created by Michel Koskas on 19/02/13.
 *  Copyright 2013 kai li. All rights reserved.
 *
 */

#include "kNN_empirique.h"
#include <fstream>
using namespace std;

void kNN_empirique::Errors(double *err)
{
  for (int i = 0; i < nb_points; i++)
    err[i] = arbre_kd->point_search[i].Point->error;
}

kNN_empirique::kNN_empirique()
{
	k_nb = 0;
	arbre_kd = NULL;
	dimension = 0;
	nb_points = 0;
	seuil = 0. ;
	W = NULL ;
	Prob_Risque = 0.;
}

kNN_empirique::kNN_empirique (point *l, int nb,int dim, int k, double **weights, double Alpha)
{

	nb_points = nb;
	seuil = 0.;
	dimension = dim;
	Prob_Risque = 0;
	k_nb = k;

	if (weights != NULL)
		W = weights;
	else
  {
		W = new double*[nb_points];
    for (int i = 0; i < nb_points; i++)
      W[i] = new double[nb_points];
    for (int i = 0; i < nb_points; i++)
      for (int j = 0; j < nb_points; j++)
        W[i][j] = Puissance(0.01 + Distance(l[i], l[j], dimension), -Alpha);
  }
	alpha = Alpha;
	arbre_kd = new KD_tree(dimension, nb_points, 0,l);
	arbre_kd->search_neighbors_KD(l, k_nb);
}

kNN_empirique::~kNN_empirique()
{
	if (arbre_kd!=NULL)
		delete arbre_kd;

}

	// classification non pondère
void	kNN_empirique::kNN_empirique_calcule_risque_NPC()
{
	int sum_label;
  Prob_Risque = 0;
	for (int num_point = 0; num_point < nb_points; num_point++)
	{
		sum_label = arbre_kd->point_search[num_point].Point->label;
		for (int j = 0; j < k_nb - 1; j++)
			sum_label += arbre_kd->point_search[num_point].neighbors[j]->label;
    arbre_kd->point_search[num_point].Point->error = ((double) sum_label)/k_nb * (1 - arbre_kd->point_search[num_point].Point->label) + (1 - (double) sum_label/k_nb) * arbre_kd->point_search[num_point].Point->label;
    if (arbre_kd->point_search[num_point].Point->error > 0.5)
      Prob_Risque += 1;
    else if (arbre_kd->point_search[num_point].Point->error == 0.5)
      Prob_Risque += 0.5;
	}
	Prob_Risque /= nb_points;
}

	// classification pondère
void	kNN_empirique::kNN_empirique_calcule_risque_PC()
{
	double sum_poids;
  double TotalSumWeights;
	for (int num_point = 0; num_point < nb_points; num_point++)
	{
    if (arbre_kd->point_search[num_point].Point->label == 1)
      sum_poids = W[num_point][num_point];
    else sum_poids = 0;
    TotalSumWeights = W[num_point][num_point];
//		for (int j = 0; j < k_nb - 1; j++)
//      if (W[num_point][arbre_kd->point_search[num_point].neighbors[j]->index] < 0)
//        std::cerr << "ERROR: You make me deal with negtive weights. Getting out now." << std::endl;
		for (int j = 0; j < k_nb - 1; j++)
    {
      if (arbre_kd->point_search[num_point].neighbors[j]->label == 1)
				sum_poids += W[num_point][arbre_kd->point_search[num_point].neighbors[j]->index];
      TotalSumWeights += W[num_point][arbre_kd->point_search[num_point].neighbors[j]->index];
		}
    sum_poids /= TotalSumWeights;
    arbre_kd->point_search[num_point].Point->error = sum_poids * (1 - arbre_kd->point_search[num_point].Point->label) + (1 - sum_poids) * arbre_kd->point_search[num_point].Point->label;
    if (arbre_kd->point_search[num_point].Point->error > 0.5)
      Prob_Risque += 1;
    else if (arbre_kd->point_search[num_point].Point->error == 0.5)
      Prob_Risque += 0.5;
	}
	Prob_Risque /= nb_points;
}

void	kNN_empirique::kNN_empirique_calcule_risque_NPR()
{
	double sum_label;
	for (int num_point = 0; num_point  < nb_points; num_point++)
	{
		sum_label = arbre_kd->point_search[num_point].Point->label;
		for (int i = 0; i < k_nb - 1; i++)
			sum_label += arbre_kd->point_search[num_point].neighbors[i]->label;

		arbre_kd->point_search[num_point].Point->error = (arbre_kd->point_search[num_point].Point->label - sum_label / k_nb) * (arbre_kd->point_search[num_point].Point->label - sum_label / k_nb);
		Prob_Risque += arbre_kd->point_search[num_point].Point->error;
	}
	Prob_Risque /= nb_points;
}

void	kNN_empirique::kNN_empirique_calcule_risque_PR()
{
	double sum_poids, sum_label_poids;

	for (int num_point = 0; num_point < nb_points; num_point++)
	{
		sum_poids = W[num_point][num_point];
		sum_label_poids = W[num_point][num_point] * arbre_kd->point_search[num_point].Point->label;
		
		for (int i = 0; i < k_nb - 1; i++)
		{
			sum_poids += W[num_point][arbre_kd->point_search[num_point].neighbors[i]->index];
			sum_label_poids += W[num_point][arbre_kd->point_search[num_point].neighbors[i]->index] * arbre_kd->point_search[num_point].neighbors[i]->label;
		}

		arbre_kd->point_search[num_point].Point->error = (arbre_kd->point_search[num_point].Point->label - sum_label_poids * 1./ sum_poids) * (arbre_kd->point_search[num_point].Point->label - sum_label_poids * 1./ sum_poids);
		Prob_Risque += arbre_kd->point_search[num_point].Point->error;
	}
	Prob_Risque /= nb_points;
}




















