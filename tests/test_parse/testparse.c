#include <stdio.h>
#include <math.h>
#include "tps_unit_test.h"
#include "../../include/struct.h"
#include "../../include/parse.h" 


TEST_INIT_GLOBAL

void test_getHauteur(void){
    tree tree;
    char * line = "137483;Arbre;Jardin;PARIS 17E ARRDT;;;PROMENADE PEREIRE TERNES-MAILLOT / 210b-218 BOULEVARD PEREIRE;000202002;Lilas des indes;Lagerstroemia;indica;;18;3;Jeune (arbre);NON;48.87986993598043,2.287629708186799";
    getHeight(line, &tree);
    tps_assert( tree.height == 3);
}

void test_getposX(void){
    tree tree;
    char * line = "137483;Arbre;Jardin;PARIS 17E ARRDT;;;PROMENADE PEREIRE TERNES-MAILLOT / 210b-218 BOULEVARD PEREIRE;000202002;Lilas des indes;Lagerstroemia;indica;;18;3;Jeune (arbre);NON;48.87986993598043,2.287629708186799";
    getposX(line, &tree);
    tps_assert( tree.geoloc.x == 48.87986993598043);
}

void test_getposY(void){
    tree tree;
    char * line = "137483;Arbre;Jardin;PARIS 17E ARRDT;;;PROMENADE PEREIRE TERNES-MAILLOT / 210b-218 BOULEVARD PEREIRE;000202002;Lilas des indes;Lagerstroemia;indica;;18;3;Jeune (arbre);NON;48.87986993598043,2.287629708186799";
    getposY(line, &tree);
    tps_assert( tree.geoloc.y == 2.287629708186799);
}


int main(void){

    TEST(test_getHauteur);
    TEST(test_getposX);
    TEST(test_getposY);
    return 0;
}