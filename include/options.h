#pragma once

#include "struct.h"

/**
 * @brief Cette fonction gère les options mises en argument
 * 
 * @param argc nombre d'arguments
 * @param argv liste des différentes chaînes de caractères écrites en arguments
 * @param options pointeur vers une structure stockant chaque option mise en argument
 * 
 */
void options(int argc, char ** argv, opt * options);