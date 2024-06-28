#pragma once
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

#define RAYON_TERRE 6378137.0 // exprimé en mètres

// renvoie le carré de la distance entre deux arbres (en mètres), sans compter le rayon de la terre
double squaredDistanceTrees(tree * tree1, tree * tree2);

double distanceTrees(tree *tree1, tree *tree2);


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
void equirectangularProjection(forest *forest);

void manageActions(tree* forest, size_t size, edge** MST, opt handlingOptions);