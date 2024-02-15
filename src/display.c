#include "../include/display.h"
#include "../include/struct.h"
#include <tps.h>


#define HEIGHT 800
#define WIDTH 800

void infoDisplay(void){
    printf("**********************************************\n");
    printf("Pour zoomer appuyer sur p.\n");
    printf("Pour dézoomer appuyer sur m.\n");
    printf("Pour se déplacer utiliser les flèches.\n");
    printf("\n**********************************************\n");
}


/**
 * @brief Effectue une transformation affine des coordonnées des arbres
 * de la liste forest de taille size, de manière à recadrer les arbres
 * dans la fenêtre de taille WIDTH*HEIGHT, et à prendre compte du zoom
 * et du déplacement avec les flèches
 * 
 * @param forest 
 * @param size 
 * @param zoom 
 * @param left 
 * @param up 
 */
void scaleTree(tree* forest, size_t size, int zoom, int left, int up){
    double xmin, xmax, ymin, ymax;
    getExtremum(forest, size, &xmin, &ymin, &xmax, &ymax);


    double alpha = (WIDTH)/(xmax - xmin )*(1+ 0.02*zoom);
    double beta = (HEIGHT)/(ymax - ymin )*(1+ 0.02*zoom);

    for (size_t i = 0; i<size; i++){
            forest[i].geoloc.x = (forest[i].geoloc.x - xmin ) * alpha - 10*zoom + 5*left;
            forest[i].geoloc.y = (forest[i].geoloc.y - ymin ) * beta - 10*zoom + 5*up;
    }
    return;
}

void displayTrees(edge* edgeList, size_t size, tree* forest){
    infoDisplay();
    
    size--;
    double x1, x2, y1, y2;
    tps_createWindow("Arbres de Paris", WIDTH, HEIGHT);
    tps_background(255, 255, 255);
    tps_setColor(0, 0, 0);
    scaleTree(forest, size + 1,0,0,0);

    for (size_t i = 0; i<size; i++){
        x1 = edgeList[i].tree1->geoloc.x;
        y1 = edgeList[i].tree1->geoloc.y;
        x2 = edgeList[i].tree2->geoloc.x;
        y2 = edgeList[i].tree2->geoloc.y;
        tps_drawLine(x1, y1, x2, y2);
    }
    
    int zoom=0;
    int left=0;
    int up=0;
    while(tps_isRunning()){
        
        if(tps_getKeyPressed() == SDLK_p ) {zoom++;}
        if(tps_getKeyPressed() == SDLK_m ) {zoom--;}

        if(tps_getKeyPressed() == SDLK_LEFT ) {left++;}
        if(tps_getKeyPressed() == SDLK_RIGHT ) {left--;}

        if(tps_getKeyPressed() == SDLK_UP ) {up++;}
        if(tps_getKeyPressed() == SDLK_DOWN ) {up--;}
        

        tps_background(255, 255, 255);
        scaleTree(forest, size + 1,zoom,left,up);
        for (size_t i = 0; i<size; i++){
            x1 = edgeList[i].tree1->geoloc.x;
            y1 = edgeList[i].tree1->geoloc.y;
            x2 = edgeList[i].tree2->geoloc.x;
            y2 = edgeList[i].tree2->geoloc.y;
            tps_drawLine(x1, y1, x2, y2);
        }
        
        tps_render();
    }    
    tps_closeWindow();
    return;
}




/**
 * @brief Renvoie le champ geoloc.x minimum de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double minX(tree* forest, size_t size){
    size_t i = 0;
    double distMin = forest[i].geoloc.x;

    for (i = 1; i<size; i++){
        if (forest[i].geoloc.x < distMin) distMin = forest[i].geoloc.x;
    }

    return distMin;
}

/**
 * @brief Renvoie le champ geoloc.y minimum de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double minY(tree* forest, size_t size){
    size_t i = 0;
    double distMin = forest[i].geoloc.y;

    for (i = 1; i<size; i++){
        if (forest[i].geoloc.y < distMin) distMin = forest[i].geoloc.y;
    }

    return distMin;
}

/**
 * @brief Renvoie le champ geoloc.x maximum de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double maxX(tree* forest, size_t size){
    size_t i = 0;
    double distMax = forest[i].geoloc.x;

    for (i = 1; i<size; i++){
        if (forest[i].geoloc.x > distMax) distMax = forest[i].geoloc.x;
    }

    return distMax;
}

/**
 * @brief Renvoie le champ geoloc.y maximum de la liste forest de taille size
 * 
 * @param forest 
 * @param size 
 * @return double 
 */
double maxY(tree* forest, size_t size){
    size_t i = 0;
    double distMax = forest[i].geoloc.y;

    for (i = 1; i<size; i++){
        if (forest[i].geoloc.y > distMax) distMax = forest[i].geoloc.y;
    }

    return distMax;
}


void getExtremum(tree* forest, size_t size, double* minimumX,
double* minimumY, double* maximumX, double* maximumY){
    *minimumX = minX(forest, size);
    *minimumY = minY(forest, size);
    *maximumX = maxX(forest, size);
    *maximumY = maxY(forest, size);
}

void loadingBar(int current, int total, clock_t delta){
    static double previoustime = 0;
    double newtime;
    if (current != total && current%100 == 0){
        printf("%d/%d -- ", current, total);
        printf("Time since beginning : %fs -- ", ((double)delta)/CLOCKS_PER_SEC);
        newtime = 0.5*previoustime + 0.5*(((double)(delta * ((float)total/(float)current)))/CLOCKS_PER_SEC);
        printf("Time left estimated : %fs\r", newtime - ((double)delta)/CLOCKS_PER_SEC);
        previoustime = newtime;
    }

    else if(current == total){
        printf("%d/%d -- ", current, total);
        printf("Time since beginning : %fs -- ", ((double)delta)/CLOCKS_PER_SEC);
        printf("Time left estimated : 0\n");
    }
}