//
// Created by amaur on 13/11/2023.
//
#include "Header_general.h"

int indice(int valeurdelaction,t_assemblage voiture){


    for (int i = 0; i < voiture.nombre_actions; i++) {
        //printf("   %d",voiture.tab_actions[i].num_action);
        if(voiture.tab_actions[i].num_action==valeurdelaction)return i;
    }
    printf("]probleme lors de la fonction indice\n");
    EXIT_FAILURE;
    return 0;
}
void Lire_Fichier_Arcs(Tableau_arcs *tab_arcs) {
    FILE *fichier;
    int opa, opb;

    //ouverture du fichier
    fichier = fopen("..\\precedences.txt", "r");
    if (fichier == NULL) {perror("Erreur lors de l'ouverture du fichier precedences.txt"); exit(EXIT_FAILURE);}

    //Initialisation du tableau arcs
    tab_arcs->arcs = NULL;
    tab_arcs->nb_arcs = 0;

    // Lecture du fichier pour alimenter les  Arcs (opa, opb et niv à 0)
    while (fscanf(fichier, "%d %d", &opa, &opb) == 2)
    {
        // Ajustement dynamique de la taille du tableau arcs
        tab_arcs->arcs = (Arcs *)realloc(tab_arcs->arcs, (tab_arcs->nb_arcs + 1) * sizeof(Arcs));
        if (tab_arcs->arcs == NULL) { perror("Erreur lors de la réallocation de mémoire tableau arcs"); exit(EXIT_FAILURE);}

        // Ajout des Arcs au tableau
        tab_arcs->arcs[tab_arcs->nb_arcs].opa = opa;
        tab_arcs->arcs[tab_arcs->nb_arcs].opb = opb;
        tab_arcs->arcs[tab_arcs->nb_arcs].niv = 0;
        tab_arcs->nb_arcs++;

    } //Fin boucle while Lecture du fichier pour alimenter les  Arcs (opa, opb et niv à 0)
    fclose(fichier);
}
void recuperation_de_donnees(t_assemblage *voiture) {
    FILE *fichier;
    fichier = fopen("..\\operation.txt", "r");
    if (fichier == NULL)printf("probleme ouverture fichier operation");
    int i = 0;
    voiture->tab_actions=NULL;
    voiture->tempsparstation=5;
    do {
        voiture->tab_actions = (actions *) realloc(voiture->tab_actions, sizeof(actions) * (i + 1));
        i++;
    } while (fscanf(fichier, "%d %f", &voiture->tab_actions[(i - 1)].num_action,&voiture->tab_actions[(i - 1)].temps_action) == 2);

    voiture->tab_actions = (actions *) realloc(voiture->tab_actions, sizeof(actions) * (i - 1));
    voiture->nombre_actions = i - 1;
    fclose(fichier);
    for (int j = 0; j < voiture->nombre_actions; j++) {
        voiture->tab_actions[j].nombre_de_exclusion=0;
        voiture->tab_actions[j].nombre_de_precedence=0;
        voiture->tab_actions[j].precedence=NULL;
        voiture->tab_actions[j].exclusion=NULL;
        voiture->tab_actions[j].disponible=1;
    }
    fichier = fopen("..\\exclusions.txt", "r");
    if (fichier == NULL)printf("probleme ouverture fichier exclusions");
    int action_temp;
    i = 0;
    do {
        fscanf(fichier,"%d ",&action_temp);
        voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_exclusion+=1;
        voiture->tab_actions[indice(action_temp,*voiture)].exclusion=(int*) realloc(voiture->tab_actions[indice(action_temp,*voiture)].exclusion,sizeof (int)*voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_exclusion);
        i++;
    } while (fscanf(fichier, "%d", &voiture->tab_actions[indice(action_temp,*voiture)].exclusion[((voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_exclusion)-1)]) == 1);
    voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_exclusion-=1;
    fclose(fichier);


    fichier = fopen("..\\precedence.txt", "r");
    if (fichier == NULL)printf("probleme d'ouverture fichier precedence");
    i = 0;
    do {
        fscanf(fichier,"%d ",&action_temp);
        voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_precedence +=1;
        voiture->tab_actions[indice(action_temp,*voiture)].precedence= (int*) realloc(voiture->tab_actions[indice(action_temp,*voiture)].precedence, sizeof(int) * voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_precedence);
        i++;
    } while (fscanf(fichier, "%d", &voiture->tab_actions[indice(action_temp,*voiture)].precedence[((voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_precedence)-1)])==1);
    voiture->tab_actions[indice(action_temp,*voiture)].nombre_de_precedence-=1;
    fclose(fichier);
    voiture->tab_station=NULL;
    voiture->tab_station=(t_station*) malloc(sizeof (t_station)*1);
    voiture->tab_station[0].station=NULL;
    voiture->tab_station[0].station=(int*) malloc(sizeof (int)*1);
    voiture->nombre_stations=1;
}
 // tes