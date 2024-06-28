#include "../include/struct.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void help(void) {
  printf("\n*******************************************************************"
         "***************************************\n");
  printf("i option (followed by a path) : path of the file you want to parse "
         "[csv or binary]\n");
  printf("c option (followed by a path) : path of the file where you want to "
         "save your gender correspondance table (if use of csv file)\n");
  printf("r option (followed by a path) : path of the file from where you want "
         "to load your gender correspondance table (if use of binary file)\n");
  printf("o option (followed by a path) : path of the file where you save the "
         "binary version of your input [binary]\n");
  printf("t option (followed by a path) : path of the file saving the minimum "
         "panning tree informations\n");
  printf("l option (followed by a positive int) : maximum distance allowed "
         "betwween your trees [meters]\n");
  printf("s option (no arguments) : to get statistics on the tree\n");
  printf("f option (followed by 4 positives int) : x minimum X1, y minimum "
         "Y1,x maximum X2, y maximum Y2 [°]\n");
  printf("g option (followed by a string) : to get a mimimum spanning tree "
         "only considering this genus\n");
  printf("h option (followed by an positive int) :  to get a mimimum spanning "
         "tree only considering at most this height [meters]\n");
  printf("*********************************************************************"
         "*************************************\n");
}

void handleCLI(int argc, char **argv, opt *options) {

  memset(options, 0, sizeof(opt));
  int c;
  while ((c = getopt(argc, argv, "i:o:t:l:sf:g:h:c:r:a")) != -1) {
    switch (c) {
    case 'i':
      options->in_path = optarg; // required
      break;
    case 'o':
      options->out_path = optarg; // only required if input is csv
      break;
    case 't':
      options->span_tree_path = optarg; // optional
      break;
    case 'f': // optional
      // todo change this to reflect what the acutal options wants to do (4
      // values representing a square in between the trees must only be
      // considered)
      options->limit_value = optarg;
      if (atoi(options->limit_value) <= 0) {
        fprintf(stderr, "The limit %d must be a positive value",
                atoi(options->limit_value));
        help();
        exit(EXIT_FAILURE);
      }
      break;
    case 's': // optional
      options->stat = 1;
      break;
    case 'l':
      options->max_distance = atoi(optarg); // optional
      break;
    case 'g':
      options->genus = optarg; // optional
      break;
    case 'h':
      options->height = atoi(optarg);
      if (options->height <= 0) {
        fprintf(stderr, "The height %d must be a positive value",
                options->height);
        help();
        exit(EXIT_FAILURE);
      }
      break;
    case 'c': // only required in case of csv
      options->genus_conserve_path = optarg;
      break;
    case 'r': // only required in case of binary
      options->genus_recharge_path = optarg;
      break;
    case 'a':
      options->help = 1;
      help();
      break;

    case '?':

      if (optopt == 'i' || optopt == 'o' || optopt == 't' || optopt == 'l' ||
          optopt == 'f' || optopt == 'g' || optopt == 'h') {
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      }
      if (isprint(optopt)) {
        fprintf(stderr, "Unknown option -%c.\n", optopt);
      }
      help();
      exit(EXIT_FAILURE);

    default:
      abort();
    }
  }

  if (options->in_path == NULL) {
    fprintf(stderr, "You must provide a path to the file you want to parse\n");
    help();
    exit(EXIT_FAILURE);
  }
}
