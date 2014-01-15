	//
	//  date_Heap_Sort.cpp
	//  KNN
	//
	//  Created by li kai on 29/06/12.
	//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
	//

#include <iostream>
#include "date_Heap_Sort.h"

date_HEAP_SORT::date_HEAP_SORT()
{
	date_list = NULL;
	tas = NULL;
	dimension_split = 0;
}

date_HEAP_SORT::date_HEAP_SORT(point **l,int taille,int d)
{
	date_list = l;
	max_nb = taille;
	dimension_split = d;
	tas = new point*[max_nb];
	tas_add();
	tas_sort();
	copy_point(l);
}

date_HEAP_SORT::~date_HEAP_SORT()
{
	if (tas != NULL) {
		delete [] tas;
	}
}


// Construit le tas , le parent est tjs supérieur à ses fils.
void date_HEAP_SORT::tas_add()
{
	int index = 0,index_remonte;
	tas[index] = date_list[index];
	point *swap;
	while (index < max_nb - 1)
	{
		index ++;
		tas[index] = date_list[index];
		index_remonte = index;
		while (index_remonte > 0)
		{
			if (tas[index_remonte]->X[dimension_split] > tas[(index_remonte - 1) / 2 ]->X[dimension_split])
			{
				swap = tas[index_remonte];
				tas[index_remonte] = tas[(index_remonte - 1)/2];
				tas[(index_remonte - 1)/2] = swap;
				index_remonte = (index_remonte - 1)/2; 
			}
			else
				break;
		}
	}
}

// tri le tableau par la coordonne des points sur l'axe associé en l'odre croissante.
void date_HEAP_SORT::tas_sort()
{
	point *swap;
	int index_cours;
	for (int i = max_nb - 1; i > 0; i--)
	{
		index_cours = 0;
		swap = tas[0];
		tas[0] = tas[i];
		tas[i] = swap;
		while (2 * index_cours + 1 < i)
		{
			if ( 2 * index_cours + 2 < i && tas[2 * index_cours + 1]->X[dimension_split] < tas[2 * index_cours + 2]->X[dimension_split]) 
			{
				if (tas[2*index_cours + 2]->X[dimension_split] > tas[index_cours]->X[dimension_split])
				{
					swap = tas[index_cours];
					tas[index_cours] = tas[index_cours * 2 + 2];
					tas[index_cours * 2 + 2] = swap;
					index_cours = index_cours * 2 + 2;
				}
				else 
					if	(tas[index_cours]->X[dimension_split] < tas[2 * index_cours + 1]->X[dimension_split])
					{
						swap = tas[index_cours];
						tas[index_cours] = tas[index_cours * 2 + 1];
						tas[index_cours * 2 + 1] = swap;
						index_cours = index_cours * 2 + 1;
					}
					else
						break;
				
			}
			else
				if (tas[index_cours]->X[dimension_split] < tas[2 * index_cours + 1]->X[dimension_split])
				{
					swap = tas[index_cours];
					tas[index_cours] = tas[index_cours * 2 + 1];
					tas[index_cours * 2 + 1] = swap;
					index_cours = index_cours * 2 + 1;
				}
				else
					break;
		}
	}
}

void date_HEAP_SORT::copy_point(point **l)
{
	for (int i = 0; i < max_nb; i++)
		l[i] = tas[i];
}
