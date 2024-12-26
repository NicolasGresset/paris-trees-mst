#pragma once
#include "struct.h"
#include <stdio.h>

/**
 * @brief Cette fonction met les arbres concernés par les options dans
 * treesSelection
 *
 * @param handlingOptions options entrées en ligne de commande
 * @param trees tableau où sont stockées les informations sur les arbres
 * @param treesSelection tableau où sont stockées les informations sur les
 * arbres après le tri selon les options
 * @param size taille du tableau trees
 * @param sizeSelection taille du tableau treesSelection
 */
void handlingRestrictingOptions(opt handlingOptions, tree *trees,
                                tree *treesSelection, int size,
                                int *sizeSelection);