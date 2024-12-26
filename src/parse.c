#include "../include/parse.h"
#include "../include/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAGIC_NUMBER 13
#define MAGIC_COOKIE "NICOLASETINES"

#include "../include/erreur.h"

// pour stocker les genres de manière plus optimisée, on décide d'établir une
// table d'indexation à chaque genre est associé un identifiant (la première
// fois qu'il a été rencontré) ces corrrespondances seront stockées dans un
// fichier texte

/* Given a certain genus, it returns the index of the genus (might evenutally
 * add it at the end of the array if it doesn"t exist yet)
 */
size_t proceedGenus(const char *genus, tab_genus *tab_corres) {
  size_t i = 0;
  for (i = 0; i < tab_corres->size; i++) {
    if (!strcmp(genus, tab_corres->genuses[i])) {
      return i;
    }
  }
  memcpy(tab_corres->genuses[tab_corres->size], genus, strlen(genus) + 1);
  tab_corres->size++;
  return tab_corres->size - 1;
}

static void getGenus(char **current, tree *tree, tab_genus *genus_save_tab) {
  (*current)++; // skipping the first comma
  char genus[MAX_GENUS_NAME_SIZE + 1];
  memset(genus, 0, MAX_GENUS_NAME_SIZE + 1);

  size_t i = 0;
  while ((*current)[i] != ';') {
    genus[i] = (*current)[i];
    i++;
  }
  genus[i] = '\0';

  tree->genus = proceedGenus(genus, genus_save_tab);
  (*current) += i - 1;
}

inline void getHeight(char **current, tree *tree) {
  tree->height = atoi(*current);
}

#define POSITION_X_SIZE 17

static void getPosition(char **current, tree *tree) {
  (*current)++; // skipping the first comma
  char posX[POSITION_X_SIZE + 1];
  memccpy(posX, *current, ',', POSITION_X_SIZE);
  posX[POSITION_X_SIZE] = '\0';
  tree->position.coord_1.latitude = atof(posX);
  tree->position.coord_2.longitude = atof(*current + POSITION_X_SIZE + 1);
}

#define MAX_LINE_SIZE 500 // arbitraty value that seems reasonable

static void parseCSVLine(char *line, tree *tree, tab_genus *genus_save_tab) {
  char *current = line;
  int count_semi_colon = 0;
  while (*current != '\n') {
    if (*current == ';') {
      count_semi_colon++;
    }
    if (count_semi_colon == 9) {
      getGenus(&current, tree, genus_save_tab);
    }
    if (count_semi_colon == 13) {
      getHeight(&current, tree);
    }
    if (count_semi_colon == 16) {
      getPosition(&current, tree);
      return; // exiting earlier because we don't need to parse the rest of
              // the line
    }
    current++;
  }
}

static void parseCSVFile(FILE *file, forest *forest,
                         tab_genus *genus_save_tab) {
  printf("Parsing csv file\n");

  char line[MAX_LINE_SIZE + 1];
  forest->size = -1;
  while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
    forest->size++;
  }
  forest->trees = malloc(forest->size * sizeof(tree));
  rewind(file);

  if (fgets(line, MAX_LINE_SIZE, file) == NULL) {
    fprintf(stderr, "File is only one line long, strange, aborting\n");
    exit(EXIT_FAILURE);
  }

  char *current = line;
  size_t i = 0;
  while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
    parseCSVLine(current, &forest->trees[i], genus_save_tab);
    i++;
  }

  printf("Data has been succesfully read\n");
}

static void saveToBinaryFile(forest *forest, const char *file_path) {
  FILE *out;
  CHK((out = fopen(file_path, "wb")) == NULL);

  // write header
  if (fwrite(MAGIC_COOKIE, MAGIC_NUMBER, 1, out) != 1) {
    exit(EXIT_FAILURE);
  }

  // write number of trees
  if (fwrite(&forest->size, sizeof(forest->size), 1, out) != 1) {
    exit(EXIT_FAILURE);
  }

  // write trees informations
  if (fwrite(forest->trees, sizeof(tree), forest->size, out) != forest->size) {
    exit(EXIT_FAILURE);
  }

  printf("Conversion to binary format ended succesfully\n");
  CHK(fclose(out));
}

