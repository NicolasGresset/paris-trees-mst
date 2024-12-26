#pragma once
#include "struct.h"
#include <stdio.h>
#include <time.h>

// /**
//  * @brief Une fonction qui permet d'afficher l'arbre recouvrant minimal
//  *
//  * @param listeAretes la liste des aretes de l'arbre
//  * @param size la taille du graphe (la structure)
//  * @param structure la structure de l'arbre de taille size + 1
//  */
// void displayTrees(edge* listeAretes, size_t size, tree* structure);

/**
 * @brief Une fonction permettant de visualiser l'avancement d'un processus
 *
 * @param current la quantité actuelle d'avancement du processus
 * @param total la quantité totale de référencee
 * @param delta le nombre de millisecondes écoulées depuis le début du programme
 */
void loadingBar(int current, int total, clock_t delta);

/**
 * @brief Get the Extremum object Ecrit à l'emplacement des pointeurs passés
 * en paramètre les extremums des champs geoloc.x et geoloc.y de la forêt
 * d'arbre forest de taille size
 *
 * @param forest
 * @param size
 * @param minimumX
 * @param minimumY
 * @param maximumX
 * @param maximumY
 */
void getExtremum(tree *forest, size_t size, double *minimumX, double *minimumY,
                 double *maximumX, double *maximumY);