#include <stdio.h>
#include "Exclusions.h"
#include "float.h"
void temps_operations_ex(Tableau_operations *tab_op) {
    FILE *fichier;
    fichier = fopen("..\\operation.txt", "r");

    if (fichier == NULL)printf("Erreur lors de l'ouverture du fichier operation.txt\n");


    int tailleInitiale = 1;
    tab_op->operations = ( Operations *)malloc(tailleInitiale * sizeof(Operations));
    if (tab_op->operations == NULL) printf("Erreur d'allocation de mémoire pour le tableau Temps_op\n");
    while (fscanf(fichier, "%d %f", &tab_op->operations[(tailleInitiale-1)].op, &tab_op->operations[(tailleInitiale-1)].temps) == 2) {
        tab_op->operations[(tailleInitiale-1)].ws=0;
        tailleInitiale++;
        tab_op->operations = (Operations *)realloc(tab_op->operations, tailleInitiale * sizeof(Operations));
    }
    tailleInitiale--;
    tab_op->operations = (Operations *)realloc(tab_op->operations, tailleInitiale * sizeof(Operations));
    tab_op->nb_op=tailleInitiale;
    fclose(fichier);

}
void recuperation_donnees(tab_exclusions*a ,Tableau_operations *b){
    FILE *fichier;
    fichier= fopen("..\\exclusions.txt","r");
    int opa,opb;
    a->nombre_ex=0;
    if(fichier==NULL)printf("probleme lors de l ouverture du fichier exclusions");
    a->ex=NULL;
    while (fscanf(fichier, "%d %d", &opa, &opb) == 2)
    {
        // Ajustement dynamique de la taille du tableau arcs
        a->ex= (exclusions *)realloc(a->ex, ( a->nombre_ex+ 1) * sizeof(exclusions));
        if (a->ex == NULL) { printf("Erreur lors de la réallocation de mémoire tableau arcs");}
        a->ex[a->nombre_ex].opa=opa;
        a->ex[a->nombre_ex].opb=opb;
        a->nombre_ex++;
    }

    fclose(fichier);
    for (int i = 0; i < b->nb_op; i++) {
        b->operations[i].ex=NULL;
        b->operations[i].nombre_ex=0;
    }
    for (int i = 0; i < b->nb_op; i++) {
        for (int j = 0; j < a->nombre_ex; j++) {
            if (b->operations[i].op == a->ex[j].opa) {
                b->operations[i].nombre_ex++;
                b->operations[i].ex = (int *)realloc(b->operations[i].ex, sizeof(int) * b->operations[i].nombre_ex);
                b->operations[i].ex[(b->operations[i].nombre_ex - 1)] = a->ex[j].opb;
            }

            if (b->operations[i].op == a->ex[j].opb) {
                b->operations[i].nombre_ex++;
                b->operations[i].ex = (int *)realloc(b->operations[i].ex, sizeof(int) * b->operations[i].nombre_ex);
                b->operations[i].ex[(b->operations[i].nombre_ex - 1)] = a->ex[j].opa;
            }
        }
    }

}
int trouver_operation_disponible(Tableau_operations a,Ws* b){
    int nombre_max=0,station=-1,vrai=0;
    for (int i = 0; i < a.nb_op; i++) {
        if(a.operations[i].ws==0){
            //printf("%d",b.nb_ws);

                if(b->nb_ws_op!=0) {
                    for (int j = 0; j < b->nb_ws_op; j++) {
                        for (int k = 0; k < a.operations[i].nombre_ex; k++) {
                            //printf("tabOPE%d tabWS%d",a.operations[i].ex[k], b->tab_op[j]);
                            if (a.operations[i].ex[k] == b->tab_op[j]) {
                                vrai = 1;
                                //printf("vrai%d\n",a.operations[i].op);
                            }
                        }

                    }
                    if ((vrai == 0) && (a.operations[i].nombre_ex >= nombre_max)) {
                        nombre_max = a.operations[i].nombre_ex;
                        station = i;
                        //printf(" k%dkk\n ",i);
                    }
                    vrai = 0;
                }

        }
        if((b->nb_ws_op==0) && (a.operations[i].nombre_ex>=nombre_max) && (a.operations[i].ws==0)){
            nombre_max = a.operations[i].nombre_ex;
            station=i;
        }
    }
    return station;
}



int toutelesactions(Tableau_operations a){
    int m=0;
    for (int i = 0; i < a.nb_op; i++) {
        m+=a.operations[i].ws;
    }

    if(m==a.nb_op)return 1;
    return 0;
}











void afficher_stations(Tableau_operations *tab_op) {
    printf("Stations et leurs opérations :\n");

    // Recherche du nombre total de stations
    int nb_stations = 0;
    for (int i = 0; i < tab_op->nb_op; i++) {
        if (tab_op->operations[i].ws >= nb_stations) {
            nb_stations = tab_op->operations[i].ws + 1;
        }
    }

    // Affichage des opérations pour chaque station
    for (int i = 0; i < nb_stations; i++) {
        printf("Station %d : ", i);
        for (int j = 0; j < tab_op->nb_op; j++) {
            if (tab_op->operations[j].ws == i) {
                printf("%d ", tab_op->operations[j].op);
            }
        }
        printf("\n");
    }
}
int mainex2(){
    Tableau_ws c;
    c.ws=(Ws*) malloc(sizeof (Ws)*1);
    c.ws[0].tab_op=NULL;
    c.nb_ws=1;
    c.ws[0].nb_ws_op=0;



    Tableau_operations a;
    tab_exclusions b;
    temps_operations_ex(&a);
    recuperation_donnees(&b,&a);
    int i=0;
    int r=-1;
    do {
        //printf("a");
        do {
            r = trouver_operation_disponible(a, &c.ws[i]);
            printf("\nrr%d\n",r);
            //printf("r%d\n", r);
            if (r != -1) {
                a.operations[r].ws = 1;
                c.ws[i].nb_ws_op++;
                c.ws[i].tab_op = (int *) realloc(c.ws[i].tab_op, sizeof(int) * c.ws[i].nb_ws_op);
                c.ws[i].tab_op[(c.ws[i].nb_ws_op - 1)] = a.operations[r].op;

            }
        } while (r != -1);
        c.nb_ws++;
        c.ws=(Ws*) realloc(c.ws,sizeof (Ws)*c.nb_ws);
        c.ws[(c.nb_ws-1)].nb_ws_op=0;
        i++;
        c.ws[i].tab_op=NULL;


    }while(toutelesactions(a)==0);





    for (int j = 0; j <  c.ws[0].nb_ws_op; j++) {
        printf("%d ",c.ws[0].tab_op[j]);
    }
    printf("\n");
    for (int j = 0; j <  c.ws[1].nb_ws_op; j++) {
        printf("%d ",c.ws[1].tab_op[j]);
    }
    return 0;
}














// La fonction Chercher_action_plus_influente reste inchangée

/*
int action_est_disponible(int action ,tab_exclusions a,Tableau_ws* b){

    for (int i = 0; i < a.nombre_ex; i++) {
        if(b.ws==NULL) {
            if (a.ex[i].opa == action && a.ex[i].opb == 0)return 1;
            if (a.ex[i].opb == action && a.ex[i].opa == 0)return 1;
        }
        else{
            for (int j = 0; j < b->nb_ws; j++) {
                for (int k = 0; k < b.ws[j].nb_ws_op; k++) {
                    for (int l = 0; l < a.nombre_ex; l++) {
                        if(a.ex[i].opa == action && (a.ex[i].opb == 0 ||b.ws[j].ws
                    }
                }
            }
        }

    }
    return 0;
}*/






