//
// Created by amaur on 13/11/2023.
//

#ifndef PROJETS1_HEADER_GENERAL_H
#define PROJETS1_HEADER_GENERAL_H
#include "stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"

typedef struct actions_duree
{
    int num_action;
    float temps_action;
}actions;

typedef struct exclusions
{
    int action1;
    int action2;
}exclusions;

typedef struct assemblage
{
    actions *tab_actions;
    exclusions *tab_ex;
    int nombre_actions;
    int nombre_exclusions;
}t_assemblage;

void recuperation_de_donnees(t_assemblage *voiture);
#endif //PROJETS1_HEADER_GENERAL_H
