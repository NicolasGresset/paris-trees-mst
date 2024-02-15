#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "../include/parse.h"
#include "../include/struct.h"
#include "../include/manageSIGINT.h"
#include "../include/display.h"



int genusKnown(char * genus, char * id, tab_genus * tab_corres){

    for(int i=0;i<tab_corres->size;i++){
        if(strcmp(genus,tab_corres->genuses[i].genus) == 0){ *id = tab_corres->genuses[i].id; return 1;}
    }
    return 0;
}

void genusId(char * genus, char * id, tab_genus * tab_corres){

    int isInTab = genusKnown(genus,id,tab_corres);

    if(isInTab == 0){
        tab_corres->size+= 1;
        tab_corres->genuses[tab_corres->size-1].id = tab_corres->size - 1;
        *id = tab_corres->size - 1;;
        strcpy(tab_corres->genuses[tab_corres->size-1].genus,genus);
    }
}

void getGenus(char* line, tree * tree, tab_genus * tab_corres){
    int cursor = 0;
    int count = 0;
    int count_semi_colon = 0;

    char * genustree = malloc(30);
    if(genustree == NULL) { exit(15); }

    while (count_semi_colon != 9){
        if (line[cursor] == ';') { count_semi_colon++; }
        cursor++;
    }
    
    while (line[cursor] != ';'){
        genustree[count] = line[cursor];
        count++;
        cursor++;
    }
    genustree[count] = '\0';
    
    char id;
    genusId(genustree,&id,tab_corres);
    tree->genus = id;

    free(genustree);
}

void getHeight(char* line, tree * tree){
    int cursor = 0;
    int count = 0;
    int count_semi_colon = 0;

    char * height_tree = malloc(5);
    if(height_tree == NULL) { exit(15); }

    while (count_semi_colon != 13){
        if (line[cursor] == ';') { count_semi_colon++; }
        cursor++;
    }

    while (line[cursor] != ';' && count < 4){
        height_tree[count] = line[cursor];
        count++;
        cursor++;
    }
    height_tree[count] = '\0';

    tree->height = (short)atoi(height_tree);
    free(height_tree);
}

void getposX(char* line, tree * tree){
    int cursor = 0;
    int count = 0;
    int count_semi_colon = 0;
    char * posx = malloc(25);
    if(posx == NULL) { exit(15); }

    while (count_semi_colon != 16){
        if (line[cursor] == ';') { count_semi_colon++; }
        cursor++;
    }

    while (line[cursor] != ','){
        posx[count] = line[cursor];
        count++;
        cursor++;
    }
    posx[count] = '\0';

    tree->geoloc.x = atof(posx);
    free(posx);
}

void getposY(char* line, tree * tree){
    int cursor = 0;
    int count = 0;
    int count_semi_colon = 0;

    char * posy = malloc(25);
    if(posy == NULL) { exit(15); }

    while (count_semi_colon != 15){
        if (line[cursor] == ';') { count_semi_colon++; }
        cursor++;
    }

    while (line[cursor] != ','){ cursor++; }
    cursor++;

    while (line[cursor] != '\n' && count<18){
        posy[count] = line[cursor];
        count++;
        cursor++;
    }
    posy[count] = '\0';

    tree->geoloc.y = atof(posy);
    free(posy);
}


void parseFile(char* file, tree * forest, size_t numberoflines, tab_genus* tab){

    printf("Parsing csv file\n");

    FILE* in = fopen(file, "r");
    if (in == NULL){
        fprintf(stderr, "Unable to open the file in parseFile %s\n", file);
        exit(16);
    }

    char * line = malloc(500*sizeof(char));
    if(line == NULL) { exit(15); }
    
    size_t line_number = 0;

    if(fgets(line, 500, in) == NULL) { exit(50); } //on écrase la première ligne
    

    while ( line_number < numberoflines - 1){ //pour chaque ligne donc chaque arbre
        if(fgets(line, 500, in) == NULL) { exit(50); }
        
        getGenus(line, &forest[line_number],tab);
        getHeight(line, &forest[line_number]);
        getposX(line, &forest[line_number]);
        getposY(line, &forest[line_number]);
        line_number++;
    }

    free(line);
    if(fclose(in) != 0) {exit(17);}
    printf("Data has been succesfully read\n");
    return;
}

