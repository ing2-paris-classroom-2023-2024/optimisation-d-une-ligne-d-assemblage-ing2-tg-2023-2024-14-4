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


bool aDesExclusionsAvecLaStation(Tableau_operations *tab_op, int index, int station) {
    for (int i = 0; i < tab_op->nb_op; i++) {
        if (tab_op->operations[i].ws == station) {
            for (int j = 0; j < tab_op->operations[index].nombre_ex; j++) {
                int exclusion = tab_op->operations[index].ex[j];
                if (exclusion == tab_op->operations[i].op) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool toutesLesContraintesDePrecedenceSontSatisfaitesa(Tableau_operations *tab_op, int index) {
    for (int i = 0; i < tab_op->operations[index].nb_antecedents; i++) {
        int antecedent = tab_op->operations[index].antecedents[i];
        if (tab_op->operations[indice(antecedent,*tab_op)].ws == 0) {
            return false; // Contrainte de précédence violée
        }
    }
    return true; // Toutes les contraintes sont satisfaites
}

void creerOptimiserStationsAvecCyclea(Tableau_operations *tab_op, Tableau_ws *tab_ws) {
    int numeroStation = 1;

    // Initialisation des workstations
    for (int i = 0; i < tab_op->nb_op; i++) {
        tab_op->operations[i].ws = 0; // Aucune workstation attribuée initialement
    }

    int operationsAttribuees = 0;

    // Boucle principale pour attribuer les opérations aux workstations
    while (operationsAttribuees < tab_op->nb_op) {
        float tempsOperation = 0;

        // Attribuer autant d'opérations que possible dans le temps de cycle à la même workstation
        for (int i = 0; i < tab_op->nb_op; i++) {
            if (tab_op->operations[i].ws == 0 &&
                toutesLesContraintesDePrecedenceSontSatisfaitesa(tab_op, i) &&
                !aDesExclusionsAvecLaStation(tab_op, i, numeroStation) &&
                (tempsOperation + tab_op->operations[i].temps) <= tab_ws->temps_cycle) {

                tab_op->operations[i].ws = numeroStation;
                tempsOperation += tab_op->operations[i].temps;
                printf("Station %d : Op%d ", numeroStation, tab_op->operations[i].op);
                operationsAttribuees++;

                // Vérifier s'il existe d'autres opérations qui peuvent être ajoutées à la même station
                for (int j = 0; j < tab_op->nb_op; j++) {
                    if (tab_op->operations[j].ws == 0 &&
                        toutesLesContraintesDePrecedenceSontSatisfaitesa(tab_op, j) &&
                        !aDesExclusionsAvecLaStation(tab_op, j, numeroStation) &&
                        (tempsOperation + tab_op->operations[j].temps) <= tab_ws->temps_cycle) {

                        tab_op->operations[j].ws = numeroStation;
                        tempsOperation += tab_op->operations[j].temps;
                        printf("Op%d ", tab_op->operations[j].op);
                        operationsAttribuees++;
                    }
                }

                printf("(temps restant : %.2f)\n", tab_ws->temps_cycle - tempsOperation);
                numeroStation++;
                break; // Passer à la station suivante
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
