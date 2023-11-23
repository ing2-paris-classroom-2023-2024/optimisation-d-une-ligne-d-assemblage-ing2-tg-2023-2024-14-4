//
// Created by amaur on 13/11/2023.
//

#ifndef PROJETS1_HEADER_GENERAL_H
#define PROJETS1_HEADER_GENERAL_H
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"

typedef struct station
{
    int* station;          // Liste de toutes les actions présentes dans la station
    float tempstotal;      // Temps total de chaque station (Addition de toutes les actions à l'intérieur de la station)
}t_station;

typedef struct actions
{
    int num_action;           // Numéro de l'action
    int disponible;           //est ce que l action est deja dans l assemblage ou pas
    float temps_action;
    int *precedence;
    int nombre_de_precedence;
    int *exclusion;           // Liste de toutes les exclusions
    int nombre_de_exclusion;  // Nombre d'exclusions pour l'action
}t_actions;

typedef struct assemblage
{
    t_station *tab_station;           // Tableau de toutes les stations
    t_actions *tab_actions;     // Tableau de toutes les actions
    int nombre_actions;
    int nombre_stations;
}t_assemblage;

void recuperation_de_donnees(t_assemblage *voiture);
int indice(int valeurdelaction,t_assemblage voiture);
#endif //PROJETS1_HEADER_GENERAL_H