void binaryFile(tree * forest, size_t size, char * save){

    sigset_t masked;
    sigset_t old;
    sigset_t pending;
    struct sigaction ignore;
    
    sigIntitialise(&masked,&old);

    FILE* out = fopen(save, "wb");
    if (out == NULL){
        fprintf(stderr, "Unable to open the file in binaryFile %s\n", save);
        exit(16);
    }

    int nbTrees = size - 1;
    fwrite(&nbTrees, sizeof(nbTrees), 1, out);

    char * header = "NICOLASETINES";
    
    if(fwrite(header, 13, 1, out)!=1){ exit(51); }
    

    for (size_t i = 0; i<size -1; i++){
        if(fwrite(&forest[i], sizeof(forest[i]), 1, out)!=1){ exit(51); }
    }

    sigHandle(&ignore,&pending,&old);

    printf("Conversion to binary format ended succesfully\n");
    if(fclose(out) != 0) {exit(17);}
 
}

void parseFromBinaryFile(char * file, tree * forest, size_t numberoflines){

    printf("Parsing binary file\n");

    FILE* in = fopen(file, "rb");
    if(in == NULL) {
        fprintf(stderr, "Unable to open the file in binaryFile %s\n", file);
        exit(16);
    }

    char lineIgnore[sizeof(int)];
    if(fread(lineIgnore, sizeof(int), 1, in) != 1) { exit(52);}

    char lineIgnore2[13];
    if(fread(lineIgnore2, 13, 1, in) != 1) { exit(52);}
    
    int i=0;
    size_t nbBlocks=0;

    while(nbBlocks != numberoflines){
        
        if(fread(&(forest[i]), sizeof(forest[i]), 1, in) != 1) {exit(52);}
        i++;
        nbBlocks++;
    }

    printf("Data was succesfully read from BinaryFile\n");
}

void SaveStructGenus(opt handlingOptions,tab_genus tab){

    FILE * saveStruct = fopen(handlingOptions.conserve,"w");
    if(saveStruct == NULL){ 
        fprintf(stderr, "Unable to open the file in SaveStructGenus %s\n", handlingOptions.conserve);
        exit(16);
    }

    for(int i=0;i<tab.size;i++){
        fprintf(saveStruct,"%d;",tab.genuses[i].id);
        fprintf(saveStruct,"%s\n",tab.genuses[i].genus);  
    }
    
    if(fclose(saveStruct) != 0){ exit(52); }

}

int isBinary(char * file){

    FILE * in = fopen(file,"r");
    if(in == NULL){ 
        fprintf(stderr, "Unable to open the file in binaryFile %s\n", file);
        exit(16);
    }

    int size;
    if(fread(&size,sizeof(size),1,in) != 1) { exit(52); }

    char line[13];
    if(fread(line,13,1,in) != 1) { exit(52); }
    line[13] = 0;

    if(strcmp(line,"NICOLASETINES") == 0) { return size;}

    if(fclose(in) != 0) { exit(17); }
    return 0;
}

void writeEdges(edge * MST, size_t size,opt handlingOptions){

    if(handlingOptions.span_tree_path == NULL){ return; }

    FILE* out = fopen(handlingOptions.span_tree_path, "w");
    if (out == NULL){
        fprintf(stderr, "Unable to open %s in function writeEdges\n", handlingOptions.span_tree_path);
        exit(16);
    }


    size_t nbTrees = size;
    fwrite(&nbTrees,sizeof(size_t),1,out);

    for (size_t i = 0; i<size; i++){
        fwrite(&MST[i].tree1,sizeof(MST[i].tree1),1,out);
        fwrite(&MST[i].tree2,sizeof(MST[i].tree2),1,out);
    }


    if(fclose(out) != 0) { exit(17); }

}

void handlingFile(opt handlingOptions, tree * tree, int * nbTrees){

    if(handlingOptions.in_path == NULL) {printf("input path needed.\n");exit(1);}
    if(handlingOptions.out_path == NULL) {printf("output path needed.\n");exit(1);}


    tab_genus tab = {.size=0};

    int size=0;
    char line[1000];

    FILE * in = fopen(handlingOptions.in_path,"r");
    if(in == NULL) {
        fprintf(stderr, "Unable to open the file in binaryFile %s\n", handlingOptions.in_path);
        exit(16);
    }

    while(fgets(line,1000,in) != NULL){ size ++; }


    if(isBinary(handlingOptions.in_path) == 0){

        if(handlingOptions.conserve == NULL){ printf("A path to save the gender correspondance table is needed with -c (to get more help : -a)\n"); exit(1);}
        parseFile(handlingOptions.in_path,tree,size,&tab);
        binaryFile(tree,size,handlingOptions.out_path);
        SaveStructGenus(handlingOptions,tab);
        *nbTrees=size -1;

    }else{
        if(handlingOptions.recharge == NULL){ printf("A path to load the gender correspondance table is needed with -r (to get more help : -a)\n"); exit(1);}
        parseFromBinaryFile(handlingOptions.in_path,tree,isBinary(handlingOptions.in_path));
        *nbTrees=isBinary(handlingOptions.in_path);
    }

    
    if(fclose(in) != 0 ){ exit(17); }

}



