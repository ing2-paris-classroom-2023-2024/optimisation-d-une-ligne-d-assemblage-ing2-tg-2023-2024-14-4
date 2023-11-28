#include <stdio.h>
#include "Exclusions.h"
int TestExclusion(int Action1,int Action2)
{
    FILE *listeExclusions;
    int nbExclusions=0;
    int nb1;
    int nb2;
    int nbActions;
    int ActionCherchee=1;         // Variable où on cherche les exclusions de chaque action
    int tabExclusions[36][35];    // Tableau qui stocke 36 lignes car on utilise pas la ligne 0 qui correspond aux nombres d'actions et 35 qui correspond aux nombres d'exclusions de chaque actions qui est au maximum de 34 plus le nombres d'exclusions de l'action.
    for(int actions=0;actions<=35;actions++)
    {
        for(int j=0;j<=34;j++)
        {
            tabExclusions[actions][j]=0;                    // On remplit le tableau avec des 0 pour pas avoir des valeurs pourris
        }
    }
    if(listeExclusions==NULL)
    {
        printf("Pb d'affichage\n");
    }
    while(ActionCherchee<=35)                              // On parcours les 35 actions
    {
        listeExclusions=fopen("..\\exclusions.txt","r");
        while(feof(listeExclusions)==0)
        {
            fscanf(listeExclusions,"%d",&nb1);
            fscanf(listeExclusions,"%d",&nb2);
            if(ActionCherchee==nb1)                     // Si dans le fichier texte, on a l'action qu'on cherche dans notre ligne correspondante
            {
                tabExclusions[ActionCherchee][0]++;
                tabExclusions[ActionCherchee][tabExclusions[ActionCherchee][0]]=nb2;    // On met nb2 dans la 1ère colonne disponible de la ligne du numéro d'exclusion.
            }
        }
        ActionCherchee++;                                // On change la valeur de l'action
    }
    fclose(listeExclusions);
    for(nbActions=0;nbActions<=35;nbActions++)
    {
        printf("Action : %d : ",nbActions);                // Prendre les valeurs
        for(int j=0;j<=34;j++)
        {
            printf("%d ",tabExclusions[nbActions][j]);
        }
        printf("\n");
    }
    for(nbActions=1;nbActions<=34;nbActions++)
    {
        if(Action2==tabExclusions[Action1][nbActions])  // Il teste si 2 actions peuvent être ensembles, si il y'a un de ces chiffres dans la ligne alors il ne peuvent pas être ensemble.
        {
            return 0;
        }
    }
    for(nbActions=1;nbActions<=34;nbActions++)
    {
        if(Action1==tabExclusions[Action2][nbActions])  // Il teste si 2 actions peuvent être ensembles, comme le test précedent, mais en prenant en compte d'abord la 2ème action
        {
            return 0;
        }
    }
    return 1;
}

int Exclusion()
{
    t_assemblage Voiture;
    t_station *Stations;
    actions *Actions;
    Stations=(t_station*)malloc(sizeof(t_station)*1);
    if(Stations->station==NULL)
        printf("Pb de creation de stations\n");
    int valeurAction1=8;
    int valeurAction2=21;
    if(TestExclusion(valeurAction1,valeurAction2)==0)
    {
        printf("Les actions %d et %d ne peuvent pas se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    else
    {
        printf("Les actions %d et %d peuvent se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    printf("Nombre total de stations: %d\n",Stations->station);
    return 0;
}


