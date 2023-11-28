/*
#ifndef PROJETS1_PRECEDENCE_H
#define PROJETS1_PRECEDENCE_H
#include "Header_general.h"
int action_disponible_precedence(t_assemblage *voiture);
actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current);
void ajout_precedence(actions current_action ,t_assemblage* voiture,int i);
void fonction_generale(t_assemblage *voitures);
void afficher_action_disponible(t_assemblage voiture);
#endif //PROJETS1_PRECEDENCE_H
 */
//
// Created by leopo on 11/26/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

#include <stdio.h>
#include <stdlib.h>
#include "Header_general.h"
/***************************************************STRUCTURES*********************************************************/
// Structure pour stocker les temps des opérations
typedef struct {
    int numero;             // Numéro opération
    float temps;            // Temps de l'opération
} Temps_op;

// Structure pour stocker les opérations
;


// Structure pour stocker les Arcs


// Structure pour stocker un tableau d'Operations


// Structure pour stocker des WS



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
int mainprecedence();




#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

