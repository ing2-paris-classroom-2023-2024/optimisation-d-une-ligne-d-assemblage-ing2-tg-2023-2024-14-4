
#ifndef PROJETS1_EXCLUSIONS_H
#define PROJETS1_EXCLUSIONS_H

#include "Header_general.h"
#include "Precedence.h"

void recuperation_donnees(tab_exclusions *a,Tableau_operations *b);
int mainex2();
void temps_operations_ex(Tableau_operations *tab_op);
int toutelesactions(Tableau_operations a);
void Trier_operations(Tableau_operations *tab_op);
int compare_operations(const void *a, const void *b);
void Trier_arcs(Tableau_arcs *tab_arcs);
int compare_arcs(const void *a, const void *b);
int compare_operations(const void *a, const void *b);
void temps_avant(Tableau_operations *tab_op);
void Hierarchie_Arcs(Tableau_arcs *tab_arcs);
void Trier_operations(Tableau_operations *tab_op);

//printf("Test"\n);
//printf("Test Final\n");


#endif //PROJETS1_EXCLUSIONS_H
