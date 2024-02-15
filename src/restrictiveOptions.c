#include "../include/parse.h"
#include "../include/struct.h"
#include "../include/restrictiveOptions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int genderInSaveFile(opt options, char * id){

    char genus[100];
    strcpy(genus,options.genus);
    
    FILE * saveStruct;
    if(options.conserve != NULL) { saveStruct = fopen(options.conserve,"r");}
    if(options.recharge != NULL) { saveStruct = fopen(options.recharge,"r");}
    
    char line[100];
    char lineGenus[100];
    
    
    while(fgets(line,100,saveStruct) != NULL){ 

        for(int k=0;k<97;k++){ lineGenus[k] = line[k+2]; if(line[k+2] == '\n') lineGenus[k]=0; }
        
        if(strcmp(lineGenus,genus) == 0){ *id = line[0]-48; return 1; } 
    }

    fclose(saveStruct);
    
    return 0;
}

int testGender(opt handlingOptions, tree tree){

    if(handlingOptions.genus == NULL){ return 1;}
    char id;
    int g = genderInSaveFile(handlingOptions,&id);

    if(!g){ fprintf(stderr,"Gender %s not existing",handlingOptions.genus); exit(1);}

    if(tree.genus == id){ return 1;}
    
    return 0;
    

}

int testHeight(opt handlingOptions, tree tree){
    

    if(handlingOptions.height == NULL){ return 1;}

    if(tree.height == atoi(handlingOptions.height)){return 1;}

    return 0;
}

void separationLimit(opt handlingOptions, double * xmin, double * xmax, double * ymin, double * ymax){

    int count=0;
    int n = strlen(handlingOptions.location);
    char line[50];
    int j=0;
    for(int i=0;i<n;i++){

        if(handlingOptions.location[i] == ','){  

            line[j]=0; 
            j=0;
            
            switch (count){
                case 0: 
                    *xmin=atof(line);
                    break;
                case 1:
                    *ymin=atof(line);
                    break;
                case 2:
                    *xmax=atof(line);
                    break;
            }
            count++;
        }

        else{line[j]=handlingOptions.location[i];j++; }

    }
    line[j]=0;
    *ymax=atof(line);
}

int testLimit(opt handlingOptions, tree tree){

    if(handlingOptions.location == NULL){ return 1;}

    double xmin;
    double xmax;
    double ymin;
    double ymax;
    separationLimit(handlingOptions,&xmin,&xmax,&ymin,&ymax);

    //printf("%lf %lf %lf %lf\n",xmin,ymin,xmax,ymax);

    if(tree.geoloc.x >= xmin && tree.geoloc.x <= xmax && tree.geoloc.y >= ymin && tree.geoloc.y <= ymax ){return 1;}

    return 0;
    
}

void handlingRestrictingOptions(opt handlingOptions, tree * trees, tree * treesSelection, int size, int * sizeSelection){

    int j=0;
    int g;
    int h;
    int l;
    for(int i=0;i<size;i++){
        
        g = testGender(handlingOptions, trees[i]);
        h = testHeight(handlingOptions, trees[i]);
        l = testLimit(handlingOptions, trees[i]);

        if(g && h && l){
            treesSelection[j] = trees[i];
            j++;
        }
    }

    *sizeSelection=j;

}
