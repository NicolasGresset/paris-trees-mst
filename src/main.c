#include "../include/algo.h"
#include "../include/options.h"
#include "../include/parse.h"
#include "../include/stat.h"
#include "../include/struct.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @mainpage
 *
 * \section sous_titre Voici le projet 1A IR 2022-2023 de Inès LEMESLE et
 * Nicolas GRESSET-BOURGOIS.
 *
 *
 * \subsection step1 *Commande type à entrer en ligne de commande :
 *
 *     ./bin/arbres -i in_path.csv -o out_path -c save-struct-genre -f 1,1,50,50
 * -s -g Acer -h 10
 *
 *     ./bin/arbres -i in_path.bin -o out_path -r save-struct-genre -f 1,1,50,50
 * -s -g Acer -h 10
 *
 *
 * \subsection step2 *Les différentes options implémentées :
 *
 *     -Attention les options -i ... et -o ... et (-c ... ou -r ...) sont
 * nécessaires au lancement du programme
 *
 *     -Possibilité de sauvegarder les informations du minimum spanning tree
 * dans un fichier (-t ...)
 *
 *     -Possibilité de choisir le genre de l'arbre (-g ...)
 *
 *     -Possibilité de choisir la hauteur de l'arbre (-h ...)
 *
 *     -Possibilité de choisir un carré limite de géolocalisation (-f ...)
 *
 *     -Possibilité de voir les statistiques du graphe (-s)
 *
 *     -Possibilité de mettre une distance maximale en mètres entre 2 arbres et
 * ne récupérer que la plus grande composante connexe (-l ...)
 *
 *  \subsection step3 *Tests disponibles :
 *
 *      -Test de la bonne gestion des options (test_option)
 *
 *      -Test de la réalisation du parsage (test_parsage)
 *
 *      -Test de la validité de la valeur des distances entre les arbres
 * (test-distance)
 *
 *      -Test de la reconnaissance d'un fichier binaire ou non (test-binary)
 *
 *      -Test arrêt du programme si fichier non existant (test_error_file)
 *
 *      -Test correspondance entre les identifiants associés aux genres et les
 * genres eux-mêmes (test_corres_genus)
 */

void test(forest *forest) {
  for (size_t i = 0; i < forest->size; i++) {
    printf("tree %ld : %d %f %f\n", i, forest->trees[i].height,
           forest->trees[i].position.coord_1.latitude,
           forest->trees[i].position.coord_2.longitude);
  }
}

int main(int argc, char **argv) {
  opt options;
  forest forest;
  MST MST;

  handleCLI(argc, argv, &options);
  loadAndParseFile(&options, &forest);
  computeMST(&forest, &MST);

  // writeEdges(options) // on s'en tape non ?
  if (options.stat) {
    dumpStats(&MST, &forest);
  }
  // displayMST(options) // à faire avec la SDL

  free(forest.trees);
  free(MST.edges);
  return 0;
}
