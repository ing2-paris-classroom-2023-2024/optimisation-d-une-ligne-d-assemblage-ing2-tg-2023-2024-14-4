#include "Precedence.h"



int rechercher_actions_la_plus_importante(t_assemblage voiture){
  //renvoie le sommet(sa valeur pas son indice)
    int valeur_max=-1;
    for (int i = 0; i < voiture.nombre_actions; i++) {
        if(voiture.tab_actions[i].nombre_de_precedence>valeur_max && voiture.tab_actions[i].disponible==0)valeur_max=voiture.tab_actions[i].num_action;
    }
    return valeur_max;
}//renvoie l'action non visite

void station_disponible_precedence(t_assemblage *voiture)
{
    for (int i = 0; i < voiture->nombre_actions; i++) {
        for (int j = 0; j < voiture->nombre_actions; j++) {
            if(voiture->tab_actions[i].disponible!=0) {
                for (int k = 0; k < voiture->tab_actions[j].nombre_de_precedence; k++) {
                    if (voiture->tab_actions[j].precedence[k] == voiture->tab_actions[i].num_action)
                        voiture->tab_actions[i].disponible = 0;
                }
            }
        }
    }
}



/*void recherche_station_disponible(t_assemblage *voiture){



}*//*
void fonction_generale(t_assemblage *voitures){
    int i=0;
    station_disponible_precedence(voitures);
    while(voitures->tab_station[i]){



    }




            )

}
*/
//tableau de station disponible
//tableau de station utilisée
/* tant que toutes les actions ne sont pas faites :
 *      tant que la station n est pas optimum:
 *          recherche de la station optimum:
 *              fonction_de_recherche(*station_disp,*station_utilisee,t_assemblage)-> a l interieur tab de station temporaire que l on insere de
 *      passer a la station suivante

 * */
