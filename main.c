/*
Name - Aaryan Sharma
CS 211 (Fall 2023) - Prof Scott Reckinger
Project - 2 (Food Web Analysis with Dynamic Memory)
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices
    int numPrey;
} Org;


void printWeb(Org* web, int numOrg) {

    for (int i=0; i<numOrg; i++) {


        if (web[i].numPrey != 0) {
            printf("  %s eats ",web[i].name);

            for (int j=0; j<web[i].numPrey-1; j++) {
                printf("%s, ", web[web[i].prey[j]].name);
            }

            printf("%s", web[web[i].prey[web[i].numPrey-1]].name);
        }

        else{
            printf("  %s",web[i].name);
        }

        printf("\n");
    }
}


void printApex(Org* web, int numOrg) {                                                                                  // Identify and print Organisms with no predators.
    for (int i=0; i<numOrg; i++) {
        int count = 0;

        for (int j=0; j<numOrg; j++) {
            for (int k=0; k<web[j].numPrey; k++) {
                if (web[j].prey[k] == i) {                                                                              // If the index of the Organism(i) exists in any "prey" array, then count is incremented.
                    count++;
                }
            }
        }

        if (count == 0) {                                                                                               // In case the Organism is not in any "prey" array, then it is an Apex Predator.
            printf("  %s\n", web[i].name);
        }
    }
}


void printVeg(Org* web, int numOrg) {                                                                                   // Identify and print Organisms with no prey.
    for (int i=0; i<numOrg; i++) {
        if (web[i].numPrey == 0) {                                                                                      // If an Organism has no prey, it is a producer.
            printf("  %s\n", web[i].name);
        }
    }
}


void printFlex(Org* web, int numOrg) {                                                                                  // Identity and print the Organisms with the most prey.
    int max = 0;
    for (int i=0; i<numOrg; i++) {                                                                                      // Get "max" from the for loop.
        if (web[i].numPrey > max) {
            max = web[i].numPrey;
        }
    }

    for (int j=0; j<numOrg; j++) {                                                                                      // Checking for "max" and printing the Organism name.
        if (max == web[j].numPrey) {
            printf("  %s\n", web[j].name);
        }
    }
}


void printTasty(Org* web, int numOrg) {                                                                                 // Identity and print Organisms eaten by the most other organisms.
    int tasty[numOrg];

    for (int i=0; i<numOrg; i++) {                                                                                      // Setting all of the elements to 0.
        tasty[i] = 0;
    }

    for (int i=0; i<numOrg; i++) {
        for (int j=0; j < web[i].numPrey; j++) {                                                                        // Counting the predators of an organism and incrementing their respective element in "tasty" array.
            if (web[i].prey[j] < numOrg) {
                tasty[web[i].prey[j]]++;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < numOrg; ++i) {                                                                                  // Setting the value of max, by traversing the "tasty" array.
        if (tasty[i] > max) {
            max = tasty[i];
        }
    }

    for (int i = 0; i < numOrg; ++i) {                                                                                  // Printing the names of the tastiest organisms.
        if (tasty[i] == max) {
            printf("  %s\n", web[i].name);
        }
    }


}


void printHeight(Org* web, int numOrg) {                                                                                // Calculate and print the length of the longest chain from a producer to each organism.
    int heights[numOrg];
    for (int i = 0; i < numOrg; ++i) {                                                                                  // Setting all of the elements to 0.
        heights[i] = 0;
    }

    bool Boolean;

    do {                                                                                                                // Do-While loop runs until the height is set as one more than its maximum prey height.
        Boolean = false;

        for (int i = 0; i < numOrg; ++i) {
            int max = -1;

            for (int j = 0; j < web[i].numPrey; j++) {                                                                  // For loop finds the max height for each element of "prey".
                if (web[i].prey[j] < numOrg) {
                    if (heights[web[i].prey[j]] > max) {
                        max = heights[web[i].prey[j]];
                    }
                }
            }

            if (heights[i] != max + 1) {                                                                                // If the height is not equal to one more than the maximum, the while loop runs again.
                heights[i] = max + 1;
                Boolean = true;
            }
        }
    } while (Boolean);

    for (int i = 0; i < numOrg; ++i) {
        printf("  %s: %d\n", web[i].name, heights[i]);
    }
}


void printVore(Org* web, int numOrgs) {

    printf("  Producers:\n");
    for (int i=0; i<numOrgs; i++) {                                                                                     // Printing producers.
        if (web[i].numPrey == 0) {
            printf("    %s\n", web[i].name);
        }
    }

    printf("  Herbivores:\n");
    for (int i = 0; i < numOrgs; i++) {                                                                                 // Printing herbivores(organisms which eat only producers).
        if (web[i].numPrey > 0) {
            bool Herbi = true;
            for (int j = 0; j < web[i].numPrey; j++) {
                if (web[web[i].prey[j]].numPrey != 0) {
                    Herbi = false;
                    break;
                }
            }
            if (Herbi) {
                printf("    %s\n", web[i].name);
            }
        }
    }

    printf("  Omnivores:\n");                                                                                           // Printing omnivores(organisms which eat both producers and non-producers).
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey > 0) {
            bool Pro = false;
            bool NonPro = false;
            for (int j = 0; j < web[i].numPrey; j++) {
                if (web[web[i].prey[j]].numPrey == 0) {
                    Pro = true;
                }

                else {
                    NonPro = true;
                }
            }
            if (Pro && NonPro) {
                printf("    %s\n", web[i].name);
            }
        }
    }

    printf("  Carnivores:\n");                                                                                          // Printing carnivores(organisms which eat only non-producers).
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey > 0) {
            bool NonPro = true;
            for (int j = 0; j < web[i].numPrey; j++) {
                if (web[web[i].prey[j]].numPrey == 0) {
                    NonPro = false;
                    break;
                }
            }
            if (NonPro) {
                printf("    %s\n", web[i].name);
            }
        }
    }
}


void buildWeb(Org* web, int numOrg, int predInd, int preyInd) {                                                         // Function to update food web by adding predator-prey relationship between specified organisms in a dynamically allocated array.

    int* pPtr = (int*) malloc(sizeof(int)*web[predInd].numPrey+1);                                                 // Increasing the size of "prey" array using malloc().

    for (int i=0; i<web[predInd].numPrey; i++) {                                                                        // Copying all of the data from "prey" to pPtr.
        pPtr[i] = web[predInd].prey[i];
    }
    pPtr[web[predInd].numPrey] = preyInd;                                                                               // Adding the new data to pPtr.

    free(web[predInd].prey);
    web[predInd].prey = pPtr;                                                                                           // Freeing and redirecting "prey" to pPtr.
    web[predInd].numPrey++;                                                                                             // Incrementing numPrey, after the new index has been added.
}


void extinction(Org** web, int* numOrgs, int index) {                                                                   // Function to update the food web, by removing a specific organism(present at "index").

    Org* wPtr;
    if (*numOrgs > 1 && web != NULL) {
        wPtr = (Org *) malloc(sizeof(Org) * (*numOrgs - 1));                                                       // Resizing "web" array.

        int offset = 0;                                                                                                 // Variable is used to change the indices of organisms present after the extinct species.
        for (int i = 0; i < *numOrgs; i++) {
            if (i == index) {

                free((*web)[i].prey);
                offset = 1;
            }
            else {
                wPtr[i - offset] = (*web)[i];
            }
        }
    }

    else {                                                                                                              // If there are 1 or no organisms, the "web" array is redirected to NULL ptr.
        wPtr = NULL;
    }

    free(*web);                                                                                                         // Freeing "web" array and redirecting it to wPtr.
    *web = wPtr;
    (*numOrgs)--;                                                                                                       // Decrementing the number of organisms present in "web" array.


    for (int i = 0; i < *numOrgs; i++) {
        Org* org = &(*web)[i];
        int found = 0;
        for (int j = 0; j < org->numPrey; j++) {
            if (org->prey[j] == index) {                                                                                // "found" is incremented if index is present in the "prey" array.
                found = 1;
            }
            else if (org->prey[j] > index) {                                                                            // Changing the values(that come after the index) present in the "prey" array.
                org->prey[j]--;
            }
        }

        if (found) {
            int* pPtr = (int*) malloc(sizeof(int) * (org->numPrey - 1));

            int offset = 0;
            for (int j = 0; j < org->numPrey; j++) {
                pPtr[j - offset] = org->prey[j];

                if (org->prey[j] != index) {
                    pPtr[j - offset] = org->prey[j];
                }
                else {
                    offset = 1;
                }
            }
            free(org->prey);
            org->prey = pPtr;
            org->numPrey--;
        }
    }
}




int main(void) {

    int numOrgs;
    printf("Welcome to the Food Web Application\n");
    printf("--------------------------------\n");
    printf("Enter number of organisms:\n");
    scanf("%d",&numOrgs);

    Org* web = NULL;
    if(numOrgs > 0) { //Do not malloc an empty array, leave it pointing to NULL
        web = (Org*)malloc(numOrgs*sizeof(Org));
    }

    printf("Enter names for %d organisms:\n", numOrgs);
    for (int i = 0; i < numOrgs; ++i) {
        scanf("%s",web[i].name);
        web[i].prey = NULL;
        web[i].numPrey = 0;
    }

    printf("Enter number of predator/prey relations:\n");
    int numRels;
    scanf("%d",&numRels);

    printf("Enter the pair of indices for the %d predator/prey relations\n",numRels);
    printf("the format is [predator index] [prey index]:\n");

    int predInd, preyInd;
    for (int i = 0; i < numRels; ++i) {
        scanf("%d %d",&predInd, &preyInd);
        buildWeb(web,numOrgs,predInd,preyInd);
    }
    printf("--------------------------------\n\n");

    printf("Food Web Predators & Prey:\n");
    printWeb(web, numOrgs);
    printf("\n");

    printf("Apex Predators:\n");
    printApex(web, numOrgs);
    printf("\n");

    printf("Producers:\n");
    printVeg(web, numOrgs);
    printf("\n");

    printf("Most Flexible Eaters:\n");
    printFlex(web, numOrgs);
    printf("\n");

    printf("Tastiest Food:\n");
    printTasty(web, numOrgs);
    printf("\n");

    printf("Food Web Heights:\n");
    printHeight(web, numOrgs);
    printf("\n");

    printf("Vore Types:\n");
    printVore(web, numOrgs);
    printf("\n");

    printf("--------------------------------\n");
    int extInd;
    printf("Enter extinct species index:\n");
    scanf("%d",&extInd);
    printf("Species Extinction: %s\n", web[extInd].name);
    extinction(&web,&numOrgs,extInd);
    printf("--------------------------------\n\n");


    printf("UPDATED Food Web Predators & Prey:\n");
    printWeb(web,numOrgs);
    printf("\n");

    printf("UPDATED Apex Predators:\n");
    printApex(web, numOrgs);
    printf("\n");

    printf("UPDATED Producers:\n");
    printVeg(web, numOrgs);
    printf("\n");

    printf("UPDATED Most Flexible Eaters:\n");
    printFlex(web, numOrgs);
    printf("\n");

    printf("UPDATED Tastiest Food:\n");
    printTasty(web, numOrgs);
    printf("\n");

    printf("UPDATED Food Web Heights:\n");
    printHeight(web, numOrgs);
    printf("\n");

    printf("UPDATED Vore Types:\n");
    printVore(web, numOrgs);
    printf("\n");
    printf("--------------------------------\n");

    for (int i=0; i<numOrgs; i++) {
        free(web[i].prey);
    }

    free(web);

    return 0;
}
