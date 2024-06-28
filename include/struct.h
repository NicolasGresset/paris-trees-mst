#pragma once
#include "array-list.h"
#include <stdio.h>

// why should we have a file with different structures ??
// it's perfect nonsense for me

/**
 * @brief Allows to store a pair of cooordinates with different names depending
 * on the context
 */
typedef struct {
  union {
    double latitude;
    double x;
  } coord_1;
  union {
    double longitude;
    double y;
  } coord_2;
} position;

/**
 * @brief structure informations importantes concernant un arbre
 */
typedef struct tree {
  position position;
  /// index renvoyant au genre (correspondance via une table d'indexation)
  short genus;
  short height;
} tree;

typedef struct {
  tree *trees;
  size_t size;
} forest;

/**
 * @brief gestion des options en argument
 */
typedef struct opt {

  int stat;                  // s
  int help;                  // a
  char *in_path;             // i
  char *out_path;            // o
  char *span_tree_path;      // t
  int max_distance;          // l
  char *limit_value;         // f
  char *genus;               // g
  int height;                // h
  char *genus_conserve_path; // c
  char *genus_recharge_path; // r

} opt;

#define MAX_GENUS_NAME_SIZE 30

typedef char genus[MAX_GENUS_NAME_SIZE + 1];

#define MAX_GENUS 255 // arbitraty value that seems reasonable
/**
 * @brief structure de tableau et taille associée
 */
typedef struct {
  /// @brief tableau de paires genre/id correspondant
  genus genuses[MAX_GENUS];
  /// @brief nombre d'éléments dans le tableau
  size_t size;

} tab_genus;

/**
 * @brief structure définissant une arête
 *
 */
typedef struct {
  /// @brief index du premier arbre connecté
  size_t tree1;
  /// @brief index du deuxième arbre connecté
  size_t tree2;
} edge;

typedef struct {
  edge *edges;
  size_t size;
} MST;


/**
 * @brief structure représentant un sommet pour la fonction minimumSpanningTree
 *
 */
typedef struct vertex {
  /// @brief la distance minimale aux autres sommets enregistrée (vaut 0 si le
  /// sommet est dans la composante)
  double distanceToComponent;
  /// @brief le sommet réalisant cette distance (identifié par son index)
  size_t whichVertex;
  ///
} vertex;
