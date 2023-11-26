/*#include "Precedence.h"



actions rechercher_actions_la_plus_importante(t_assemblage voiture,t_station current){
    printf("MOST IMPORTANT ACTION ->");
    actions pas_de_voiture;
    pas_de_voiture.disponible=-1;
    int valeur_max=-1;
    for (int i = 0; i < voiture.nombre_actions; i++) {
        if(voiture.tab_actions[i].nombre_de_precedence>valeur_max && voiture.tab_actions[i].disponible==1 && (current.tempstotal+voiture.tab_actions[i].temps_action<voiture.tempsparstation))valeur_max=voiture.tab_actions[i].num_action;
    }
    printf("DONE : %d\n",valeur_max);
    if(valeur_max!=-1)return voiture.tab_actions[indice(valeur_max,voiture)];

    else{
        printf("PROBLEM");
        return pas_de_voiture;
    }
}//renvoie l'action non visite

int action_disponible_precedence(t_assemblage *voiture)
{
    printf("AVAILABLE ACTION -> ");
    for (int i = 0; i < voiture->nombre_actions; i++) {
        for (int j = 0; j < voiture->nombre_actions; j++) {
            if(voiture->tab_actions[i].disponible!=0) {
                for (int k = 0; k < voiture->tab_actions[j].nombre_de_precedence; k++) {
                    if (voiture->tab_actions[j].precedence[k] == voiture->tab_actions[i].num_action && voiture->tab_actions[i].disponible!=2){
                        voiture->tab_actions[i].disponible = 0;
                        //printf("i:%d  aa%d  aaaa%d  j%dk%d    ",i,voiture->tab_actions[j].precedence[k],voiture->tab_actions[i].num_action,j,k);
                    }
                }
            }
        }
    }
    printf(" DONE\n");
    return 1;
}
void ajout_precedence(actions current_action ,t_assemblage* voiture,int i){
    printf("PRECEED IN PROGRESS ->");
    voiture->tab_station[i].tempstotal+=current_action.temps_action;
    voiture->tab_station[i].nombre_action+=1;
    voiture->tab_station[i].station=(int*) realloc(voiture->tab_station[i].station,sizeof (int)*voiture->tab_station[i].nombre_action);
    voiture->tab_station[i].station[i]=current_action.num_action;
    voiture->tab_actions[indice(current_action.num_action,*voiture)].disponible=2;
    //printf("%d  ",indice(current_action.num_action,*voiture));


    printf(" DONE\n");
}
void afficher_action_disponible(t_assemblage voiture){
    printf("Actions Availables : ");
    for (int i = 0; i < voiture.nombre_actions; i++) {
        if(voiture.tab_actions[i].disponible==1)printf("%d ",voiture.tab_actions[i].num_action);
    }
    printf("\n");
}
void MAJ_action_disp(t_assemblage *voiture) {
    printf("debutMAJ : %d\n", voiture->nombre_actions);

    for (int i = 0; i < voiture->nombre_actions; i++) {
        int indicateur = 1;

        for (int j = 0; j < voiture->tab_actions[i].nombre_de_precedence; j++) {
            int indice_precedent = indice(voiture->tab_actions[i].precedence[j], *voiture);

            if (voiture->tab_actions[indice_precedent].disponible != 2) {
                indicateur = 0;
                break;
            }
        }

        if (indicateur) {
            voiture->tab_actions[i].disponible = 1;
        }
    }
}
void fonction_generale(t_assemblage *voitures){
    int i=0;
    actions mostimportant;
    action_disponible_precedence(voitures);
    while(rechercher_actions_la_plus_importante(*voitures,voitures->tab_station[i]).disponible!=-1) {
        printf("%d\n",i);
        while (voitures->tab_station[i].tempstotal < 5) {

            action_disponible_precedence(voitures);
            afficher_action_disponible( *voitures);
            mostimportant = rechercher_actions_la_plus_importante(*voitures, voitures->tab_station[i]);
            ajout_precedence(mostimportant, voitures, i);
            MAJ_action_disp(voitures);

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


// Fonction pour remplir un tableau de Arcs avec les données du fichier precedences.txt
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
    fichier = fopen("..\\operation.txt", "r");

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
    fichier = fopen("..\\temps_cycle.txt", "r");
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

int mainprecedence() {
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
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");
    printf("hello_world");









} // FIN MAIN