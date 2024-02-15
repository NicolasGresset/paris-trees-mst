#include "../include/pile.h"
#include <stdio.h>
#include "../include/array-list.h"


pile_t* pile_create(void){
    return list_create();
}

void* pop(pile_t* pile){
    return list_take(pile, list_size(pile) - 1);
}


int push(pile_t* pile, void* elm){
    return list_append(pile, elm);
}

int is_empty(pile_t* pile){
    if (list_size(pile) == 0) return 1;
    return 0;
}

void pile_free(pile_t* pile){
    list_free2(pile);
}

size_t pile_size(pile_t* pile){
    return list_size(pile);
}