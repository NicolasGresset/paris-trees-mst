#pragma once
#include <stdio.h>
#include "array-list.h"

/**
 * @brief structure donnant la localisation d'un arbre
 */
typedef struct position{
    /// @brief latitude position arbre (en degré)
    double x;
    /// @brief longitude position arbre (en degré)
    double y;
} position;

/**
 * @brief structure informations importantes concernant un arbre
 */
typedef struct tree{
    /// @brief struture correspondant à la position de l'arbre
    position geoloc;
    /// @brief genre de l'arbre
    short genus;
    /// @brief hauteur de l'arbre
    short height;

} tree;

/**
 * @brief gestion des options en argument
 */
typedef struct opt{
    
    int stat;                  //s
    int help;                  //a
    char *in_path;             //i
    char *out_path;            //o
    char *span_tree_path;      //t
    char *location;            //l
    char *limit_value;         //f
    char *genus;               //g
    char *height;              //h
    char *conserve;            //c
    char *recharge;            //r
    

}opt;

/**
 * @brief structure associant une genre à une identifiant
 */
typedef struct corres_genus{
    /// @brief genre de l'arbre (string)
    char genus[30];
    /// @brief identifiant associé
    char id;

 } corres_genus;

/**
 * @brief structure de tableau et taille associée
 */
 typedef struct tab_genus{
    /// @brief tableau de paires genre/id correspondant
    corres_genus genuses[255];
    /// @brief nombre d'éléments dans le tableau
    int size;

 }tab_genus;


/**
 * @brief structure définissant une arête
 * 
 */
 typedef struct edge{
    /// @brief premier arbre connecté
    tree * tree1;
    /// @brief deuxième arbre connecté
    tree * tree2;
} edge;



/**
 * @brief 2ième structure définissant une arête (pour options)
 * 
 */
typedef struct edge2{
    size_t tree1;
    size_t tree2;
} edge2;


/**
 * @brief structure représentant un sommet pour la fonction minimumSpanningTree
 * 
 */
typedef struct vertex{
    /// @brief 1 si le sommet est déjà dans la composante
    short isInComponent;
    /// @brief la distance minimale aux autres sommets enregistrée
    double distMin;
    /// @brief le sommet réalisant cette distance
    size_t vertexMin; 
 } vertex;

/**
 * @brief structure définissant un noeud
 * 
 */
typedef struct node{
    list_t* neighbors;
} node;


 
 
