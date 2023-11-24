#include <stdio.h>
#include "Exclusions.h"

int TestExclusion(int Action1,int Action2)
{
    FILE *listeExclusions;
    char c;
    int nbExclusions=0;
    int nb1,nb2;
    int ActionCherchee=1;         // Variable où on cherche les exclusions de chaque action
    int tabExclusions[36][35];    // Tableau qui stocke 36 lignes car on utilise pas la ligne 0 qui correspond aux nombres d'actions et 35 qui correspond aux nombres d'exclusions de chaque actions qui est au maximum de 34 plus le nombres d'exclusions de l'action.
    for(int actions=0;actions<=35;actions++)
    {
        for(int j=0;j<=34;j++)
        {
            tabExclusions[actions][j]=0;      // On remplit le tableau avec des 0 pour pas avoir des valeurs pourris
        }
    }
    if(listeExclusions==NULL)
    {
        printf("Pb d'affichage\n");
    }
    while(ActionCherchee<=35)
    {
        listeExclusions=fopen("exclusions.txt","r");
        while(feof(listeExclusions)==0)
        {
            fscanf(listeExclusions,"%d",&nb1);
            fscanf(listeExclusions,"%d",&nb2);
            if(ActionCherchee==nb1)             // Si dans le fichier texte, on a l'action qu'on cherche dans notre ligne
            {
                tabExclusions[ActionCherchee][0]++;
                tabExclusions[ActionCherchee][tabExclusions[ActionCherchee][0]]=nb2;    // On met nb2 dans la 1ère colonne disponible de la ligne du numéro d'exclusion.
            }
        }
        ActionCherchee++;      // On change la valeur de l'action
    }
    for(int actions=0;actions<=35;actions++)
    {
        printf("Action : %d : ",actions);           // Prendre les valeurs
        for(int j=0;j<=34;j++)
        {
            printf("%d ",tabExclusions[actions][j]);
        }
        printf("\n");
    }
    fclose(listeExclusions);
    return 0;
}

int Exclusion()
{
    t_assemblage Voiture;
    t_station *Stations;
    t_actions *Actions;
    int numExclusions=0;
    Stations=(t_station*)malloc(sizeof(t_station));
    if(Stations->station==NULL)
    {
        printf("Pb de creation de stations\n");
    }
    printf("Nombre total de stations: %d\n",Stations->station);
    int valeurAction1=1;
    int valeurAction2=4;
    if(TestExclusion(valeurAction1,valeurAction2)==0)
    {
        printf("Les actions %d et %d ne peuvent pas se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    else
    {
        printf("Les actions %d et %d peuvent se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    printf("Bonjour\n");
    return 0;
}


