#include "../include/stat.h"
#include "../include/algo.h"
#include "../include/array-list.h"
#include "../include/fonctions.h"
#include "../include/options.h"
#include "../include/pile.h"
#include "../include/struct.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINI 4000000

// on peut trouver le diamètre d'un arbre en choisissant un sommet arbitraire
// n1, en trouvant le sommet n2 le plus éloigné de n1 ; puis en trouvant le
// sommet n3 le plus éloigné de n2
// la distance entre n2 et n3 est le diamètre de l'arbre

typedef struct {
  dynamic_list *neighbors;
} node;

typedef struct {
  node *nodes;
  size_t size;
} graph;

void freeGraph(graph *graph) {
  for (size_t i = 0; i < graph->size; i++) {
    list_free(graph->nodes[i].neighbors);
  }
  free(graph->nodes);
}

void allocateGraph(graph *graph) {
  graph->nodes = malloc(graph->size * sizeof(node));
  for (size_t i = 0; i < graph->size; i++) {
    graph->nodes[i].neighbors = list_create();
  }
}

void getGraphFromMST(MST *MST, graph *graph) {
  graph->size = MST->size + 1;
  allocateGraph(graph);
  for (size_t i = 0; i < MST->size; i++) {
    list_append(graph->nodes[MST->edges[i].tree1].neighbors,
                MST->edges[i].tree2);
    list_append(graph->nodes[MST->edges[i].tree2].neighbors,
                MST->edges[i].tree1);
  }
}

#define NOT_VISITED -1

// pour un sommet vertex donné, renvoie la distance au sommet le plus
// éloigné de current_vertex et met l'index de ce sommet dans excentric_vertex
// utilise un parcours en largeur avec une structure de pile
double getExcentricVertex(graph *graph, forest *forest, size_t vertex,
                          size_t *excentric_vertex) {
  double excentricity = 0; // distance maximale trouvée
  double distance[graph->size];
  for (size_t i = 0; i < graph->size; i++) {
    distance[i] = NOT_VISITED;
  }
  distance[vertex] = 0;

  pile *pile = pile_create();
  push(pile, vertex);
  size_t current;
  while (!is_empty(pile)) {
    current = pop(pile);

    size_t neighbor;
    for (size_t i = 0; i < list_size(graph->nodes[current].neighbors); i++) {
      neighbor = list_get(graph->nodes[current].neighbors, i);

      if (distance[neighbor] == NOT_VISITED) {
        push(pile, neighbor);
        distance[neighbor] =
            distance[current] +
            distanceTrees(&forest->trees[current], &forest->trees[neighbor]);

        // update excentricity
        if (distance[neighbor] > excentricity) {
          excentricity = distance[neighbor];
          *excentric_vertex = neighbor;
        }
      }
    }
  }
  pile_free(pile);
  return excentricity;
}

// https://www.quora.com/Why-is-it-sufficient-to-run-BFS-only-two-times-in-order-to-find-the-diameter-of-an-N-ary-tree
double diameterMST(MST *MST, forest *forest) {
  // on a besoin de faire un parcours en largeur du graphe pour trouver le
  // diamètre il faut donc qu'on se fasse une autre représentation de l'arbre,
  // une liste d'arêtes ne convient pas
  graph graph;
  getGraphFromMST(MST, &graph);

  size_t arbitraty_vertex = 0;
  size_t extremity1, extremity2;
  getExcentricVertex(&graph, forest, arbitraty_vertex, &extremity1);
  double diameter = getExcentricVertex(&graph, forest, extremity1, &extremity2);
  freeGraph(&graph);
  printf("extremity1 : %ld, extremity2 : %ld\n", extremity1, extremity2);
  return diameter;
}

double weightMinimumSpanningTree(MST *MST, forest *forest) {
  double weight = 0;
  for (size_t i = 0; i < MST->size; i++) {
    weight += distanceTrees(&forest->trees[MST->edges->tree1],
                            &forest->trees[MST->edges->tree2]);
  }
  return weight;
}

void dumpStats(MST *MST, forest *forest) {
  printf("Nombre d'arbres : %ld\n", forest->size);
  printf("Degré moyen : %ld/%ld soit %lf\n", 2 * (forest->size - 1),
         forest->size,
         2 * (forest->size - 1) /
             (double)forest->size); // todo verifier que c'est bien ce résultat

  double weight = weightMinimumSpanningTree(MST, forest);
  printf("Poids de l'arbre couvrant minimal : %lf\n", weight);

  double diameter = diameterMST(MST, forest);
  printf("Diamètre de l'arbre couvrant minimal : %lf\n", diameter);
}
