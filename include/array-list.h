#include <stdio.h>

typedef struct list dynamic_list;

/**
 * @brief Crée une liste vide
 *
 * @return list_t* ou NULL en cas de problème
 */
dynamic_list *list_create(void);

/**
 * @brief Ajoute un élément à la fin de la liste
 *
 * @return 0 en cas de problème, 1 sinon
 */
int list_append(dynamic_list *list, size_t elem);

/**
 * @brief retourne le (idx+1)ème élément
 * comportement indéfini en cas de dépassemnt
 *
 * @return void*
 */
size_t list_get(dynamic_list *list, int index);

size_t list_pop(dynamic_list *list);

/**
 * @brief remplace l'élément à la position donnée par l'élément donné
 *
 */
void list_set(dynamic_list *, int index, size_t new_value);

size_t list_size(dynamic_list *list);

void list_free(dynamic_list *list);
