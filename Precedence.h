/*
#ifndef PROJETS1_PRECEDENCE_H
#define PROJETS1_PRECEDENCE_H
#include "Header_general.h"
int action_disponible_precedence(t_assemblage *voiture);
actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current);
void ajout_precedence(actions current_action ,t_assemblage* voiture,int i);
void fonction_generale(t_assemblage *voitures);
#endif //PROJETS1_PRECEDENCE_H
 */
//
// Created by leopo on 11/26/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

#include <stdio.h>
#include <stdlib.h>

/***************************************************STRUCTURES*********************************************************/
// Structure pour stocker les temps des opérations
typedef struct {
    int numero;             // Numéro opération
    float temps;            // Temps de l'opération
} Temps_op;

// Structure pour stocker les opérations
typedef struct {
    int op;                  // Numéro opération
    int priorite;            // Priorité de l'opération
    float temps;             // Temps de l'opération
    float temps_avant;       // Temps cumulé des opérations précedentes
    int *antecedents;        // Tableau des opérations précedentes
    int nb_antecedents;      // Nombre des opérations précédentes dans le tableau
    int ws;                  // ws affectée
} Operations;


// Structure pour stocker les Arcs
typedef struct {
    int opa;        // opération depart
    int opb;        // opération arrivée
    int niv;        // Niveau herarchique de l'arc
} Arcs;

// Structure pour stocker un tableau d' Arcs
typedef struct {
    Arcs *arcs;      // tableau des arcs
    int nb_arcs;     // Nombre arcs dans le tableau
} Tableau_arcs;

// Structure pour stocker un tableau d'Operations
typedef struct {
    Operations *operations;    // tableau des operations
    int nb_op;                 // Nombre d'operation dans le tableau
    int nb_priorite;           // Nombre de priorité dans le tableau
} Tableau_operations;

// Structure pour stocker des WS
typedef struct {
    int   ws;               // Numero de la work station
    float temps_ops;        // Temps des opérations affectées
    float temps_restant;    // Temps restant an fonction de temps de cycle
    int nb_ws_op;           // Nombre d'opérations affectées
} Ws;

// Structure pour stocker un tableau des WS
typedef struct {
    Ws *ws;               // Tableau des work station
    int nb_ws;            // nombre  des work station
    float temps_cycle;    // temps de cycle par work station
} Tableau_ws;


