#include <stdio.h>
#include <stdlib.h>
#include "tps_unit_test.h"
#include "../../include/parse.h"

TEST_INIT_GLOBAL

void test_binary(void){

    tps_assert(isBinary("binary") == 10);

}

void test_csv(void){

    tps_assert(isBinary("csv") == 0);

}

void test_none(void){  //mauvais header

    tps_assert(isBinary("none") == 0);

}


int main(void){
    TEST(test_binary);
    TEST(test_csv);
    TEST(test_none);
    return 0;
}