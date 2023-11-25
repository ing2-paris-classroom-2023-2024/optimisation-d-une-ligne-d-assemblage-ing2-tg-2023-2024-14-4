
#ifndef PROJETS1_PRECEDENCE_H
#define PROJETS1_PRECEDENCE_H
#include "Header_general.h"
int action_disponible_precedence(t_assemblage *voiture);
actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current);
ajout_precedence(actions current_action ,t_assemblage* voiture,int i);
void fonction_generale(t_assemblage *voitures);
#endif //PROJETS1_PRECEDENCE_H
