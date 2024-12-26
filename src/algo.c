#include "../include/algo.h"
#include "../include/display.h"
#include "../include/fonctions.h"
#include "../include/struct.h"
#include <stdlib.h>
#include <time.h>

#define INFINI 4000000 // todo modifier par le double maximum

static inline void initializeVertexes(vertex *vertexes, size_t size) {
  vertexes[0].distanceToComponent = 0;
  for (size_t i = 1; i < size; i++) {
    vertexes[i].distanceToComponent = INFINI;
  }
}

static inline void allocateEdgesMemory(MST *MST, size_t numberofedges) {
  MST->edges = malloc((numberofedges) * sizeof(edge));
  if (MST->edges == NULL) {
    fprintf(stderr, "Allocation error in function computeMST");
    exit(1);
  }
}

inline int isInComponent(vertex *vertex) {
  return vertex->distanceToComponent == 0;
}

// given the new integrated vertex, update the distances to the main component
// for every not integrated vertex and returns the closest one to the main
// component
// this function does 2 things at once to avoid a second loop
size_t updateDistancesAndFindClosestVertex(vertex *vertexes, forest *forest,
                                           size_t lastIntegratedVertex) {
  double currentDist;
  size_t closestVertex = 0;
  double minDist = INFINI;
  for (size_t i = 1; i < forest->size; i++) {
    if (!isInComponent(&vertexes[i])) {
      currentDist = squaredDistanceTrees(&forest->trees[i],
                                         &forest->trees[lastIntegratedVertex]);
      if (currentDist < vertexes[i].distanceToComponent) {
        vertexes[i].distanceToComponent = currentDist;
        vertexes[i].whichVertex = lastIntegratedVertex;
      }
      if (currentDist < minDist) {
        minDist = vertexes[i].distanceToComponent;
        closestVertex = i;
      }
    }
  }
  return closestVertex;
}

inline void addNewEdge(MST *MST, size_t tree1, size_t tree2) {
  MST->edges[MST->size].tree1 = tree1;
  MST->edges[MST->size].tree2 = tree2;
  MST->size++;
}

void computeMST(forest *forest, MST *MST) {
  clock_t start = clock();
  printf("Computing MST...\n");
  printf("Projecting trees...\n");
  // equirectangularProjection(forest);
  printf("Trees projected\n");

  vertex vertexes[forest->size];
  initializeVertexes(vertexes, forest->size);

  MST->size = 0;
  allocateEdgesMemory(MST, forest->size - 1);

  size_t lastIntegratedVertex = 0;
  size_t closestVertex;
  while (MST->size < forest->size - 1) {
    closestVertex = updateDistancesAndFindClosestVertex(vertexes, forest,
                                                        lastIntegratedVertex);
    addNewEdge(MST, closestVertex, vertexes[closestVertex].whichVertex);
    loadingBar(MST->size, forest->size - 1, clock() - start);
  }
  printf("\nFinished computing MST, took %ld seconds\n",
         (int)(clock() - start) / CLOCKS_PER_SEC);
}

// /// Pour gérer le cas où on ne veut que la plus grande composante connexe

// /**
//  * @brief retourne le premier sommet pas encore traité
//  *
//  * @param composante
//  * @param size
//  * @return size_t
//  */
// size_t firstNotHandledVertex(short *composante, size_t size) {
//   for (size_t i = 0; i < size; i++) {
//     if (!composante[i]) {
//       composante[i] = 1;
//       return i;
//     }
//   }
//   return -1;
// }

// /**
//  * @brief Ajoute à currentcomposante le premier sommet non traité à
//  * distance<distmax de tree1 et itère sur ce sommet
//  *
//  * @param composante
//  * @param size
//  * @param tree
//  * @param forest
//  * @param distmax
//  * @param currentcomposante
//  */
// void addVertexes(short *composante, size_t size, size_t tree1, tree *forest,
//                  double distmax, list_t *currentcomposante) {
//   composante[tree1] = 1;
//   for (size_t i = 0; i < size; i++) {
//     if (!composante[i]) {
//       if (distanceTrees(&forest[tree1], &forest[i]) < distmax) {
//         list_append(currentcomposante, create_size_t(i));
//         addVertexes(composante, size, i, forest, distmax, currentcomposante);
//       }
//     }
//   }
// }

// /**
//  * @brief Copie le contenu de composante2 dans composante1
//  * en supposant que size(composante2) > size(composante1)
//  *
//  * @param composante1
//  * @param composante2
//  */
// void copyComposant(list_t *composante1, list_t *composante2) {
//   for (size_t i = 0; i < list_size(composante1); i++) {
//     size_t elm = *((size_t *)list_get(composante2, i));
//     list_set2(composante1, i, create_size_t(elm));
//   }
//   for (size_t i = list_size(composante1); i < list_size(composante2); i++) {
//     size_t elm = *((size_t *)list_get(composante2, i));
//     list_append(composante1, create_size_t(elm));
//   }
// }

// tree *getForestMaxComposante(tree *forest, size_t size, double distmax,
//                              size_t *newsize) {
//   clock_t start = clock();
//   short composante[size]; // si l'arbre appartient déjà à une composante
//   size_t numberOfVertexHandled = 0;

//   for (size_t i = 0; i < size; i++) {
//     composante[i] = 0;
//   }

//   list_t *composantemax = list_create();

//   while (numberOfVertexHandled < size) {
//     list_t *currentcomposante = list_create();
//     list_append(currentcomposante,
//                 create_size_t(firstNotHandledVertex(composante, size)));
//     addVertexes(composante, size, *((size_t *)list_get(currentcomposante,
//     0)),
//                 forest, distmax, currentcomposante);

//     numberOfVertexHandled += list_size(currentcomposante);
//     // loadingBar(numberOfVertexHandled, size, clock() - start);
//     if (list_size(currentcomposante) > list_size(composantemax)) {
//       ;
//       copyComposant(composantemax, currentcomposante);
//     }
//     list_free(currentcomposante);
//   }

//   tree *forest2 = malloc(sizeof(*forest2) * list_size(composantemax));

//   for (size_t i = 0; i < list_size(composantemax); i++) {
//     size_t tree = *((size_t *)list_get(composantemax, i));
//     forest2[i] = forest[tree];
//   }

//   *newsize = list_size(composantemax);
//   list_free(composantemax);
//   return forest2;
// }