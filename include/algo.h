#pragma once
#include "struct.h"
#include <stdio.h>


/**
 * @brief Compute the minimum spanning tree (MST) for the given forest
 * considered as a complete graph using Prim's algorithm
 *
 * @param forest
 * @param MST
 */
void computeMST(forest *forest, MST *MST);

/**
 * @brief Get the Forest Max Composante object Renvoie la liste d'arbres
 * "forêt" composée de la plus grande composante connexe, paramétrée par la
 * distance distmax
 *
 * @param forest
 * @param size la taille de forest
 * @param distmax
 * @param newsize pointeur vers la nouvelle taille de la forêt
 * @return tree*
 */
tree *getForestMaxComposante(tree *forest, size_t size, double distmax,
                             size_t *newsize);