/***************************************************FONCTIONS************************************************************************/
// Fonction pour remplir un tableau de Arcs avec les données du fichier precedences.txt
void Lire_Fichier_Arcs(Tableau_arcs *tab_arcs) {
    FILE *fichier;
    int opa, opb;

    //ouverture du fichier
    fichier = fopen("precedences.txt", "r");
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
// FIN Fonction Lire_Fichier_Arcs

// Fonction pour déterminer le niveau hiérarchique des arcs (niv)
void Hierarchie_Arcs(Tableau_arcs *tab_arcs) {
    int cpt=0;
    int i = -1;

    do { i++;   // Boucle index i

        for (int a = 0; a < tab_arcs->nb_arcs; a++) {          //Parcours le niveau hiérarchique des arcs du tableau tab_arcs index=a
            int niva = tab_arcs->arcs[a].niv;

            if (niva == i) {                                   //Si niveau hiérarchique de l'arc (niva) = i alors..
                int opa = tab_arcs->arcs[a].opa;

                for (int b = 0; b < tab_arcs->nb_arcs; b++) {  //Parcours le niveau hiérarchique des arcs du tableau tab_arcs index=b
                    int nivb = tab_arcs->arcs[b].niv;

                    if (nivb >= i) {                           //Si niveau hiérarchique de l'arc (nivb) >= i et..
                        int opb = tab_arcs->arcs[b].opb;

                        if (opa == opb) {                      //Si op du Parcours a =  op du Parcours b alors..
                            tab_arcs->arcs[a].niv = i + 1;     //Mise à jour du niveau hiérarchique de l'arc index=a avec i+1 et mise a jour cpt = i + 1
                            cpt = i + 1;

                        } //Fin    Si op du Parcours a =  op du Parcours b alors
                    }     //Fin    Si niveau hiérarchique de l'arc (nivb) >= i et..
                } 		  //Fin    Parcours le niveau hiérarchique des arcs du tableau tab_arcs index=b
            }             //Fin    Si niveau hiérarchique de l'arc (niva) = i alors..
        }                 //Fin    Parcours le  niveau hiérarchique des arcs du tableau tab_arcs index=a
    } while (cpt > i);    //Sortie si cpt est supérieur à i la boucle ne trouve plus de niveau supérieur
}
// FIN    Fonction Hierarchie_Arcs

// Fonction de comparaison arcs niv,opa,opb
int compare_arcs(const void *a, const void *b) {
    // Compare d'abord par niveau hiérarchique (niv)
    int diff_niv = ((Arcs *)a)->niv - ((Arcs *)b)->niv;
    if (diff_niv != 0) {
        return diff_niv;
    }

    // Si les niveaux sont égaux, compare par opa
    int diff_opa = ((Arcs *)a)->opa - ((Arcs *)b)->opa;
    if (diff_opa != 0) {
        return diff_opa;
    }

    // Si opa est également égal, compare par opb
    return ((Arcs *)a)->opb - ((Arcs *)b)->opb;
}
// FIN Fonction de comparaison arcs niv,opa,opb

// Fonction pour trier le tableau d'arcs
void Trier_arcs(Tableau_arcs *tab_arcs) {
    qsort(tab_arcs->arcs, tab_arcs->nb_arcs, sizeof(Arcs), compare_arcs);
}
// FIN   Trier_arcs

// Fonction pour remplir les opérations
void Remplir_operations(Tableau_arcs *tab_arcs, Tableau_operations *tab_op) {

    // Initialisation du tableau des operations
    tab_op->operations = NULL;
    tab_op->nb_op = 0;
    tab_op->nb_priorite = 0;

    int opa;
    int priorite;
    int cpt = 0;

    // On Parcours opa du tableau des Arcs pour creer les operations trouvées si elles n'existent pas
    for (int a = 0; a < tab_arcs->nb_arcs; a++)    //Parcours du tableau des arcs index = a  recherche donnees (opa et niv)
    {
        opa = tab_arcs->arcs[a].opa;
        priorite = tab_arcs->arcs[a].niv;
        cpt = 0;

        for (int i = 0; i < tab_op->nb_op; i++)    // Parcours du tableau des operation index = i recherche donnees (opa)
        {
            if (opa == tab_op->operations[i].op) {  // On verifie si l'opération (opa) est déjà créer dans le tableau des operations
                cpt = 1;
                break;
            }
        }                                          //Fin Parcours du tableau des operation index = i

        if (cpt == 0) {                            // L'operation (opa) n'existe pas dans le tableau des operations alors ajout

            // Ajustement dynamique de la taille du tableau operations
            tab_op->operations = (Operations *)realloc(tab_op->operations, (tab_op->nb_op + 1) * sizeof(Operations));
            if (tab_op->operations == NULL) {perror("Erreur lors de la réallocation de mémoire tableau operations"); exit(EXIT_FAILURE);}

            // Initialisation du tableau d'antécédents
            tab_op->operations[tab_op->nb_op].antecedents = NULL;
            tab_op->operations[tab_op->nb_op].nb_antecedents = 0;
            tab_op->operations[tab_op->nb_op].op = opa;
            tab_op->operations[tab_op->nb_op].priorite = priorite;
            tab_op->operations[tab_op->nb_op].temps = 0.00;
            tab_op->operations[tab_op->nb_op].temps_avant = 0.00;
            tab_op->operations[tab_op->nb_op].ws = 0;
            tab_op->nb_op++;
            tab_op->nb_priorite = priorite;
        }
    }  // FIN du Parcours opa du tableau des Arcs pour creer les operations trouvées si elles n'existent pas

    // On Parcours opb du tableau des Arcs pour creer les operations trouvées si elles n'existent pas
    for (int b = 0; b < tab_arcs->nb_arcs; b++)    //Parcours du tableau des arcs index = b
    {
        int  opb = tab_arcs->arcs[b].opb;
        priorite = tab_arcs->arcs[b].niv;
        cpt = 0;

        for (int i = 0; i < tab_op->nb_op; i++)                //Parcours du tableau des operation index = i
        {
            if (opb == tab_op->operations[i].op)               //si l'opération existe dans le tableau cpt = 1
            {cpt = 1;
                if (priorite+1 > tab_op->operations[i].priorite) {tab_op->operations[i].priorite=priorite+1;}
            }
        }												       //Fin Parcours du tableau des operation index = i


        if (cpt == 0)                              // si l'opération n'existe pas dans le tableau alors ajout de l'opération
        {
            // Ajustement dynamique de la taille du tableau operations
            tab_op->operations = (Operations *)realloc(tab_op->operations, (tab_op->nb_op + 1) * sizeof(Operations));
            if (tab_op->operations == NULL) {perror("Erreur lors de la réallocation de mémoire tableau operations");exit(EXIT_FAILURE);}

            // Initialisation du tableau d'antécédents
            tab_op->operations[tab_op->nb_op].antecedents = NULL;
            tab_op->operations[tab_op->nb_op].nb_antecedents = 0;

            tab_op->operations[tab_op->nb_op].op = opb;
            tab_op->operations[tab_op->nb_op].priorite = priorite + 1;
            tab_op->operations[tab_op->nb_op].temps = 0.00;
            tab_op->operations[tab_op->nb_op].temps_avant = 0.00;
            tab_op->operations[tab_op->nb_op].ws = 0;
            cpt=1;
            tab_op->nb_op++;
            tab_op->nb_priorite = priorite + 1;
        }  // Fin  if (cpt == 0)
    } // Fin du Parcours opb du tableau des Arcs pour creer les operations trouvées si elles n'existent pas
    //on recherhce les antécédents pour les opérations de priorite >0
    for (int i = 0; i < tab_op->nb_op; i++) {                        //Parcours du tableau des operation index = i rechere op,priorite
        priorite = tab_op->operations[i].priorite;
        int op = tab_op->operations[i].op;

        if (priorite > 0)
        {
            for (int b = 0; b < tab_arcs->nb_arcs; b++) {           //Parcours du tableau des arcs index = b recherche opb


                if (op == tab_arcs->arcs[b].opb)
                {
                    // Ajustement dynamique de la taille du tableau d'antécédents
                    tab_op->operations[i].antecedents = (int *)realloc(tab_op->operations[i].antecedents,(tab_op->operations[i].nb_antecedents + 1) * sizeof(int));
                    if (tab_op->operations[i].antecedents == NULL) {perror("Erreur lors de la réallocation de mémoire tableau antecedents");exit(EXIT_FAILURE);}

                    // Ajout de l'antécédent au tableau
                    tab_op->operations[i].antecedents[tab_op->operations[i].nb_antecedents] = tab_arcs->arcs[b].opa;
                    tab_op->operations[i].nb_antecedents++;
                    cpt=0;
                }  // Fin if (op == tab_arcs->arcs[b].opb)
            }  // Fin Parcours du tableau des arcs index = b recherche opb
        }   // Fin if (priorite > 0)
    }  // Fin de recherhce les antécédents pour les opérations de priorite >0
}
// FIN Fonction pour remplir les opérations

// Fonction compare_operations
int compare_operations(const void *a, const void *b) {

    // Compare d'abord priorite(niv)
    int diff_priorite = ((Operations *)a)->priorite - ((Operations *)b)->priorite;
    if (diff_priorite != 0) {
        return diff_priorite;
    }

    // Si les niveaux sont égaux, compare par temps
    int diff_temps = ((Operations *)a)->temps - ((Operations *)b)->temps;
    if (diff_temps != 0) {
        return diff_temps;
    }

    // Si temps est également égal, compare par op
    return ((Operations *)a)->temps - ((Operations *)b)->temps;


} // FIN Fonction compare_operations

// Fonction pour trier le tableau d'opérations
void Trier_operations(Tableau_operations *tab_op) {
    qsort(tab_op->operations, tab_op->nb_op, sizeof(Operations), compare_operations);
}
// FIN    Trier_operations

// Fonction pour libérer la mémoire allouée pour les tableaux
void liberer_memoire(Tableau_arcs *tab_arcs, Tableau_operations *tab_op) {
    for (int i = 0; i < tab_op->nb_op; i++) {
        free(tab_op->operations[i].antecedents);
    }
    free(tab_arcs->arcs);
    free(tab_op->operations);
}
// FIN liberer_memoire

// Fonction pour lire le fichier des temps des opérations
void temps_operations(Tableau_operations *tab_op) {
    FILE *fichier;
    fichier = fopen("operation.txt", "r");

    if (fichier == NULL) {perror("Erreur lors de l'ouverture du fichier operation.txt");exit(EXIT_FAILURE);
    }

    Temps_op *tableau = NULL;   // Création du tableau dynamique de structure Temps_op
    int tailleInitiale = 1;     // Taille initiale pour le tableau dynamique
    tableau = (Temps_op *)malloc(tailleInitiale * sizeof(Temps_op)); // Allocation de la mémoire pour le tableau dynamique

    int i = 0;
    int numero;
    float temps;


    // Lecture du fichier ligne par ligne
    while (fscanf(fichier, "%d %f", &numero, &temps) == 2) {
        i++; // Incrémentation  de i après chaque lecture réussie
        // Vérification de la taille allouée
        if (i >= tailleInitiale) {
            tailleInitiale++; // Incrémentation la taille du tableau dynamique
            tableau = (Temps_op *)realloc(tableau, tailleInitiale * sizeof(Temps_op)); // Réallouer de la mémoire pour le tableau avec la nouvelle taille

            // Vérifier si la réallocation de mémoire a réussi
            if (tableau == NULL) {perror("Erreur de réallocation de mémoire.\n");exit(EXIT_FAILURE);}
        }

        tableau[i].numero = numero;
        tableau[i].temps  = temps;
    }


    for (int i = 0; i < tab_op->nb_op; i++)
    {
        for (int j = 0;j < tailleInitiale; j++) {
            if (tableau[j].numero == tab_op->operations[i].op) {
                tab_op->operations[i].temps = tableau[j].temps;
            }
        }
    }
    free(tableau);
}
// FIN temps_operations

// Fonction Vider le tampon
void viderTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vider le tampon jusqu'à la fin de ligne ou la fin du fichier
    }
}
// FIN Fonction Vider le tampon

