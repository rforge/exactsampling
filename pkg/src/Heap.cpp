	//
	//  Heap.cpp
	//  KD_tree
	//
	//  Created by li kai on 14/06/12.
	//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
	//

#include <iostream>

#include "Heap.h"
#include "Candidat.h"
Heap::Heap()
{
	nb_elements = 0 ;
	MAX_elements = 0;
	tas = NULL;
}

Heap::Heap(int k)
{
	nb_elements = 0;
	MAX_elements = k;
	tas = new Candidat[k];
}



void Heap::add()
{
	if (nb_elements < MAX_elements)
	{
		nb_elements++;
		int Indice = nb_elements - 1;
		while (Indice > 0)
		{
			if (tas[Indice].distance > tas[(Indice - 1) / 2].distance)  // compare avec le node parents
			{
				tas[Indice].swap(tas[(Indice - 1) / 2]);
				Indice= (Indice - 1 ) / 2;
			}
			else
				break;
		}
		return;
	}
}


void Heap::maketas(point *a, double d)
{
	if (nb_elements < MAX_elements)
	{
		tas[nb_elements].initialise(a, d);
		add();
	}
	else
	{
		if (d > tas[0].distance)
			return;
		tas[0].initialise(a, d);
		int Indice = 0;
			// si le branche droite existe
		while (2 * Indice + 1 < nb_elements - 1)
		{
				//branche gauche.
			int Indice_echange = 2 * Indice + 1;
			if (tas[Indice_echange + 1].distance > tas[Indice_echange].distance)
				Indice_echange++;
			if (tas[Indice].distance < tas[Indice_echange].distance)
			{
				tas[Indice].swap(tas[Indice_echange]);
				Indice = Indice_echange;
			}
			else
				break;
		}
		if (2 * Indice + 1 == nb_elements - 1)
		{
			if (tas[Indice].distance < tas[2 * Indice + 1].distance)
				tas[Indice].swap(tas[2 * Indice + 1]);
		}
	}
}


void Heap::sort()
{ 
	int index,index_end;
	for (int i = MAX_elements - 1; i > 0; i--)
	{
			// échange les éléments dans le noeud tête et  terminal.
		tas[0].swap(tas[i]);
		index = 0;
		index_end = i - 1;
			// ordonne l'élément en tête, si il inférieur à ses noeud fils
		while (index_end > 2 * index +1)
		{
			if (tas[index].distance >= tas[2 * index +1].distance && tas[index].distance >= tas[2 * index + 2].distance )
				break ;
			
			else if(tas[2 * index +1].distance >=tas[2 * index +2].distance)
			{
				tas[index].swap(tas[index * 2 + 1]);
				index = 2 * index + 1;
			}
			else 
			{
				tas[index].swap(tas[index * 2 + 2]);
				index = 2 * index + 2;
			}
		}
		
		if ((2*index+1)==index_end && tas[2 * index + 1].distance >tas[index].distance)
			tas[index].swap(tas[index * 2 + 1]);
	}
}

Heap::~Heap()
{
	if (tas != NULL)
		delete [] tas;
}
