#pragma once
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <tps.h>

#define RAYON 6378137.0

/**
 * @brief Cette fonction renvoie la distance en mètres entre deux arbres repérés par leurs coordonnées latitude et longitude
 * 
 * @param tree1 premier arbre à comparer
 * @param tree2 second arbre à comparer
 * @return double 
 * 
 */
double distanceTrees(tree * tree1, tree * tree2);


/**
 * @brief Cette fonction renvoie la conversion en radians d'un angle exprimé en degrés
 * 
 * @return double 
 */
double radians(double);

/**
 * @brief Fais la projection équirectangulaire des arbres de la liste forest
 * de taille size
 * 
 * @param forest 
 * @param size 
 */
void projectionTrees(tree* forest, size_t size);

void manageActions(tree* forest, size_t size, edge** MST, opt handlingOptions);