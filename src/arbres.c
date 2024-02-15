#include <stdio.h>
#include "../include/struct.h"
#include "../include/fonctions.h"
#include "../include/options.h"
#include "../include/parse.h"
#include "../include/algo.h"
#include "../include/display.h"
#include "../include/stat.h"
#include "../include/restrictiveOptions.h"

/**
 * @mainpage
 * 
 * \section sous_titre Voici le projet 1A IR 2022-2023 de Inès LEMESLE et Nicolas GRESSET-BOURGOIS. 
 * 
 *
 * \subsection step1 *Commande type à entrer en ligne de commande :
 *  
 *     ./bin/arbres -i in_path.csv -o out_path -c save-struct-genre -f 1,1,50,50 -s -g Acer -h 10
 * 
 *     ./bin/arbres -i in_path.bin -o out_path -r save-struct-genre -f 1,1,50,50 -s -g Acer -h 10
 * 
 * 
 * \subsection step2 *Les différentes options implémentées :
 * 
 *     -Attention les options -i ... et -o ... et (-c ... ou -r ...) sont nécessaires au lancement du programme
 * 
 *     -Possibilité de sauvegarder les informations du minimum spanning tree dans un fichier (-t ...)
 * 
 *     -Possibilité de choisir le genre de l'arbre (-g ...)
 * 
 *     -Possibilité de choisir la hauteur de l'arbre (-h ...)
 * 
 *     -Possibilité de choisir un carré limite de géolocalisation (-f ...)
 * 
 *     -Possibilité de voir les statistiques du graphe (-s)
 *      
 *     -Possibilité de mettre une distance maximale en mètres entre 2 arbres et ne récupérer que la plus grande composante connexe (-l ...)
 * 
 *  \subsection step3 *Tests disponibles :
 *    
 *      -Test de la bonne gestion des options (test_option)
 * 
 *      -Test de la réalisation du parsage (test_parsage)
 * 
 *      -Test de la validité de la valeur des distances entre les arbres (test-distance)
 * 
 *      -Test de la reconnaissance d'un fichier binaire ou non (test-binary)
 * 
 *      -Test arrêt du programme si fichier non existant (test_error_file)
 * 
 *      -Test correspondance entre les identifiants associés aux genres et les genres eux-mêmes (test_corres_genus)
 */


int main(int argc, char ** argv){
    (void)argc;

    opt handlingOptions;
    options(argc,argv,&handlingOptions);
    
    int size;
    tree * trees=malloc(300000*sizeof(tree));
    if(trees == NULL) { exit(15); }
    memset(trees,0,sizeof(*trees)*300000);
    handlingFile(handlingOptions,trees,&size);
    
    int sizeSelection;
    tree * treesSelection=malloc(300000*sizeof(tree));
    if(treesSelection == NULL){ exit(15); }
    edge * MST;
    char * endPointer;
    size_t newsize;

    projectionTrees(trees, size);

    
    if(handlingOptions.height == NULL && handlingOptions.genus == NULL && handlingOptions.limit_value == NULL){ 

        if(handlingOptions.location != NULL) {
            tree* treesSelection2 = getForestMaxComposante(trees, size, pow(strtod(handlingOptions.location,&endPointer)/RAYON, 2), &newsize);
            manageActions(treesSelection2, newsize, &MST, handlingOptions);
            free(treesSelection2);
        }else{
            manageActions(trees, size, &MST, handlingOptions);
        }

    }else{   
        handlingRestrictingOptions(handlingOptions,trees,treesSelection,size,&sizeSelection); 
        if(handlingOptions.location != NULL) {
            tree* treesSelection2 = getForestMaxComposante(treesSelection, sizeSelection, pow(strtod(handlingOptions.location,&endPointer)/RAYON, 2), &newsize);
            manageActions(treesSelection2, newsize, &MST, handlingOptions);
            free(treesSelection2);
        }else{
            manageActions(treesSelection, sizeSelection, &MST, handlingOptions);
        }

    }

    free(MST);
    free(trees);
    free(treesSelection);
    return 0;
}
