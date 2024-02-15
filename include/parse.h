#pragma once
#include "struct.h"
#include <stdio.h>


/**
 * @brief Cette fonction vérifie si le genre donné en argument est connu ou non
 * 
 * @param genus genre de l'arbre considéré (string)
 * @param id pointeur vers l'identifiant id (char), on lui affecte l'id correspondant au genre obtenu dans tab_corres, on ne fait rien si genre pas dans tab_corres
 * @param tab_corres tableau de paires genre/id correspondant des genres déjà connus
 * @return renvoie 1 si le genre est connu et affecte l'id correspond, renvoie 0 sinon
 */
int genusKnown(char * genus, char * id, tab_genus * tab_corres);

/**
 * @brief Cette fonction associe à genre un identifiant stocké dans *id 
 * 
 * @param genus genre (string)
 * @param id pointeur vers id (short)
 * @param tab_corres tableau de paires genre/id correspondant des genres déjà connus
 */
void genusId(char * genus, char * id, tab_genus * tab_corres);

/**
 * @brief Récupère le champ Genre d'une ligne et stocke le résultat dans le champ genre (un char) de l'arbre pointé par tree et l'ajoute à tab_corres si non connu
 * 
 * @param line ligne du fichier csv
 * @param tree pointeur vers une structure qui stocke les informations d'un arbre
 * @param tab_corres tableau des correspondances entre genre et identifiant attribué
 */
void getGenus(char* line, tree * tree, tab_genus * tab_corres);


/**
 * @brief Récupère le champ Hauteur d'une ligne et stocke le résultat dans le champ hauteur de l'arbre pointé par tree
 * 
 * @param line ligne du fichier csv
 * @param tree pointeur vers une structure qui stocke les informations d'un arbre
 * 
 */
void getHeight(char* line, tree * tree);

/**
 * @brief Récupère le champ PositionX d'une ligne et stocke le résultat dans le champ geoloc.x de l'arbre pointé par tree
 * 
 * @param line ligne du fichier csv
 * @param tree pointeur vers une structure qui stocke les informations d'un arbre
 * 
 */
void getposX(char* line, tree * tree);

/**
 * @brief Récupère le champ PositionY d'une ligne et stocke le résultat dans le champ geoloc.y de l'arbre pointé par tree
 * 
 * @param line ligne du fichier csv
 * @param tree pointeur vers une structure qui stocke les informations d'un arbre
 * 
 */
void getposY(char* line, tree * tree);


/**
 * @brief Cette fonction trie des données utiles d'un fichier csv
 * 
 * @param file fichier que l'on va trier
 * @param forest pointure vers la structure dans lequel on va stocker les données utiles
 * @param numberoflines nombre total de lignes du fichier
 * 
 */
void parseFile(char* file, tree * forest, size_t numberoflines, tab_genus* tab);

/**
 * @brief Cette fonction met les informations d'un arbre dans un fichier binaire
 * 
 * @param structure liste de structures de tous les arbres pris en compte
 * @param size taille totale du tableau
 * @param save fichier dans lequel on sauvegarde les données de la structure 
 * 
 */
void binaryFile(tree * forest, size_t size, char * save);

/**
 * @brief Cette fonction trie des données utiles d'un fichier binaire
 * 
 * @param file fichier que l'on va trier
 * @param forest pointure vers la structure dans lequel on va stocker les données utiles
 * @param numberoflines nombre total de lignes du fichier
 * 
 */
void parseFromBinaryFile(char * file, tree * forest, size_t numberoflines);


/**
 * @brief Cette fonction permet la sauvegarde de l'association d'un genre (char *) à un identifiant (char)
 * 
 * @param tab tableau de correspondance
 */
void SaveStructGenus(opt handlingOptions,tab_genus tab);

/**
 * @brief Cette fonction vérifie si le fichier est un fichier binaire ou non
 * 
 * @param file chemin vers le fichier binaire ou non
 * @return renvoie 0 si le fichier n'est pas binaire, le nombre d'arbres sinon
 */
int isBinary(char * file);

/**
 * @brief Cette fonction gère l'ouverture des fichiers, le parsage, la sauvegarde de la structure etc
 * 
 * @param gestionOptions options entrées en ligne de commande
 * @param tree tableau où sont stockées les informations sur les arbres après le parsage
 */
void handlingFile(opt handlingOptions, tree * tree, int * nbTrees);


/**
 * @brief Cette fonction écrit dans un fichier l'arbre recouvrant minimal
 * 
 * @param file Le fichier dans lequel on écrit
 * @param arbre L'arbre recouvrant minimal
 * @param size Sa taille
 */
void writeEdges(edge * MST, size_t size, opt handlingOptions);