// Fonction temps_avant
void temps_avant(Tableau_operations *tab_op) {

    int op_ant;
    int priorite =0;
    int cpt=0;


    do { priorite++;

        for (int i = 0; i < tab_op->nb_op; i++)
        {

            if (priorite == tab_op->operations[i].priorite) {

                for (int ant = 0; ant < tab_op->operations[i].nb_antecedents; ant++) {

                    op_ant = tab_op->operations[i].antecedents[ant];

                    for (int j = 0; j < tab_op->nb_op; j++) {
                        if (tab_op->operations[j].op == op_ant)
                        {tab_op->operations[i].temps_avant =  tab_op->operations[j].temps+tab_op->operations[j].temps_avant;
                            ;cpt = priorite+1;}

                    }
                }
            }
        }
    } while (cpt >  priorite );
}
// FIN Fonction temps_avant

//Fonction Lire_Fichier_temps_cycle
void Lire_Fichier_temps_cycle(Tableau_ws *tab_ws) {
    FILE *fichier;
    float temps_cycle;

    //ouverture du fichier
    fichier = fopen("temps_cycle.txt", "r");
    if (fichier == NULL) {perror("Erreur lors de l'ouverture du fichier precedences.txt"); exit(EXIT_FAILURE);}

    //Initialisation du tableau ws
    tab_ws->ws = NULL;
    tab_ws->nb_ws = 0;
    temps_cycle = 0.0;

    // Lecture du fichier pour alimenter les  ws
    while (fscanf(fichier, "%f ", &temps_cycle) == 1)
    {
        //Mise à jour du temps cycle dans le tableau après lecture du fichier
        tab_ws->temps_cycle = temps_cycle;

    }
    fclose(fichier);
}
// FIN Fonction Lire_Fichier_temps_cycle

