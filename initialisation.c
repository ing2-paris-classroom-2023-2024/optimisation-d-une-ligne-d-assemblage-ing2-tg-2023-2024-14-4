//
// Created by amaur on 13/11/2023.
//
#include "Header_general.h"
void recuperation_de_donnees(assemblage *voiture) {
    FILE *fichier;
    fichier = fopen("operation.txt", "r");
    if (fichier == NULL)printf("probleme ouverture fichier");
    int i = 0;
    do {
        voiture->tab_actions = (actions *) realloc(voiture->tab_actions, sizeof(actions) * (i + 1));
        i++;
    } while (fscanf(fichier, "%d %f", &voiture->tab_actions[(i - 1)].num_action, &voiture->tab_actions[(i - 1)].temps_action) == 2);
    voiture->tab_actions = (actions *) realloc(voiture->tab_actions, sizeof(actions) * (i - 1));
    voiture->nombre_actions=i-1;
    fclose(fichier);
    fichier= fopen("exclusion.txt", "r");
    if (fichier == NULL)printf("probleme ouverture fichier");
    i = 0;
    do {
        voiture->tab_ex = (exclusions *) realloc(voiture->tab_ex, sizeof(exclusions) * (i + 1));
        i++;
    } while (fscanf(fichier, "%d %d", &voiture->tab_ex[(i - 1)].action1, &voiture->tab_ex[(i - 1)].action2) == 2);
    voiture->tab_ex = (exclusions *) realloc(voiture->tab_ex, sizeof(exclusions ) * (i - 1));
    voiture->nombre_exclusions=i-1;
}