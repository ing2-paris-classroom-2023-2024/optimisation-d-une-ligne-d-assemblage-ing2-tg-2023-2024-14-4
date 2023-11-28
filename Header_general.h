//
// Created by amaur on 13/11/2023.
//

#ifndef PROJETS1_HEADER_GENERAL_H
#define PROJETS1_HEADER_GENERAL_H
#include "stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"

//



typedef struct {
    int opa;        // opération depart
    int opb;        // opération arrivée
    int niv;        // Niveau herarchique de l'arc
} Arcs;

// Structure pour stocker un tableau d' Arcs
typedef struct {
    Arcs *arcs;      // tableau des arcs
    int nb_arcs;     // Nombre arcs dans le tableau
} Tableau_arcs;
typedef struct {
    int op;                  // Numéro opération
    int priorite;            // Priorité de l'opération
    float temps;             // Temps de l'opération
    float temps_avant;       // Temps cumulé des opérations précedentes
    int *antecedents;        // Tableau des opérations précedentes
    int nb_antecedents;      // Nombre des opérations précédentes dans le tableau
    int ws;                  // ws affectée
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
} Ws;

// Structure pour stocker un tableau des WS
typedef struct {
    Ws *ws;               // Tableau des work station
    int nb_ws;            // nombre  des work station
    float temps_cycle;    // temps de cycle par work station
} Tableau_ws;


typedef struct station{
    int *station;
    float tempstotal;
    int nombre_action;
}t_station;

typedef struct actions_duree
{
    int num_action;
    int disponible;               //est ce que l action est deja dans l assemblage ou pas
    float temps_action;
    int *precedence;
    int nombre_de_precedence;
    int *exclusion;
    int nombre_de_exclusion;
}actions;

typedef struct assemblage
{
    t_station *tab_station;
    actions *tab_actions;
    int nombre_actions;
    int nombre_stations;
    float tempsparStation;
}t_assemblage;

int indice(int valeurdelastation,t_assemblage voiture);
void recuperation_de_donnees(t_assemblage *voiture);

#endif //PROJETS1_HEADER_GENERAL_H
