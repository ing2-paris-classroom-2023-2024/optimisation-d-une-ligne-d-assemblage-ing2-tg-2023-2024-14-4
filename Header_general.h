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
    int station;
    float tempstotal;
}t_station;

typedef struct actions_duree
{
    int num_action;
    int disponible;           //est ce que l action est deja dans l assemblage ou pas
    float temps_action;
    int precedence;
    int nombre_de_precedence;
    int exclusion;
    int nombre_de_exclusion;
}t_actions;

typedef struct assemblage
{
    t_station tab_station;
    t_actions *tab_actions;
    int nombre_actions;
    int nombre_stations;
}t_assemblage;

void recuperation_de_donnees(t_assemblage *voiture);
#endif //PROJETS1_HEADER_GENERAL_H