void parseFromBinaryFile(const char *file_path, forest *forest) {
  printf("Parsing from binary file\n");
  FILE *in;
  CHK((in = fopen(file_path, "rb")) == NULL);
  // todo check return value

  // header has been checked previously so we can just skip it
  fseek(in, MAGIC_NUMBER, SEEK_SET);

  // read number of trees
  if (fread(&forest->size, sizeof(forest->size), 1, in) != 1) {
    exit(EXIT_FAILURE);
  }

  // allocate memory for trees
  forest->trees = malloc(forest->size * sizeof(tree));

  // read trees informations
  if (fread(forest->trees, sizeof(tree), forest->size, in) != forest->size) {
    exit(EXIT_FAILURE);
  }

  if (fclose(in) != 0) {
    raler("fclose", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  printf("Data was succesfully read from BinaryFile\n");
}

void saveGenusCorrespondance(const char *file_path, tab_genus *tab) {
  FILE *out;
  CHK((out = fopen(file_path, "w")) == NULL);

  // write number of genuses
  fprintf(out, "%zu\n", tab->size);

  for (size_t i = 0; i < tab->size; i++) {
    fprintf(out, "%s\n", tab->genuses[i]);
  }

  CHK(fclose(out) != 0);
}

static int isBinary(FILE *file) {
  char line[MAGIC_NUMBER + 1];
  if (fread(line, MAGIC_NUMBER, 1, file) != 1) {
    exit(EXIT_FAILURE);
  }
  line[MAGIC_NUMBER] = 0;
  return !(strcmp(line, MAGIC_COOKIE));
}

void writeEdges(edge *MST, size_t size, opt handlingOptions) {

  if (handlingOptions.span_tree_path == NULL) {
    return;
  }

  FILE *out = fopen(handlingOptions.span_tree_path, "w");
  if (out == NULL) {
    fprintf(stderr, "Unable to open %s in function writeEdges\n",
            handlingOptions.span_tree_path);
    exit(16);
  }

  size_t nbTrees = size;
  fwrite(&nbTrees, sizeof(size_t), 1, out);

  // for (size_t i = 0; i < size; i++) {
  //   fwrite(&MST[i].tree1, sizeof(MST[i].tree1), 1, out);
  //   fwrite(&MST[i].tree2, sizeof(MST[i].tree2), 1, out);
  // }

  if (fclose(out) != 0) {
    exit(17);
  }
}

void restoreGenus(const char *file_path, forest *forest, tab_genus *tab) {
  FILE *in;
  CHK((in = fopen(file_path, "r")) == NULL);

  // get number of genuses
  fread(&tab->size, sizeof(tab->size), 1, in);

  // get genuses
  for (size_t i = 0; i < tab->size; i++) {
    fgets(tab->genuses[i], MAX_GENUS_NAME_SIZE, in);
    tab->genuses[i][strlen(tab->genuses[i]) - 1] = 0; // removing the \n
  }

  // restore genuses
  for (size_t i = 0; i < forest->size; i++) {
    forest->trees[i].genus =
        proceedGenus(tab->genuses[forest->trees[i].genus], tab);
  }

  CHK(fclose(in) != 0);
}

void loadAndParseFile(opt *option, forest *forest) {
  FILE *in;
  CHK((in = fopen(option->in_path, "r")) == NULL);

  tab_genus genus_save_tab;
  memset(&genus_save_tab, 0, sizeof(tab_genus));
  if (isBinary(in)) {
    if (option->genus_recharge_path == NULL) {
      fprintf(stderr, "You used a binary file to load data but did not specify "
                      "any gender correspondance table\n");
      exit(EXIT_FAILURE);
    }
    parseFromBinaryFile(option->in_path, forest);
    restoreGenus(option->genus_recharge_path, forest, &genus_save_tab);
    CHK(fclose(in) != 0);
    return;
  }

  // else : file is csv
  parseCSVFile(in, forest, &genus_save_tab);
  saveToBinaryFile(forest, option->out_path);
  saveGenusCorrespondance(option->genus_conserve_path, &genus_save_tab);

  CHK(fclose(in) != 0);
}
