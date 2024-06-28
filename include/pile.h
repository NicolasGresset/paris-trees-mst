#pragma once
#include <stdio.h>

typedef struct pile pile;

pile* pile_create(void);

size_t pop(pile* pile);

int push(pile* pile, size_t element);

int is_empty(pile* pile);

void pile_free(pile* pile);
