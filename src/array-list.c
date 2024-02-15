#include "../include/array-list.h"
#include <stdio.h>
#include <stdlib.h>

struct  list_t{
    void** element;
    size_t allocated;
    size_t size;
};

list_t* list_create(void){
    list_t* it = malloc(sizeof(*it));
    if (it == NULL) return NULL;

    it->element = malloc(10*sizeof(it->element[0]));
    if (it->element == NULL){
        free(it);
        return NULL;
    }

    it->allocated = 10;
    it->size = 0;
    return it;
}


int list_append(list_t* it, void* element_to_append){
    if( it->size < it->allocated){
        it->element[it->size] = element_to_append;
        it->size ++;
        return 1; 
    }

    void** tmp = realloc(it->element,(it->allocated+15)*sizeof(it->element[0]));
    if (tmp == NULL){
        return 0;
    }

    it->element = tmp;
    it->allocated += 15; 
    it->element[it->size] = element_to_append;
    it->size ++;
    return 1;
}

void* list_get(list_t* it, int pos){
    return it->element[pos];
}

void list_set(list_t* it, int pos, void* element){
    it->element[pos] = element;
}

void list_set2(list_t* it, int pos, void* element){
    free(list_get(it, pos));
    it->element[pos] = element;
}

size_t list_size(list_t* it){
    return it->size;
}

int list_insert(list_t* it, size_t pos, void* elmt){

    if (list_append(it, elmt) == 0) return 0;

    for (size_t i = it->size - 1; i>pos; i--){
        list_set(it, i, list_get(it, i-1));
    }
    list_set(it, pos, elmt);
    return 1;
}

int list_prepend(list_t* it, void* elmt){
    return list_insert(it, 0, elmt);
}

void* list_take(list_t* it, int pos){
    void* elmt = list_get(it, pos);

    for (size_t i = pos; i < it->size-1; i++){
        it->element[i] = it->element[i+1];
    }
    it->size--;
    return elmt;
}


void list_free(list_t* it){
    for(size_t i = 0; i < list_size(it); i++){
        free(list_get(it, i));
    }

    free(it->element);
    free(it); //modif concernant le projet programmation 
}

size_t* create_size_t(size_t i){
  size_t* p = malloc(sizeof(size_t));
  *p = i;
  return p;
}

void list_free2(list_t* it){
    free(it->element); 
    free(it);
}
