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
    if (fichier == NULL) {printf("Erreur lors de l'ouverture du fichier precedences.txt");}

    //Initialisation du tableau arcs
    tab_arcs->arcs = NULL;
    tab_arcs->nb_arcs = 0;

    // Lecture du fichier pour alimenter les  Arcs (opa, opb et niv à 0)
    while (fscanf(fichier, "%d %d", &opa, &opb) == 2)
    {
        // Ajustement dynamique de la taille du tableau arcs
        tab_arcs->arcs = (Arcs *)realloc(tab_arcs->arcs, (tab_arcs->nb_arcs + 1) * sizeof(Arcs));
        if (tab_arcs->arcs == NULL) { printf("Erreur lors de la réallocation de mémoire tableau arcs"); }

        // Ajout des Arcs au tableau
        tab_arcs->arcs[tab_arcs->nb_arcs].opa = opa;
        tab_arcs->arcs[tab_arcs->nb_arcs].opb = opb;
        tab_arcs->arcs[tab_arcs->nb_arcs].niv = 0;
        tab_arcs->nb_arcs++;

    } //Fin boucle while Lecture du fichier pour alimenter les  Arcs (opa, opb et niv à 0)
    fclose(fichier);
}
bool toutesLesContraintesDePrecedencesSontSatisfaites(Tableau_operations *tab_op, int index) {
    for (int i = 0; i < tab_op->operations[index].nb_antecedents; i++) {
        int antecedent = tab_op->operations[index].antecedents[i];
        if (tab_op->operations[indice(antecedent, *tab_op)].ws == 0) {
            return false;  // Retourner false si l'une des contraintes de précédence n'est pas satisfaite
        }
    }
    return true;  // Toutes les contraintes de précédence sont satisfaites
}

// Fonction pour vérifier si une opération a des exclusions avec les opérations déjà attribuées à une station
bool aDesExclusionsAvecLaStation(Tableau_operations *tab_op, int index, int station) {
    for (int i = 0; i < tab_op->nb_op; i++) {
        if (tab_op->operations[i].ws == station) {
            for (int j = 0; j < tab_op->operations[index].nombre_ex; j++) {
                int exclusion = tab_op->operations[index].ex[j];
                if (exclusion == tab_op->operations[i].op) {
                    return true;  // Retourner true si l'opération a une exclusion avec une opération déjà attribuée à la station
                }
            }
        }
    }
    return false;  // Aucune exclusion avec les opérations déjà attribuées à la station
}

void creerOptimiserStationsAvecCyclea(Tableau_operations *tab_op, Tableau_ws *tab_ws) {
    int numeroStation = 1;

    // Initialisation des workstations
    for (int i = 0; i < tab_op->nb_op; i++) {
        tab_op->operations[i].ws = 0; // Aucune workstation attribuée initialement
    }

    int operationsNonAttribuees = 1; // Flag pour suivre si toutes les opérations ont été attribuées

    // Tant qu'il reste des opérations non attribuées
    while (operationsNonAttribuees == 1) {
        operationsNonAttribuees = 0; // Réinitialiser le flag

        // Boucle principale pour attribuer les opérations aux workstations en tenant compte du temps de cycle
        for (int i = 0; i < tab_op->nb_op; i++) {
            // Si l'opération n'a pas de workstation attribuée, toutes les contraintes de précédence sont satisfaites,
            // et aucune exclusion avec les opérations déjà attribuées à la station
            if (tab_op->operations[i].ws == 0 && toutesLesContraintesDePrecedenceSontSatisfaites(tab_op, i)
                && !aDesExclusionsAvecLaStation(tab_op, i, numeroStation)) {

                float tempsOperation = tab_op->operations[i].temps;

                // Attribuer la workstation et afficher les opérations attribuées à cette workstation
                tab_op->operations[i].ws = numeroStation;
                printf("Station %d  : Op%d ", numeroStation, tab_op->operations[i].op);

                // Attribuer autant d'opérations suivantes que possible dans le temps de cycle à la même workstation
                for (int j = i + 1; j < tab_op->nb_op; j++) {
                    if (tab_op->operations[j].ws == 0) {
                        // Vérifier si toutes les opérations précédentes ont été effectuées (sont présentes dans une station)
                        bool prereqsDone = true;

                        for (int k = 0; k < tab_op->operations[j].nb_antecedents; k++) {
                            int antecedent = tab_op->operations[j].antecedents[k];

                            if (tab_op->operations[indice(antecedent, *tab_op)].ws == 0) {
                                prereqsDone = false;
                                break;  // Sortir de la boucle dès qu'une opération précédente n'est pas effectuée
                            }
                        }

                        if (prereqsDone) {
                            float tempsOperationSuivante = tab_op->operations[j].temps;

                            if ((tempsOperation + tempsOperationSuivante) <= tab_ws->temps_cycle
                                && !aDesExclusionsAvecLaStation(tab_op, j, numeroStation)) {
                                // L'opération suivante peut être ajoutée à la workstation sans dépasser le temps de cycle
                                // et sans avoir d'exclusions avec les opérations déjà attribuées à la station
                                tab_op->operations[j].ws = numeroStation;
                                tempsOperation += tempsOperationSuivante;
                                printf("Op%d ", tab_op->operations[j].op);
                            }
                        }
                    }
                }

                // Afficher le temps restant dans la station
                printf("(temps restant : %.2f)\n",tab_ws->temps_cycle-tempsOperation);
                numeroStation++;
            }
        }

        // Vérifier s'il reste des opérations non attribuées
        for (int k = 0; k < tab_op->nb_op; k++) {
            if (tab_op->operations[k].ws == 0) {
                operationsNonAttribuees = 1;
                break;
            }
        }
    }
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
    creerOptimiserStationsAvecCyclea(&tab_op,&tab_ws);





    return 0;
}
