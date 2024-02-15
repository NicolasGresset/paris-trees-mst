#include "../include/algo.h"
#include "../include/fonctions.h"
#include "../include/struct.h"
#include <stdlib.h>
#include "../include/display.h"
#include <time.h>


#define INFINI 4000000



size_t vertexDistMin(vertex* tab, size_t size){
    double distmin = tab[0].distMin;
    size_t imin = 0;
    for (size_t i = 0; i<size; i++){
        if ( (tab[i].distMin < distmin) && !tab[i].isInComponent){
            distmin = tab[i].distMin;
            imin = i;
        }
    }
    return imin;
}

edge* minimumSpanningTree(tree* forest, size_t size){
    clock_t start = clock();
    vertex tab[size];
    size_t sizeOfComposante = 1;
    double minimumDistance = INFINI;
    
    for (size_t i = 0; i<size; i++){
        tab[i].distMin = minimumDistance;
        tab[i].vertexMin = 0;
        tab[i].isInComponent = 0;
    }
    tab[0].isInComponent = 1;

    edge* listeOfAretes = malloc((size - 1)*sizeof(edge));
    if (listeOfAretes== NULL){
        fprintf(stderr, "Allocation error in function arbreRecouvrantMinimal");
        exit(1);
    }

    size_t minimumVertex;
    size_t lastHandledVertex = 0;
    double currentDist;

    while(sizeOfComposante <= size - 1){ //nb aretes <= nsommets - 1
        for (size_t i = 0; i<size; i++){ //sur tous les arbres de la structure sauf le premier
            if ( !tab[i].isInComponent){ //sommet pas dans la composante connexe
                if ( (currentDist = distanceTrees(&forest[i], &forest[lastHandledVertex])) < tab[i].distMin){
                    tab[i].distMin = currentDist;
                    tab[i].vertexMin = lastHandledVertex;
                }
            } 
        }

        minimumVertex = vertexDistMin(tab, size);          

        listeOfAretes[sizeOfComposante-1].tree1 = &forest[minimumVertex];
        listeOfAretes[sizeOfComposante-1].tree2 = &forest[tab[minimumVertex].vertexMin];
        sizeOfComposante++;
        lastHandledVertex = minimumVertex;
        tab[minimumVertex].isInComponent= 1;
        loadingBar(sizeOfComposante - 1, size - 1, clock() - start);      
    }

    printf("\nCalcul de l'arbre recouvrant minimal terminé \n");
    return listeOfAretes;
}



/// Pour gérer le cas où on ne veut que la plus grande composante connexe

/**
 * @brief retourne le premier sommet pas encore traité
 * 
 * @param composante 
 * @param size 
 * @return size_t 
 */
size_t firstNotHandledVertex(short*  composante, size_t size){
    for (size_t i = 0; i<size; i++){
        if (!composante[i]) {
            composante[i] = 1;
            return i;
        }
    }
    return -1;
}

/**
 * @brief Ajoute à currentcomposante le premier sommet non traité à distance<distmax de tree1 et itère sur ce sommet
 * 
 * @param composante 
 * @param size 
 * @param tree 
 * @param forest 
 * @param distmax 
 * @param currentcomposante 
 */
void addVertexes(short* composante, size_t size, size_t tree1, tree* forest, double distmax, list_t* currentcomposante){
    composante[tree1] = 1;
    for (size_t i = 0; i<size; i++){
        if (!composante[i]){
            if (distanceTrees(&forest[tree1], &forest[i]) < distmax){
                list_append(currentcomposante, create_size_t(i));
                addVertexes(composante, size, i, forest, distmax, currentcomposante);
            }
        }
    }
}


/**
 * @brief Copie le contenu de composante2 dans composante1
 * en supposant que size(composante2) > size(composante1)
 * 
 * @param composante1 
 * @param composante2 
 */
void copyComposant(list_t* composante1, list_t* composante2){
    for (size_t i = 0; i<list_size(composante1); i++){
        size_t elm = *((size_t*)list_get(composante2, i));
        list_set2(composante1, i, create_size_t(elm));
    }
    for (size_t i = list_size(composante1); i<list_size(composante2); i++){
        size_t elm = *((size_t*)list_get(composante2, i));
        list_append(composante1, create_size_t(elm));
    }
}



tree* getForestMaxComposante(tree* forest, size_t size, double distmax, size_t* newsize){
    clock_t start = clock();
    short composante[size]; //si l'arbre appartient déjà à une composante
    size_t numberOfVertexHandled = 0;

    for (size_t i = 0; i<size; i++){
        composante[i] = 0;
    }

    list_t* composantemax = list_create();


    while (numberOfVertexHandled < size){
        list_t* currentcomposante = list_create();
        list_append(currentcomposante, create_size_t(firstNotHandledVertex(composante, size)));
        addVertexes(composante, size, *((size_t*)list_get(currentcomposante, 0)), forest, distmax, currentcomposante);

        numberOfVertexHandled+=list_size(currentcomposante);
        loadingBar(numberOfVertexHandled, size, clock() - start);
        if (list_size(currentcomposante) > list_size(composantemax)){;
            copyComposant(composantemax, currentcomposante);
        }
        list_free(currentcomposante);
    }

    tree* forest2 = malloc(sizeof(*forest2)*list_size(composantemax));

    for (size_t i = 0; i<list_size(composantemax); i++){
        size_t tree = *((size_t*)list_get(composantemax, i));
        forest2[i] = forest[tree];
    }
    
    *newsize = list_size(composantemax);
    list_free(composantemax);
    return forest2;
}