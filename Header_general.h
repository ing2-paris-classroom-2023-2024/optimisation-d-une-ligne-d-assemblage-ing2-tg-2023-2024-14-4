//
// Created by amaur on 13/11/2023.
//

#ifndef PROJETS1_HEADER_GENERAL_H
#define PROJETS1_HEADER_GENERAL_H
#include "stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"

typedef struct actions_duree // Structure qui correspond au duree des actions
{
    int num_action;
    float temps_action;
}t_actions_duree;

typedef struct exclusions // Structure avec les valeurs des actions des exclusions
{
    int action1;
    int action2;
}t_exclusions;

typedef struct assemblage // Structure Assemblage principal
{
    t_actions_duree *tab_actions;
    t_exclusions *tab_ex;
    int nombre_actions;
    int nombre_exclusions;
}t_assemblage;

void recuperation_de_donnees(t_assemblage *voiture);
#endif //PROJETS1_HEADER_GENERAL_H
