#include "../include/pile.h"
#include "../include/array-list.h"
#include <stdlib.h>

struct pile {
  dynamic_list *list;
};

pile *pile_create(void) {
  pile *pile = malloc(sizeof(*pile));
  if (pile == NULL)
    return NULL;

  if ((pile->list = list_create()) == NULL) {
    free(pile);
    return NULL;
  }
  return pile;
}

size_t pop(pile *pile) { return list_pop(pile->list); }

int push(pile *pile, size_t element) {
  return list_append(pile->list, element);
}

int is_empty(pile *pile) { return list_size(pile->list) == 0; }

void pile_free(pile *pile) {
  list_free(pile->list);
  free(pile);
}