// Fonction pour créer et alimenter les postes de travail
void Creer_ws(Tableau_ws *tab_ws, Tableau_operations *tab_op) {

    // Parcours du tableau des opérations en fonction du nombre de priorités
    for (int priorite = 0; priorite < tab_op->nb_priorite; priorite++) {

        // Parcours du tableau des opérations en fonction du nombre d'opérations
        for (int op = 0; op < tab_op->nb_op; op++) {

            // Si l'opération est dans la priorité parcourue et qu'elle n'a pas de poste de travail affecté (ws=0) alors...
            if (tab_op->operations[op].priorite == priorite && tab_op->operations[op].ws == 0) {

                // Si le nombre de postes de travail = 0 ou si le temps restant est inférieur au temps de l'opération alors...
                if (tab_ws->nb_ws == 0 || tab_ws->ws[tab_ws->nb_ws - 1].temps_restant < tab_op->operations[op].temps) {

                    // Ajustement dynamique de la taille du tableau ws
                    tab_ws->ws = (Ws *)realloc(tab_ws->ws, (tab_ws->nb_ws + 1) * sizeof(Ws));
                    if (tab_ws->ws == NULL) { perror("Erreur lors de la réallocation de mémoire tableau ws"); exit(EXIT_FAILURE); }

                    // Ajout d'un poste de travail
                    tab_ws->ws[tab_ws->nb_ws].ws = tab_ws->nb_ws + 1;
                    tab_ws->ws[tab_ws->nb_ws].temps_ops = 0.00;
                    tab_ws->ws[tab_ws->nb_ws].temps_restant = tab_ws->temps_cycle;
                    tab_ws->ws[tab_ws->nb_ws].nb_ws_op = 0;
                    tab_ws->nb_ws++;
                }

                int nb_ws = tab_ws->nb_ws - 1;

                // Mise à jour des informations de l'opération et du poste de travail
                tab_op->operations[op].ws = tab_ws->nb_ws;
                tab_ws->ws[nb_ws].temps_ops += tab_op->operations[op].temps;
                tab_ws->ws[nb_ws].temps_restant -= tab_op->operations[op].temps;
                tab_ws->ws[nb_ws].nb_ws_op++;

            } // Fin du if (tab_op->operations[op].priorite == priorite && tab_op->operations[op].ws == 0)

        } // Fin du for (int op = 0; op < tab_op->nb_op; op++)
    } // Fin du for (int priorite = 0; priorite < tab_op->nb_priorite; priorite++)
} // FIN Fonction pour créer et alimenter les postes de travail


// Fonction pour créer et alimenter les postes de travail
void Ajuster_temps_cycle(Tableau_ws *tab_ws, Tableau_operations *tab_op) {

    float temps_cycle = tab_ws->temps_cycle;
    int nb_ws_ini = tab_ws->nb_ws;

    do {

        for (int k = 0; k < tab_op->nb_op; k++) { tab_op->operations[k].ws = 0 ; } // on reinitialise les operations sur ws=0

        temps_cycle -= .1;
        tab_ws->ws = NULL;
        tab_ws->nb_ws = 0;
        tab_ws->temps_cycle = temps_cycle;

        Creer_ws(tab_ws, tab_op);

    } while (nb_ws_ini==tab_ws->nb_ws) ;


    tab_ws->temps_cycle = temps_cycle + 0.1;
    tab_ws->ws = NULL;
    tab_ws->nb_ws = 0;
    for (int k = 0; k < tab_op->nb_op; k++) { tab_op->operations[k].ws = 0 ; }  // on reinitialise les operations sur ws=0
    Creer_ws(tab_ws, tab_op);

}
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_14_4_PRECEDENCES_H

