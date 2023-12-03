
//
// Created by leopo on 11/26/2023.
//
#include "Precedence.h"

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
            if (tab_op->operations == NULL) printf("Erreur lors de la réallocation de mémoire tableau operations");

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
            if (tab_op->operations == NULL)printf("Erreur lors de la réallocation de mémoire tableau operations");

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

}
// FIN Fonction pour remplir les opérations

// Fonction compare_operations



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
    fichier = fopen("..\\operation.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier operation.txt\n");
        return;
    }

    Temps_op *tableau = NULL;
    int tailleInitiale = 1;
    tableau = (Temps_op *)malloc(tailleInitiale * sizeof(Temps_op));

    if (tableau == NULL) {
        printf("Erreur d'allocation de mémoire pour le tableau Temps_op\n");
        fclose(fichier);
        return;
    }

    int i = 0;
    int numero;
    float temps;
    rewind(fichier);

    while (fscanf(fichier, "%d %f", &numero, &temps) == 2) {

        if (i >= tailleInitiale) {
            tailleInitiale++;
            tableau = (Temps_op *)realloc(tableau, tailleInitiale * sizeof(Temps_op));
            if (tableau == NULL) {
                printf("Erreur de réallocation de mémoire pour le tableau Temps_op\n");
                fclose(fichier);
                return;
            }
        }

        tableau[i].numero = numero;
        tableau[i].temps  = temps;
        i++;
    }
    tab_op->nb_op = i;

    for (int k = 0; k < tab_op->nb_op; k++) {

        for (int j = 0; j < tailleInitiale; j++) {

            if (tableau[j].numero == tab_op->operations[k].op) {
                tab_op->operations[k].temps = tableau[j].temps;
            }
        }
    }

    free(tableau);

    fclose(fichier);
}




//Fonction Lire_Fichier_temps_cycle
void Lire_Fichier_temps_cycle(Tableau_ws *tab_ws) {
    FILE *fichier;
    float temps_cycle;

    //ouverture du fichier
    fichier = fopen("..\\temps_cycle.txt", "r");
    if (fichier == NULL) printf("Erreur lors de l'ouverture du fichier precedences.txt");

    //Initialisation du tableau ws
    tab_ws->ws = NULL;
    tab_ws->nb_ws = 0;
    temps_cycle = 0;

    // Lecture du fichier pour alimenter les  ws
    while (fscanf(fichier, "%f ", &temps_cycle) == 1)
    {
        //Mise à jour du temps cycle dans le tableau après lecture du fichier
        tab_ws->temps_cycle = temps_cycle;

    }

    fclose(fichier);
}


// Fonction pour créer et optimiser les stations en tenant compte des cycles et des dépendances
void creerOptimiserStationsAvecCycleEtPrecedence(Tableau_operations *tab_op, Tableau_ws *tab_ws) {
    int numeroStation = 1;

    // Initialisation des workstations
    for (int i = 0; i < tab_op->nb_op; i++) {
        tab_op->operations[i].ws = 0; // Aucune workstation attribuée initialement
    }

    // Boucle principale pour attribuer les opérations aux workstations en tenant compte du temps de cycle
    for (int i = 0; i < tab_op->nb_op; i++) {
        // Si l'opération n'a pas de workstation attribuée
        if (tab_op->operations[i].ws == 0) {
            float tempsOperation = tab_op->operations[i].temps;

            // Vérifier si toutes les opérations antérieures ont été effectuées
            int precedencesEffectuees = 1;
            for (int k = 0; k < tab_op->operations[i].nb_antecedents; k++) {
                int antecedent = tab_op->operations[i].antecedents[k];
                if (tab_op->operations[antecedent].ws == 0) {
                    precedencesEffectuees = 0;
                    break;
                }
            }

            if (precedencesEffectuees) {
                // Attribuer la workstation et afficher les opérations attribuées à cette workstation
                tab_op->operations[i].ws = numeroStation;
                printf("Station %d : \nOp%d tpscumule:%.2f\n", numeroStation, tab_op->operations[i].op, tab_op->operations[i].temps);

                // Attribuer les opérations suivantes dans le temps de cycle à la même workstation
                for (int j = i + 1; j < tab_op->nb_op; j++) {
                    if (tab_op->operations[j].ws == 0) {
                        float tempsOperationSuivante = tab_op->operations[j].temps;

                        if ((tempsOperation + tempsOperationSuivante) <= tab_ws->temps_cycle) {
                            // L'opération suivante peut être ajoutée à la workstation sans dépasser le temps de cycle
                            tab_op->operations[j].ws = numeroStation;
                            tempsOperation += tempsOperationSuivante;
                            printf("Op%d tpscumule %.2f\n", tab_op->operations[j].op, tempsOperation);
                        }
                    }
                }

                printf("\n");
                numeroStation++;
            }
        }
    }

    // Affichage du nombre total de stations utilisées
    printf("Nombre total de stations : %d\n", numeroStation - 1);
}


int mainprecedence() {
    Tableau_arcs tab_arcs;
    Tableau_operations tab_op;
    Tableau_ws tab_ws;
    Lire_Fichier_Arcs(&tab_arcs);

    Remplir_operations(&tab_arcs, &tab_op);

    temps_operations(&tab_op);

    Lire_Fichier_temps_cycle(&tab_ws);

    creerOptimiserStationsAvecCycleEtPrecedence(&tab_op, &tab_ws);

    liberer_memoire(&tab_arcs, &tab_op);

    return 0;
}

















