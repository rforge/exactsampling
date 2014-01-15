//
//  KD_tree.cpp
//  KD_tree
//
//  Created by li kai on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "KD_tree.h"

int *KD_tree::FirstNeighbors(int k, int NumPoint)
{
  int*Res = new int[k];
  for (int i = 0; i < k; i++)
    Res[i] = point_search[NumPoint].neighbors[i]->index;
  return Res;
}


KD_tree::KD_tree()
{
	data = NULL;
	parents = NULL;
	left = NULL;
	right = NULL;
	seuil = 0;
	split_index = 0;
	point_search = NULL;
	k_neighbors = 0;
	is_left = NULL;
}

	// initialisation le noeud root
KD_tree::KD_tree(int d, int t, int dts, point *mpt)
{
	data = new data_set(d, t, dts, mpt);
	parents = NULL;
	split_index = t / 2;
	seuil = data->mypoint[split_index]->X[data->dimension_to_split];
	k_neighbors = 0;
	is_left = NULL;
	point_search = new Point_Neighbors[t];
	split_tree(data);
}

	// construit les branches 
KD_tree::KD_tree(int d, int t, int dts, point **p, KD_tree *f,bool isleft)
{
	point_search = NULL;
	is_left = isleft;
	data = new data_set(d,t,dts,p);
	parents = f;
	split_tree(data);
}


void KD_tree::split_tree(data_set *data)
{ 
	if ( data->taille == 1)
	{
		data->mypoint[data->taille-1]->my_node = this ;
		return ;
	}
	int taille_split_to_left_branche = (data->taille + 1 ) / 2;
	
	split_index = taille_split_to_left_branche - 1;  
	seuil = data->mypoint[split_index]->X[data->dimension_to_split];
	point **thePoints_left = new point*[taille_split_to_left_branche];
	point **thePoints_right = new point*[data->taille - taille_split_to_left_branche];
	
		// copie les points aux branches associés
	for (int i = 0; i < taille_split_to_left_branche; i++) 
		thePoints_left[i] = data->mypoint[i];
	for (int i = taille_split_to_left_branche ; i < data->taille; i++)
		thePoints_right[i - taille_split_to_left_branche] = data->mypoint[i]; 
	
		// create les branches gauche et droite recursivement
	
	left= new KD_tree(data->dimension,taille_split_to_left_branche,(data->dimension_to_split + 1 ) % data->dimension, thePoints_left,this,true); 
	right = new KD_tree(data->dimension,data->taille - taille_split_to_left_branche,(data->dimension_to_split + 1 ) % data->dimension, thePoints_right,this,false);
	delete  [] thePoints_left;
	delete  [] thePoints_right;
}

KD_tree::~KD_tree()
{
	if (point_search != NULL)
	{
		delete [] point_search;
	delete  data;
	delete  left;
	delete  right;
	}
}

// La fonction search_neighbors_KD lance le processus de rechercher les k plus proches voisins avec la seletion de candidat par l'algorithme Heap sort. 
void KD_tree::search_neighbors_KD( point *mpt, int k)
{
	this->k_neighbors = k;
	for (int i = 0; i < data->taille; i++) 
	{
		point_search[i].Point = &mpt[i];
		point_search[i].neighbors = new point*[k_neighbors];
		point_search[i].distance = new double[k_neighbors];  // stock les distances entre les voisins et le points propre selon l'ordre croissante.
		search_neigbors(point_search[i]);
	}
}


void KD_tree::search_neigbors(Point_Neighbors &P)
{
	KD_tree *search_node = P.Point->my_node;
	int compte_nb = 0;
	double d;
//	 initialise le tableau de Tas(Heap sort) da taille k.
	Heap t(k_neighbors);
	int dimension = this->data->dimension;
	
//	remplit le tableau de Tas(Heap sort) par les premiers k points à partir de la feuille où le point propre se situe
	while (compte_nb < k_neighbors && search_node->parents != NULL)
	{
		if (search_node->is_left)
			search_node = search_node->parents->right;
		else
			search_node = search_node->parents->left;
		for (int i = 0; i < search_node->data->taille; i++)
		{
			compte_nb++;
			d = distance(*P.Point, *search_node->data->mypoint[i], dimension);
			t.maketas(search_node->data->mypoint[i],d);
		}
		search_node = search_node->parents;
	}
	
		
		//  Une fois le tableau est plein, on commence choisir le point comme le k-ieme plus proche voisin par la critere seuil dans chaque noeud.
	double distance_seuilPoint;
	while (search_node->parents != NULL)
	{
			// Calcule la distance entre le point propre et le seuil dans le parent du noeud courant. Si la distance entre le dernier voisin et le point propre est plus grand à la premiere distance. Alors, on peut entrer dans le parent de noeud courant à choisir les plus proches voisins.
		distance_seuilPoint = P.Point->X[search_node->parents->data->dimension_to_split] - search_node->parents->seuil;
		if (distance_seuilPoint < 0)
			distance_seuilPoint = -1. * distance_seuilPoint;
		
		if (t.tas[0].distance >= distance_seuilPoint)
		{
				// si le noeud courant est le branche gauche de parent, on passe dans le branche droite de parent. Si non, change la role de gauche et droite.
			if (search_node->is_left)
				search_node = search_node->parents->right;
			else
				search_node = search_node->parents->left;
			for (int i = 0; i < search_node->data->taille; i++)
			{
				d = distance(*P.Point, *search_node->data->mypoint[i], dimension);
				t.maketas(search_node->data->mypoint[i],d);
			}
		}
		search_node = search_node->parents;
	}
	
//	ordonne le tableau Tas
	t.sort();
		for (int i = 0; i < k_neighbors; i++)
	{
		P.neighbors[i] = t.tas[i].point_test;
		P.distance[i] = t.tas[i].distance;
	}
}

double KD_tree::distance(point a,point b,int d)
{
	double dis = 0.;
	for (int i = 0; i < d; i++) 
		dis = dis + (a.X[i] - b.X[i])*(a.X[i] - b.X[i]);
	return sqrt(dis);
}





