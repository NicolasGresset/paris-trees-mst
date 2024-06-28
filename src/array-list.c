#include "../include/array-list.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_LIST_SIZE 8
#define GROWTH_FACTOR 2

struct list {
  size_t *elements;
  size_t allocated;
  size_t size;
};

dynamic_list *list_create(void) {
  dynamic_list *list = malloc(sizeof(*list));
  if (list == NULL)
    return NULL;

  list->elements = malloc(INITIAL_LIST_SIZE * sizeof(list->elements[0]));
  if (list->elements == NULL) {
    free(list);
    return NULL;
  }

  list->allocated = INITIAL_LIST_SIZE;
  list->size = 0;
  return list;
}

int list_append(dynamic_list *list, size_t element) {
  if (list->size < list->allocated) {
    list->elements[list->size] = element;
    list->size++;
    return 1;
  }

  size_t *tmp = realloc(list->elements, (list->allocated * GROWTH_FACTOR *
                                         sizeof(list->elements[0])));
  if (tmp == NULL) {
    return 0;
  }
  list->elements = tmp;
  list->allocated *= GROWTH_FACTOR;
  list->elements[list->size] = element;
  list->size++;
  return 1;
}

size_t list_get(dynamic_list *list, int index) { return list->elements[index]; }

void list_set(dynamic_list *list, int index, size_t element) {
  list->elements[index] = element;
}

size_t list_size(dynamic_list *it) { return it->size; }

size_t list_pop(dynamic_list *list) {
  list->size--;
  return list->elements[list->size];
}

void list_free(dynamic_list *list) {
  free(list->elements);
  free(list);
}
