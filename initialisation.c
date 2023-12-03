//
// Created by amaur on 13/11/2023.
//
#include "Header_general.h"
#include"Precedence.h"
#include "Exclusions.h"

int indice(int valeurdelaction,Tableau_operations voiture){
    for (int i = 0; i < voiture.nb_op; i++) {
        if(voiture.operations[i].op==valeurdelaction)return i;
    }
    printf("probleme lors de la fonction indice");
    return 0;
}
void Lire_Fichier_Arcs(Tableau_arcs *tab_arcs) {
    FILE *fichier;
    int opa, opb;

    //ouverture du fichier
    fichier = fopen("..\\precedence.txt", "r");
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
void verificationexclusions(Tableau_operations* tab_op, Tableau_ws *tab_ws,int numero){
    for (int i = 0; i < tab_op->nb_op; i++) {

    }
}
void creerOptimiserStationsAvecCycleEtPrecedenceetex(Tableau_operations* tab_op, Tableau_ws *tab_ws) {
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
                if (tab_op->operations[antecedent].ws == 0 || tab_op->operations[antecedent].ws > numeroStation) {
                    precedencesEffectuees = 0;
                    break;
                }
            }

            // Vérifier si l'opération respecte également la station actuelle
            if (precedencesEffectuees && estValideAvecStation(tab_op, i, numeroStation)) {
                // Attribuer la workstation et afficher les opérations attribuées à cette workstation
                tab_op->operations[i].ws = numeroStation;
                printf("Station %d : \nOp%d tpscumule:%.2f\n", numeroStation, tab_op->operations[i].op, tab_op->operations[i].temps);

                // Attribuer les opérations suivantes dans le temps de cycle à la même workstation
                for (int j = i + 1; j < tab_op->nb_op; j++) {
                    if ((tab_op->operations[j].ws == 0) && (estValideAvecExclusionsEtStation(tab_op, j, i, numeroStation)) && estValideAvecStation(tab_op, j, numeroStation)) {
                        float tempsOperationSuivante = tab_op->operations[j].temps;

                        // Vérifier la précédence de l'opération suivante
                        int precedencesOpSuivante = 1;
                        for (int l = 0; l < tab_op->operations[j].nb_antecedents; l++) {
                            int antecedentSuivant = tab_op->operations[j].antecedents[l];
                            if (tab_op->operations[antecedentSuivant].ws == 0 || tab_op->operations[antecedentSuivant].ws > numeroStation) {
                                precedencesOpSuivante = 0;
                                break;
                            }
                        }

                        if (precedencesOpSuivante && (tempsOperation + tempsOperationSuivante) <= tab_ws->temps_cycle) {
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

    // Vérification supplémentaire après la boucle pour s'assurer que tous les antécédents sont effectués
    for (int i = 0; i < tab_op->nb_op; i++) {
        if (tab_op->operations[i].ws == 0 || !estValideAvecExclusionsEtStation(tab_op, i, i, tab_op->operations[i].ws)) {
            // L'opération n'a pas été attribuée ou n'a pas respecté les antécédents et les exclusions
            printf("Erreur : Op%d ne peut pas être attribuée en respectant la précédence et les exclusions.\n", tab_op->operations[i].op);
            // Vous pouvez ajouter ici une gestion d'erreur appropriée, par exemple, sortir de la fonction ou prendre une action corrective.
        }
    }

    // Affichage du nombre total de stations utilisées
    printf("Nombre total de stations : %d\n", numeroStation - 1);
}


int estValideAvecExclusionsEtStation(Tableau_operations *tab_op, int opA, int opB, int station) {
    // Check exclusions for opA to opB
    for (int i = 0; i < tab_op->operations[opA].nombre_ex; i++) {
        if (tab_op->operations[opA].ex[i] == opB && tab_op->operations[opB].ws == station) {
            return 0; // OpA and OpB are excluded in the same station
        }
    }

    // Check exclusions for opB to opA
    for (int i = 0; i < tab_op->operations[opB].nombre_ex; i++) {
        if (tab_op->operations[opB].ex[i] == opA && tab_op->operations[opA].ws == station) {
            return 0; // OpB and OpA are excluded in the same station
        }
    }

    // Check precedences for opA
    for (int j = 0; j < tab_op->operations[opA].nb_antecedents; j++) {
        int antecedent = tab_op->operations[opA].antecedents[j];
        if (tab_op->operations[antecedent].ws > station) {
            return 0; // OpA has a precedence issue
        }
    }

    // Check precedences for opB
    for (int j = 0; j < tab_op->operations[opB].nb_antecedents; j++) {
        int antecedent = tab_op->operations[opB].antecedents[j];
        if (tab_op->operations[antecedent].ws > station) {
            return 0; // OpB has a precedence issue
        }
    }

    return 1; // No exclusion found or exclusions are in different stations
}



// Fonction pour vérifier si une opération est valide dans une station donnée
int estValideAvecStation(Tableau_operations *tab_op, int op, int station) {
    // Vérifier si l'opération respecte la station actuelle
    for (int j = 0; j < tab_op->operations[op].nb_antecedents; j++) {
        int antecedent = tab_op->operations[op].antecedents[j];
        if (tab_op->operations[antecedent].ws > station) {
            return 0;
        }
    }
    return 1; // Opération valide dans la station actuelle
}








int mainexplusprecedence(){
    tab_exclusions b;
    Tableau_arcs tab_arcs;
    Tableau_operations tab_op;
    Tableau_ws tab_ws;
    Lire_Fichier_Arcs(&tab_arcs);
    Remplir_operations(&tab_arcs, &tab_op);
    temps_operations(&tab_op);
    Lire_Fichier_temps_cycle(&tab_ws);
    recuperation_donnees(&b,&tab_op);
    creerOptimiserStationsAvecCycleEtPrecedenceetex(&tab_op, &tab_ws);




    return 0;
}
