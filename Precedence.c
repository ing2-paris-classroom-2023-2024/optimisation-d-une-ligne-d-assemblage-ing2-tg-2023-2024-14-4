#include "Precedence.h"



actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current){
    printf("recherche d action la plus importante en cours ->");
    actions pas_de_voiture;
    pas_de_voiture.disponible=-1;
    int valeur_max=-1;
    for (int i = 0; i < voiture.nombre_actions; i++) {
        if(voiture.tab_actions[i].nombre_de_precedence>valeur_max && voiture.tab_actions[i].disponible==0 && (current.tempstotal+voiture.tab_actions[i].temps_action<voiture.tempsparstation))valeur_max=voiture.tab_actions[i].num_action;
    }
    printf("recherche action la plus importante trouve %d\n",valeur_max);
    if(valeur_max!=-1)return voiture.tab_actions[indice(valeur_max,voiture)];
    else return pas_de_voiture;
}//renvoie l'action non visite

int action_disponible_precedence(t_assemblage *voiture)
{
    printf("action disponible en cours -> ");
    for (int i = 0; i < voiture->nombre_actions; i++) {
        for (int j = 0; j < voiture->nombre_actions; j++) {
            if(voiture->tab_actions[i].disponible!=0) {
                for (int k = 0; k < voiture->tab_actions[j].nombre_de_precedence; k++) {
                    if (voiture->tab_actions[j].precedence[k] == voiture->tab_actions[i].num_action && voiture->tab_actions[i].disponible!=2)
                        voiture->tab_actions[i].disponible = 0;
                }
            }
        }
    }
    printf(" action disponible reussi\n");
    return 1;
}
void ajout_precedence(actions current_action ,t_assemblage* voiture,int i){
    printf("ajout precedence en cours ->");
    voiture->tab_station[i].tempstotal+=current_action.temps_action;
    voiture->tab_station[i].nombre_action+=1;
    voiture->tab_station[i].station=(int*) realloc(voiture->tab_station[i].station,sizeof (int)*voiture->tab_station[i].nombre_action);
    voiture->tab_station[i].station[i]=current_action.num_action;
    voiture->tab_actions[indice(current_action.num_action,*voiture)].disponible=2;
    printf("%d  ",indice(current_action.num_action,*voiture));


    printf(" ajout precedence reussi.\n");
}




void fonction_generale(t_assemblage *voitures){
    int i=0;
    actions mostimportant;
    action_disponible_precedence(voitures);
    while(rechercher_actions_la_plus_importante(*voitures,voitures->tab_station[i]).disponible!=-1) {
        printf("%d\n",i);
        while (voitures->tab_station[i].tempstotal < 5) {
            action_disponible_precedence(voitures);
            mostimportant = rechercher_actions_la_plus_importante(*voitures, voitures->tab_station[i]);
            ajout_precedence(mostimportant, voitures, i);
        }
        voitures->tab_station[i].nombre_action-=1;
        i+=1;
        printf("\n\n\n");
    }
}
/*
 * action.disponible :    -1:plus de station"code erreur"
 *                        0->pas disponible
 *                        1->disponible
 *                        2->pas disponible mais deja dans une station
 */


//tableau de station disponible
//tableau de station utilisée
/* tant que toutes les actions ne sont pas faites :
 *      tant que la station n est pas optimum:
 *          recherche de la station optimum:
 *              fonction_de_recherche(*station_disp,*station_utilisee,t_assemblage)-> a l interieur tab de station temporaire que l on insere de
 *      passer a la station suivante

 * */
