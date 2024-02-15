#pragma once
#include "struct.h"
#include <stdio.h>



/**
 * @brief Une fonction qui calcule l'arbre recouvrant minimal du graphe
 * structure passé en paramètre
 * 
 * @param forest le graphe dont on calcule l'arbre
 * @param size la taille du graphe
 * @return arete* : la liste des arètes constituant l'arbre recouvrant 
 * minimal
 */
edge* minimumSpanningTree(tree* forest, size_t size);


/**
 * @brief Get the Forest Max Composante object Renvoie la liste d'arbres "forêt" composée de la plus grande composante connexe,
 * paramétrée par la distance distmax
 * 
 * @param forest 
 * @param size la taille de forest
 * @param distmax 
 * @param newsize pointeur vers la nouvelle taille de la forêt
 * @return tree* 
 */
tree* getForestMaxComposante(tree* forest, size_t size, double distmax, size_t* newsize);