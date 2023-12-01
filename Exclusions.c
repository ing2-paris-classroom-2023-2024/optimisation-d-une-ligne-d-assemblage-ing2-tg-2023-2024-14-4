#include <stdio.h>
#include "Exclusions.h"

void recuperation_donnees(tab_exclusions*a){
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
        // Ajout des Arcs au tableau


    } //Fin boucle while Lecture du fichier pour alimenter les  Arcs (opa, opb et niv à 0)
    /*for (int i = 0; i < a->nombre_ex; i++) {
        printf("%d %d ",a->ex[i].opa,a->ex[i].opb);
        printf("\n");
    }*/
    fclose(fichier);
}
void creation_station(tab_exclusions a){}
int mainexclusions(){
    tab_exclusions a;
    recuperation_donnees(&a);


    return 0;
}




