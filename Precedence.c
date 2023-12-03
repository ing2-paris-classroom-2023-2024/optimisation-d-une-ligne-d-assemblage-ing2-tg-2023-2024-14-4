#include "Precedence.h"



// Fonction pour remplir un tableau de Arcs avec les données du fichier precedences.txt

// FIN Fonction Lire_Fichier_Arcs

// Fonction pour déterminer le niveau hiérarchique des arcs (niv)
void Hierarchie_Arcs(Tableau_arcs *tab_arcs) {
    int cpt=0;
    int i = -1;

    do { i++;   // Boucle index i

        for (int a = 0; a < tab_arcs->nb_arcs; a++) {
                                    //Parcours le niveau hiérarchique des arcs du tableau tab_arcs index=a
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


///LEs arcs sont tries avec tab_arc->arcs[b].niv plus l'arc est loin du point de depart plus son niveau est eleve


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
//permet de comparer les arcs en fonctions des niv puis des poa puis des opb

// FIN Fonction de comparaison arcs niv,opa,opb pour le qsort

// Fonction pour trier le tableau d'arcs
void Trier_arcs(Tableau_arcs *tab_arcs) {
    qsort(tab_arcs->arcs, tab_arcs->nb_arcs, sizeof(Arcs), compare_arcs);
}
/*void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
base : Pointeur vers le début du tableau à trier.
nmemb : Nombre d'éléments dans le tableau.
size : Taille en octets d'un élément du tableau.
compar : Pointeur vers une fonction de comparaison qui compare deux éléments du tableau.
 Cette fonction doit renvoyer un entier négatif si le premier élément est inférieur au deuxième,
 zéro s'ils sont égaux, et un entier positif si le premier élément est supérieur au deuxième.*/


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
                    if (tab_op->operations[i].antecedents == NULL) printf("Erreur lors de la réallocation de mémoire tableau antecedents");

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
    fichier = fopen("..\\operation.txt", "r");

    if (fichier == NULL) printf("Erreur lors de l'ouverture du fichier operation.txt");

    Temps_op *tableau = NULL;
    int tailleInitiale = 1;
    tableau = (Temps_op *)malloc(tailleInitiale * sizeof(Temps_op));



    int i=0;

    int numero;
    float temps;
    rewind(fichier);

    while (fscanf(fichier, "%d %f", &numero, &temps) == 2) {

        i++; // Incrémentation  de i après chaque lecture réussie
        // Vérification de la taille allouée
        if (i >= tailleInitiale) {
            tailleInitiale++; // Incrémentation la taille du tableau dynamique

            tableau = (Temps_op *)realloc(tableau, tailleInitiale * sizeof(Temps_op)); // Réallouer de la mémoire pour le tableau avec la nouvelle taille

            // Vérifier si la réallocation de mémoire a réussi
            if (tableau == NULL) printf("Erreur de réallocation de mémoire.\n");
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

    fclose(fichier);
}

// FIN Fonction Vider le tampon

// Fonction temps_avant
void temps_avant(Tableau_operations *tab_op) {

    int op_ant;//operation anterieur
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
                            cpt = priorite+1;}

                    }
                }
            }
        }
    } while (cpt >  priorite );
}
//progressivement en allant de 0 a la fin des priorite ont actualise les temps min avant
// FIN Fonction temps_avant

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


void creerOptimiserStationsAvecCycle(Tableau_operations *tab_op, Tableau_ws *tab_ws) {
    int numeroStation = 1;

    // Initialisation des workstations
    for (int i = 0; i < tab_op->nb_op; i++) {
        tab_op->operations[i].ws = 0; // Aucune workstation attribuée initialement
    }

    int operationsNonAttribuees = 1; // Flag pour suivre si toutes les opérations ont été attribuées

    // Tant qu'il reste des opérations non attribuées
    while (operationsNonAttribuees==1) {
        operationsNonAttribuees = 0; // Réinitialiser le flag

        // Boucle principale pour attribuer les opérations aux workstations en tenant compte du temps de cycle
        for (int i = 0; i < tab_op->nb_op; i++) {
            // Si l'opération n'a pas de workstation attribuée et toutes les contraintes de précédence sont satisfaites
            if (tab_op->operations[i].ws == 0 && toutesLesContraintesDePrecedenceSontSatisfaites(tab_op, i)) {
                float tempsOperation = tab_op->operations[i].temps;

                // Attribuer la workstation et afficher les opérations attribuées à cette workstation
                tab_op->operations[i].ws = numeroStation;
                printf("Station %d  : Op%d ", numeroStation, tab_op->operations[i].op);


                // Attribuer autant d'opérations suivantes que possible dans le temps de cycle à la même workstation
                for (int j = i + 1; j < tab_op->nb_op; j++) {
                    if (tab_op->operations[j].ws == 0) {
                        // Vérifier si toutes les opérations précédentes ont été effectuées (sont présentes dans une station)
                        bool prereqsDone = true;
                        //printf("\n%d",tab_op->operations[j].op);
                        for (int k = 0; k < tab_op->operations[j].nb_antecedents; k++) {
                            int antecedent = tab_op->operations[j].antecedents[k];


                            if (tab_op->operations[indice(antecedent,*tab_op)].ws == 0) {
                                prereqsDone = false;
                                break;  // Sortir de la boucle dès qu'une opération précédente n'est pas effectuée
                            }
                        }

                        if (prereqsDone) {
                            float tempsOperationSuivante = tab_op->operations[j].temps;

                            if ((tempsOperation + tempsOperationSuivante) <= tab_ws->temps_cycle) {
                                // L'opération suivante peut être ajoutée à la workstation sans dépasser le temps de cycle
                                tab_op->operations[j].ws = numeroStation;
                                tempsOperation += tempsOperationSuivante;
                                printf("Op%d ", tab_op->operations[j].op);
                            }
                        }
                    }
                }


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


// Fonction pour vérifier si toutes les contraintes de précédence sont satisfaites pour une opération donnée
int toutesLesContraintesDePrecedenceSontSatisfaites(Tableau_operations *tab_op, int index) {
    for (int k = 0; k < tab_op->operations[index].nb_antecedents; k++) {
        int op_precedente = tab_op->operations[index].antecedents[k];
        if (tab_op->operations[op_precedente].ws == 0) {
            return 0; // Contrainte de précédence non satisfaite
        }
    }
    return 1; // Toutes les contraintes de précédence sont satisfaites
}

// Fonction pour vérifier s'il reste des opérations non attribuées
int ilResteDesOperationsNonAttribuees(Tableau_operations *tab_op) {
    for (int i = 0; i < tab_op->nb_op; i++) {
        if (tab_op->operations[i].ws == 0) {
            return 1; // Il reste des opérations non attribuées
        }
    }
    return 0; // Toutes les opérations ont été attribuées
}





int mainprecedence() {
    Tableau_arcs tab_arcs;
    Tableau_operations tab_op;
    Tableau_ws tab_ws;

    Lire_Fichier_Arcs(&tab_arcs);

    Hierarchie_Arcs(&tab_arcs);
    Trier_arcs(&tab_arcs);
    Remplir_operations(&tab_arcs, &tab_op);
    Trier_operations(&tab_op);

    temps_operations(&tab_op);
    temps_avant(&tab_op);
    Lire_Fichier_temps_cycle(&tab_ws);


    creerOptimiserStationsAvecCycle(&tab_op, &tab_ws);

    liberer_memoire(&tab_arcs, &tab_op);


    return 0;
}
