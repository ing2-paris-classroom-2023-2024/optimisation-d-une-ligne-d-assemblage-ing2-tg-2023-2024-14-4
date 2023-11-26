/*
#ifndef PROJETS1_PRECEDENCE_H
#define PROJETS1_PRECEDENCE_H
#include "Header_general.h"
int action_disponible_precedence(t_assemblage *voiture);
actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current);
void ajout_precedence(actions current_action ,t_assemblage* voiture,int i);
void fonction_generale(t_assemblage *voitures);
#endif //PROJETS1_PRECEDENCE_H
 */
//
// Created by leopo on 11/26/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

#include <stdio.h>
#include <stdlib.h>

/***************************************************STRUCTURES*********************************************************/
// Structure pour stocker les temps des opérations
typedef struct {
    int numero;             // Numéro opération
    float temps;            // Temps de l'opération
} Temps_op;

// Structure pour stocker les opérations
typedef struct {
    int op;                  // Numéro opération
    int priorite;            // Priorité de l'opération
    float temps;             // Temps de l'opération
    float temps_avant;       // Temps cumulé des opérations précedentes
    int *antecedents;        // Tableau des opérations précedentes
    int nb_antecedents;      // Nombre des opérations précédentes dans le tableau
    int ws;                  // ws affectée
} Operations;


// Structure pour stocker les Arcs
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

// Structure pour stocker un tableau d'Operations
typedef struct {
    Operations *operations;    // tableau des operations
    int nb_op;                 // Nombre d'operation dans le tableau
    int nb_priorite;           // Nombre de priorité dans le tableau
} Tableau_operations;

// Structure pour stocker des WS
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


/***************************************************FONCTIONS************************************************************************/
void Lire_Fichier_Arcs(Tableau_arcs *tab_arcs);
void Hierarchie_Arcs(Tableau_arcs *tab_arcs);
int compare_arcs(const void *a, const void *b);
void Trier_arcs(Tableau_arcs *tab_arcs);
void Remplir_operations(Tableau_arcs *tab_arcs, Tableau_operations *tab_op);
int compare_operations(const void *a, const void *b);
void Trier_operations(Tableau_operations *tab_op);
void liberer_memoire(Tableau_arcs *tab_arcs, Tableau_operations *tab_op);
void temps_operations(Tableau_operations *tab_op);
void viderTampon();
void temps_avant(Tableau_operations *tab_op);
void Lire_Fichier_temps_cycle(Tableau_ws *tab_ws);
void Creer_ws(Tableau_ws *tab_ws, Tableau_operations *tab_op);
void Ajuster_temps_cycle(Tableau_ws *tab_ws, Tableau_operations *tab_op);





#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

