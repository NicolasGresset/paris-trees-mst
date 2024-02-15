#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/struct.h"

void help(void){
    printf("\n**********************************************************************************************************\n");
    printf("i option (followed by a path) : path of the file you want to parse [csv or binary]\n");
    printf("c option (followed by a path) : path of the file where you want to save your gender correspondance table (if use of csv file)\n");
    printf("r option (followed by a path) : path of the file from where you want to load your gender correspondance table (if use of binary file)\n");
    printf("o option (followed by a path) : path of the file where you save the binary version of your input [binary]\n");
    printf("t option (followed by a path) : path of the file saving the minimum panning tree informations\n");
    printf("l option (followed by a positive int) : maximum distance allowed betwween your trees [meters]\n");
    printf("s option (no arguments) : to get statistics on the tree\n");
    printf("f option (followed by 4 positives int) : x minimum X1, y minimum Y1,x maximum X2, y maximum Y2 [°]\n");
    printf("g option (followed by a string) : to get a mimimum spanning tree only considering this genus\n");
    printf("h option (followed by an positive int) :  to get a mimimum spanning tree only considering this height [meters]\n");
    printf("**********************************************************************************************************\n");
}

void initOptions(opt * options){
    options->in_path = NULL;  //ok
    options->out_path = NULL;  //ok
    options->span_tree_path = NULL;   //ok
    options->limit_value = NULL;  
    options->stat = 0;
    options->location = NULL;    //ok
    options->genus = NULL;  //ok
    options->height = NULL;  //ok
    options->conserve = NULL;  //ok
    options->recharge = NULL;   //ok
    options->help = 0;   //ok

}

void options(int argc, char ** argv, opt * options){

    initOptions(options);
    int c;
    while ((c = getopt (argc, argv, "i:o:t:l:sf:g:h:c:r:a")) != -1)
        switch (c) {
            case 'i':
                options->in_path = optarg;
                break;
            case 'o':
                options->out_path = optarg;
                break;
            case 't':
                options->span_tree_path = optarg;
                break;
            case 'f':
                options->limit_value = optarg;
                if(atoi(options->limit_value) <= 0) {fprintf(stderr,"The limit %d must be a positive value",atoi(options->limit_value)); help(); exit(1);}
                break;
            case 's':
                options->stat= 1;
                break;
            case 'l':
                options->location = optarg;
                break;
            case 'g':
                options->genus = optarg;
                break;
            case 'h':
                options->height = optarg;
                if(atoi(options->height) <= 0) {fprintf(stderr,"Th height %d must be a positive value",atoi(options->height));  help(); exit(1);}
                break;
            case 'c':
                options->conserve = optarg;
                break;
            case 'r':
                options->recharge = optarg;
                break;
            case 'a':
                options->help = 1;
                help();
                break;

            case '?':

                if (optopt == 'i' || optopt == 'o'|| optopt == 't' || optopt == 'l' || optopt == 'f' || optopt == 'g' || optopt == 'h'){
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                    help(); 
                    exit(2);

                }else if (isprint (optopt)){
                    fprintf (stderr, "Unknown option -%c.\n", optopt);
                    exit(3);

                }else{
                    fprintf (stderr,"Unknown option character `\\x%x'.\n", optopt);
                    exit(3);
                }
                

            default:
                abort ();
        }


}

