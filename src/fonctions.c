#include "../include/fonctions.h"
#include "../include/algo.h"
#include "../include/display.h"
#include "../include/parse.h"
#include "../include/stat.h"
#include <math.h>

void getMeanCoordinates(double *meanLatitude, double *meanLongitude,
                        forest *forest) {
  double sumLatitude = 0;
  double sumLongitude = 0;
  for (size_t i = 0; i < forest->size; i++) {
    sumLatitude += forest->trees[i].position.coord_1.latitude;
    sumLongitude += forest->trees[i].position.coord_2.longitude;
  }
  *meanLatitude = sumLatitude / forest->size;
  *meanLongitude = sumLongitude / forest->size;
}

inline void setNewCoordinates(tree *tree, double phi0, double lambda0,
                              double cosphi0) {
  tree->position.coord_1.x =
      cosphi0 * (tree->position.coord_1.latitude - lambda0) * M_PI / 180;
  tree->position.coord_2.y =
      (tree->position.coord_2.longitude - phi0) * M_PI / 180;
}

// maybe it's not the best one, to be tested
// c'est basiquement un changement d'origine et une déformation sur le premier
// axe
void equirectangularProjection(forest *forest) {
  double phi0, lambda0;
  getMeanCoordinates(&phi0, &lambda0, forest);
  double cosphi0 = cos(phi0 * M_PI / 180);

  for (size_t i = 0; i < forest->size; i++) {
    setNewCoordinates(&forest->trees[i], phi0, lambda0, cosphi0);
  }
}

double squaredDistanceTrees(tree *tree1, tree *tree2) {
  return ((pow(tree1->position.coord_1.x - tree2->position.coord_1.x, 2) +
           pow(tree1->position.coord_2.y - tree2->position.coord_2.y, 2)));
}

double distanceTrees(tree *tree1, tree *tree2) {
  return RAYON_TERRE * sqrt(squaredDistanceTrees(tree1, tree2));
}

void manageActions(tree *forest, size_t size, edge **MST, opt handlingOptions) {
  //*MST = minimumSpanningTree(forest, size);
  // stat(handlingOptions, *MST, size, forest);
  // displayTrees(*MST, size, forest);
  writeEdges(*MST, size - 1, handlingOptions);
}