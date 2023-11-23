#include <stdio.h>
#include "Header_general.h"

#define MAX_EXCLUSIONS 35

int TestExclusion(t_exclusions exclusions[],int numExclusions,int Action1,int Action2)
{
    int numero=0;
    for(numero=0;numero<numExclusions;numero++)
    {
        if((exclusions[numero].action1==Action1 && exclusions[numero].action2==Action2)||(exclusions[numero].action1==Action2 && exclusions[numero].action2==Action1))
        {
            return 1;
        }
    }
    return 0;
}

int Exclusion()
{
    FILE *listeExclusions;
    t_assemblage Assemblage;
    t_actions_duree Duree;
    int nbCycles=10;
    int nbOperations=35;
    char operations;
    listeExclusions=fopen("..\\exclusion.txt","r");
    if(listeExclusions==NULL)
    {
        printf("Pb d'affichage\n");
    }
    int maxActions=0;
    int action1;
    int action2;
    int numExclusions=0;
    t_exclusions exclusions[MAX_EXCLUSIONS];
    fclose(listeExclusions);
    printf("Nombre total d'actions : %d\n",maxActions);
    int valeurAction1=1;
    int valeurAction2=4;
    if(TestExclusion(exclusions, numExclusions, valeurAction1,valeurAction2)==0)
    {
        printf("Les actions %d et %d ne peuvent pas se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    else
    {
        printf("Les actions %d et %d peuvent se situer dans la meme station.\n",valeurAction1,valeurAction2);
    }
    return 0;
}


