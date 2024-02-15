#include <stdio.h>
#include <math.h>
#include "tps_unit_test.h"
#include "../../include/struct.h"
#include "../../include/fonctions.h" 

#define EPSILON 0.01 
TEST_INIT_GLOBAL

double absol(double x){
    if (x>=0) return x;
    return -x;
}

void test_distance(void){

    tree tree1 = { .geoloc = {.x= 48.904054713302315, .y= 2.4116452063563227} };
    tree tree2 = { .geoloc = {.x= 49.904054713302315, .y= 4.4116452063563227} };

    double dist = distanceTrees(&tree1,&tree2);
    tps_assert(absol(dist-182693.93175786689971573650836944580078125) < EPSILON);

}

void test_radians(void){
    double angle = 2;
    tps_assert(radians(angle) == M_PI*angle/180);
}

int main(void){
    TEST(test_radians);
    TEST(test_distance);
    return 0;
}