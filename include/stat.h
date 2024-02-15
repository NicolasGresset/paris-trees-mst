#pragma once

#include <stdio.h>
#include "struct.h"

void stat(opt handlingOptions, edge * MST,size_t size, tree* forest);


/**
 * @brief renvoie le poids de l'arbre recouvrant minimal passé en paramètre
 * 
 * @param MST les aretes constituant l'arbre recouvrant minimal
 * @param size sa taille
 * @return double le poids de l'arbre recouvrant minimal
 */
double weightMinimumSpanningTree(edge* MST, size_t size);

double diameterMST(edge* MST, tree* forest, size_t size);
