/*#include "Precedence.h"



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
//
// Created by leopo on 11/26/2023.
//
#include "Precedence.h"


int main() {
    Tableau_arcs tab_arcs;
    Tableau_operations tab_op;
    Tableau_ws tab_ws;

    // Lire le fichier des precedences
    Lire_Fichier_Arcs(&tab_arcs);
    printf("Lecture du fichier precedences.txt \n");
    printf("il y a %d Arcs dans le fichier :\n", tab_arcs.nb_arcs );


    // Determiner le niveau hierarchique des arcs
    Hierarchie_Arcs(&tab_arcs);

    // Trier le tableau d'arcs par niveau
    Trier_arcs(&tab_arcs);

    printf("Liste des Arcs avec niveau hierarchique : \n");
    for (int i = 0; i < tab_arcs.nb_arcs; i++)  {
        printf  ("%d  %d -> %d : niveau = %d \n", i+1,
                 tab_arcs.arcs[i].opa, tab_arcs.arcs[i].opb , tab_arcs.arcs[i].niv);

    }
    printf("\n");
/*
        printf("Appuyez sur entrer pour continuer...\n");
        getchar(); // Attend la frappe d'une touche
		viderTampon();
        system("cls");
*/


    //Remplir le tableau des opérations
    Remplir_operations(&tab_arcs, &tab_op);

    //Trier le tableau d'opérations
    Trier_operations(&tab_op);
    printf("Nombre de priorité = %d : \n" , tab_op.nb_priorite );
    printf("Liste des operations triee  avec antecedents : \n");
    for (int j = 0; j < tab_op.nb_op; j++) {
        printf("operation : %d, priorite = %d, antecedents = [",
               tab_op.operations[j].op, tab_op.operations[j].priorite);

        for (int k = 0; k < tab_op.operations[j].nb_antecedents; k++) {
            printf("%d", tab_op.operations[j].antecedents[k]);
            if (k < tab_op.operations[j].nb_antecedents - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    printf("\n");
    /*
           printf("Appuyez sur entrer pour continuer...\n");
           getchar(); // Attend la frappe d'une touche
           viderTampon();
          // system("cls");
   */
    // Lire le fichier des temps des opérations
    temps_operations(&tab_op);
    temps_avant(&tab_op);

    printf("Lecture du fichier operation.txt \n");
    printf("Ajout du temps au tableau des operation \n");



    // Affichage du contenu du tableau d'opérations trié avec antécédents
    for (int j = 0; j < tab_op.nb_op; j++) {
        printf("op = %d, priorite = %d, temps = %.2f, temps_avant = %.2f , antecedents = [",
               tab_op.operations[j].op, tab_op.operations[j].priorite, tab_op.operations[j].temps, tab_op.operations[j].temps_avant);

        for (int k = 0; k < tab_op.operations[j].nb_antecedents; k++) {
            printf("%d", tab_op.operations[j].antecedents[k]);
            if (k < tab_op.operations[j].nb_antecedents - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    printf("\n");

    Lire_Fichier_temps_cycle(&tab_ws);

    printf("Lecture du fichier temps_cycle.txt \n");
    printf("temps_cycle = %f \n", tab_ws.temps_cycle);
    printf("\n");

    Creer_ws(&tab_ws, &tab_op);

    printf("Nombre minimum des work stations : %d \n", tab_ws.nb_ws);
    printf("Detail des work stations \n");

    // Affichage du contenu du tableau d'opérations trié avec antécédents
    int cpt=0;
    for (int j = 0; j < tab_ws.nb_ws; j++) {
        printf("ws = %d, nombre d'operations = %d, temps restant = %.2f , operations = [",
               tab_ws.ws[j].ws, tab_ws.ws[j].nb_ws_op, tab_ws.ws[j].temps_restant );
        cpt = tab_ws.ws[j].nb_ws_op;

        for (int k = 0; k < tab_op.nb_op; k++) {
            if (tab_op.operations[k].ws == tab_ws.ws[j].ws) {
                printf("%d", tab_op.operations[k].op);
                cpt--;


                if (cpt >0) {printf(" -> ");}

            }
        }
        printf("]\n");
    } printf("\n");


    Ajuster_temps_cycle (&tab_ws, &tab_op);
    printf("temps cycle uptimum = %.2f \n", tab_ws.temps_cycle);
    printf("\n");

    // Affichage du contenu du tableau d'opérations trié avec antécédents
    printf("Detail des work stations \n");
    cpt=0;
    for (int j = 0; j < tab_ws.nb_ws; j++) {
        printf("ws = %d, nombre d'operations = %d, temps restant = %.2f , operations = [",
               tab_ws.ws[j].ws, tab_ws.ws[j].nb_ws_op, tab_ws.ws[j].temps_restant );
        cpt = tab_ws.ws[j].nb_ws_op;

        for (int k = 0; k < tab_op.nb_op; k++) {
            if (tab_op.operations[k].ws == tab_ws.ws[j].ws) {
                printf("%d", tab_op.operations[k].op);
                cpt--;


                if (cpt >0) {printf(" -> ");}

            }
        }
        printf("]\n");
    } printf("\n");



    // Libération de la mémoire allouée pour les tableaux
    liberer_memoire(&tab_arcs, &tab_op);

    return 0;
} // FIN MAIN