#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tps_unit_test.h"
#include "../../include/parse.h"
#include "../../include/struct.h"

TEST_INIT_GLOBAL

void test_corres(void){

    FILE * file = fopen("inpath","r");
    if(file == NULL) { fprintf(stderr,"Unable to open the inpath file"); exit(1);}

    FILE * fileStruct = fopen("save","r");
    if(fileStruct == NULL) { fprintf(stderr,"Unable to open the in file"); exit(1);}

    tab_genus treeStruct = { .size=0 };
    tree forest[10];

    parseFile("inpath", forest, 11, &treeStruct);
    
    printf("%s\n",treeStruct.genuses[4].genus);

    char id;
    genusKnown("Liquidambar",&id,&treeStruct);
    tps_assert(id==4);
    
    genusKnown("Acer",&id,&treeStruct);
    tps_assert(id==5);

 
}



int main(void){
    TEST(test_corres);
    return 0;
}