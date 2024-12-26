#pragma once
#include "struct.h"
#include <stdio.h>

/**
 * @brief Cette fonction écrit dans un fichier l'arbre recouvrant minimal
 *
 * @param file Le fichier dans lequel on écrit
 * @param arbre L'arbre recouvrant minimal
 * @param size Sa taille
 */
void writeEdges(edge *MST, size_t size, opt handlingOptions);

// load the file parsed in CLI
void loadAndParseFile(opt *option, forest *forest);

// testing purposes

#ifdef TEST_BUILD

void getHeight(char **current, tree *tree);

#endif