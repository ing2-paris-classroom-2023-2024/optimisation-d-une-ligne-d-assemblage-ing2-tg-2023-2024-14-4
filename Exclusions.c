#include <stdio.h>
#include "Header_general.h"

typedef struct Operations
{
    int Op[10];
    int tempsOperations;
}t_Operations;

typedef struct Stations
{
    int nbStations;

}t_Stations;

int Exclusion()
{
    FILE *listeExclusions;
    listeExclusions=fopen("exclusions.txt","r");
    if(listeExclusions==NULL)
    {
        printf("Pb d'affichage\n");
    }
    printf("Test Exclusions");
    return 0;
}