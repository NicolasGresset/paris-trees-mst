#include "../include/options.h"
#include "../include/struct.h"
#include "../include/stat.h"
#include "../include/algo.h"
#include <stdio.h>
#include "../include/fonctions.h"
#include "../include/pile.h"
#include "../include/array-list.h"

#define INFINI 4000000

/*double averageHeight(tree * trees,int size){

    int sum = 0;
    for(int i=0;i<size;i++){ sum += trees[i].height; }
    return sum/(double)size;
}*/

double weightMinimumSpanningTree(edge* MST, size_t size){
    double weight = 0;
    for (size_t i = 0; i<size; i++){
        weight += distanceTrees(MST[i].tree1, MST[i].tree2);
    }
    return RAYON*sqrt(weight);
}

void stat(opt handlingOptions, edge * MST,size_t size, tree* forest){ // size est la taille de forest

    if(handlingOptions.stat == 1) {

        printf("Nombre d'arbres : %ld\n",size);
        printf("Degré moyen : %ld/%ld soit %lf\n",2*(size-1),size, 2*(size-1)/(double)size);

        double weight = weightMinimumSpanningTree(MST, size - 1);
        printf("Poids du minimum spanning tree : %lfm\n",weight);

        printf("Le diamètre du graphe vaut %fm\n", diameterMST(MST, forest, size));

    }

}


edge2* otherMST(edge* MST, size_t size, tree* forest){ //size correspond au nombre d'arbres ie la taille de forest
    edge2* otherMST = malloc((size - 1)*sizeof(*otherMST));
    if (otherMST == NULL){
        fprintf(stderr, "Allocation error in generateMST\n");
        exit(1);
    }

    for (size_t i = 0; i<size - 1; i++){
        otherMST[i].tree1 = (size_t)(MST[i].tree1 - forest);
        otherMST[i].tree2 = (size_t)(MST[i].tree2 - forest);
    }

    return otherMST;
}

node* newMST(edge2* MST, size_t size){
    node* newmst = malloc(size*sizeof(*newmst));
    if (newmst == NULL){
        fprintf(stderr, "Allocation error in newmst\n");
        exit(1);
    }

    for (size_t i = 0; i<size; i++){
        newmst[i].neighbors = list_create();
    }

    size_t currenttree1, currenttree2;
    for (size_t i = 0; i<size - 1; i++){
        currenttree1 = MST[i].tree1;
        currenttree2 = MST[i].tree2;

        list_append(newmst[currenttree1].neighbors, create_size_t(currenttree2));
        list_append(newmst[currenttree2].neighbors, create_size_t(currenttree1));

    }

    return newmst;
}

double exentricityVertex(node* MST, size_t size, size_t current_tree, tree* forest, size_t *excentricVertex){
    double excentricity = 0;
    double distance[size];
    for (size_t i = 0; i<size; i++){
        distance[i] = INFINI;
    }
    distance[current_tree] = 0;

    pile_t* pile = pile_create();
    size_t *s = create_size_t(current_tree);
    push(pile, s);

    while (!is_empty(pile)){
        void* vertex = pop(pile);
        size_t x = *((size_t*)vertex);
        free(vertex);

        for (size_t i = 0; i<list_size(MST[x].neighbors); i++){
            size_t *y = create_size_t(*((size_t*)list_get(MST[x].neighbors, i)));

            if (distance[*y] == INFINI){
                push(pile, y);
                distance[*y] = distance[x] + distanceTrees(&forest[x], &forest[*y]);
                if (distance[*y] > excentricity){
                    excentricity = distance[*y];
                    *excentricVertex = *y;
                }
                
            }
            else{
                free(y);
            }
        }
    }
    pile_free(pile);
    return excentricity;
}

void freeNode(node* listofnodes, size_t size){
    for (size_t i = 0; i<size; i++){
        list_free(listofnodes[i].neighbors);
    }
    free(listofnodes);
}


double diameterMST(edge* MST, tree* forest, size_t size){ //size correspond à la taille de forest
    edge2* othermst = otherMST(MST, size, forest);
    node* newmst = newMST(othermst, size);

    free(othermst);
    size_t v = 0, w = 0;
    exentricityVertex(newmst, size, 0, forest, &v);
    double excentricity =  exentricityVertex(newmst, size, v, forest, &w);

    freeNode(newmst, size);
    return RAYON*sqrt(excentricity);
}

