//
// Created by amaur on 13/11/2023.
//

#ifndef PROJETS1_HEADER_GENERAL_H
#define PROJETS1_HEADER_GENERAL_H
#include "stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"
#include <stdbool.h>




typedef struct {
    int opa;        // opération depart
    int opb;        // opération arrivée
    int niv;        // Niveau herarchique de l'arc
} Arcs;

typedef struct {
    int opa;        // opération depart
    int opb;        // opération arrivée

}exclusions;
typedef struct{
    exclusions *ex;  //tableau des exclusions
    int nombre_ex;      //nombre d exclusion
}tab_exclusions;
// Structure pour stocker un tableau d' Arcs
typedef struct {
    Arcs *arcs;      // tableau des arcs
    int nb_arcs;     // Nombre arcs dans le tableau
} Tableau_arcs;
typedef struct {
    int op;
    int indice;// Numéro opération
    int priorite;            // Priorité de l'opération
    float temps;             // Temps de l'opération
    float temps_avant;       // Temps cumulé des opérations précedentes
    int *antecedents;        // Tableau des opérations précedentes
    int nb_antecedents;      // Nombre des opérations précédentes dans le tableau
    int ws;    // ws affectée
    int *ex;    //tableau d exclusion en lien avec l operation
    int nombre_ex;  //nombre des exclusion lie a l operation
} Operations;

typedef struct {
    Operations *operations;    // tableau des operations
    int nb_op;                 // Nombre d'operation dans le tableau
    int nb_priorite;           // Nombre de priorité dans le tableau
} Tableau_operations;
typedef struct {
    int   ws;               // Numero de la work station
    float temps_ops;        // Temps des opérations affectées
    float temps_restant;    // Temps restant an fonction de temps de cycle
    int nb_ws_op;           // Nombre d'opérations affectées
    int*tab_op;     //stocke les operations
} Ws;  //structure station

// Structure pour stocker un tableau des WS
typedef struct {
    Ws *ws;               // Tableau des work station
    int nb_ws;            // nombre  des work station
    float temps_cycle;    // temps de cycle par work station
} Tableau_ws;  //tableau de station
int indice(int valeurdelaction,Tableau_operations voiture);//cherche l indice de l operation a partir de son numero

bool aDesExclusionsAvecLaStation(Tableau_operations *tab_op, int index, int station);//gere la contrainte precendence


bool toutesLesContraintesDePrecedenceSontSatisfaitesa(Tableau_operations *tab_op, int index);//gere ma contraine exclusion
void creerOptimiserStationsAvecCyclea(Tableau_operations *tab_op, Tableau_ws *tab_ws);//optimise de exclusion et precedence en meme temps
int mainexplusprecedence();//execute l optimisation de exclusion et precedence en meme temps





#endif //PROJETS1_HEADER_GENERAL_H
