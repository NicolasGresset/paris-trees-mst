#include <stdio.h>

typedef struct list_t list_t ;



/**
 * @brief Crée une liste vide
 * 
 * @return list_t* ou NULL en cas de problème
 */
list_t* list_create(void);


/**
 * @brief Ajoute un élément à la fin de la liste
 * 
 * @return 0 en cas de problème, 1 sinon
 */
int list_append(list_t*, void*);

/**
 * @brief Ajoute un élément en début de liste
 * 
 * @return 0 en cas de problème, 1 sinon
 */
int list_prepend(list_t*, void*);


/**
 * @brief retourne le (idx+1)ème élément
 * comportement indéfini en cas de dépassemnt
 * 
 * @return void* 
 */
void* list_get(list_t*, int);


/**
 * @brief remplace l'élément à la position donnée par l'élément donné
 * 
 */
void list_set(list_t*, int, void*);

/**
 * @brief remplace l'élément à la position donnée par l'élément donné et free l'élément remplacé
 * 
 */
void list_set2(list_t* it, int pos, void* element);

/**
 * @brief revoie la taille de la liste
 * 
 * @return size_t 
 */
size_t list_size(list_t*);

/**
 * @brief insère un élément à la position idx
 * 
 * @return 0 en cas de problème, 1 sinon 
 */
int list_insert(list_t*, size_t, void*);

/**
 * @brief retourne l'élément à la position idc, puis enlève cet élément de la liste
 * 
 * @return void* 
 */
void* list_take(list_t*, int);

/**
 * @brief libère la liste et tous ses éléments
 * 
 */
void list_free(list_t*);


size_t* create_size_t(size_t i);

void list_free2(list_t* it);