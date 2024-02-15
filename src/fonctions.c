#include "../include/fonctions.h"
#include <math.h>
#include "../include/algo.h"
#include "../include/stat.h"
#include "../include/display.h"
#include "../include/parse.h"


/**
 * @brief Get the Mean Longitude object
 * Renvoie la longitude moyenne des arbres de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double getMeanLongitude(tree* forest, size_t size){
    double meanLongitude = 0;
    for (size_t i = 0; i<size; i++){
        meanLongitude += forest[i].geoloc.y;
    }
    return meanLongitude/size;
}

/**
 * @brief Get the Mean Latitude object
 * Renvoie la latitude moyenne des arbres de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double getMeanLatitude(tree* forest, size_t size){
    double meanLatitude = 0;
    for (size_t i = 0; i<size; i++){
        meanLatitude += forest[i].geoloc.x;
    }
    return meanLatitude/size;
}


void projectionTrees(tree* forest, size_t size){
    double phi0 = getMeanLatitude(forest, size);
    double lambda0 = getMeanLongitude(forest, size);
    double cosphi0 = cos(phi0*M_PI/180);

    for(size_t i = 0; i<size; i++){
        double oldx = forest[i].geoloc.x;
        forest[i].geoloc.x = cosphi0*(forest[i].geoloc.y - lambda0)*M_PI/180;
        forest[i].geoloc.y = (oldx - phi0)*M_PI/180;
    }
}

double distanceTrees(tree* tree1, tree* tree2){
	return ((pow(tree1->geoloc.x - tree2->geoloc.x, 2) + pow(tree1->geoloc.y - tree2->geoloc.y, 2)));
}


void manageActions(tree* forest, size_t size, edge** MST, opt handlingOptions){
    *MST = minimumSpanningTree(forest, size);
    stat(handlingOptions, *MST, size, forest);
    displayTrees(*MST, size, forest);
    writeEdges(*MST, size - 1, handlingOptions);
}