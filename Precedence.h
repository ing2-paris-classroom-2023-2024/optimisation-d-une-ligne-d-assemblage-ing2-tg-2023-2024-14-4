
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

#include <stdio.h>
#include <stdlib.h>
#include "Header_general.h"
#include "Exclusions.h"
/***************************************************STRUCTURES*********************************************************/
// Structure pour stocker les temps des opérations
typedef struct {
    int numero;             // Numéro opération
    float temps;            // Temps de l'opération
} Temps_op;

/***************************************************FONCTIONS************************************************************************/
void Lire_Fichier_Arcs(Tableau_arcs *tab_arcs);
int compare_arcs(const void *a, const void *b);//utiliser pour le qsort de trierArc
void Trier_arcs(Tableau_arcs *tab_arcs);
void Remplir_operations(Tableau_arcs *tab_arcs, Tableau_operations *tab_op);//va remplir les operations avec la precedence et les priorite
int compare_operations(const void *a, const void *b);//utiliser pour le qsort de trierOperation
void Trier_operations(Tableau_operations *tab_op);
void liberer_memoire(Tableau_arcs *tab_arcs, Tableau_operations *tab_op);//libere la memoire
void temps_operations(Tableau_operations *tab_op);//recupere les informations de
void Lire_Fichier_temps_cycle(Tableau_ws *tab_ws);//lit le temps de cycle
int mainprecedence();//appel les differentes fonctions

int toutesLesContraintesDePrecedenceSontSatisfaites(Tableau_operations *tab_op, int index);//optimise le systeme


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

