#pragma once
#include <stdio.h>

typedef struct list_t pile_t;

pile_t* pile_create(void);

void* pop(pile_t* pile);

int push(pile_t* pile, void* elm);

int is_empty(pile_t* pile);

void pile_free(pile_t* pile);

size_t pile_size(pile_t* pile);