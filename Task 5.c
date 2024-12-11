#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUPPLIES 10
#define MAX_NAME_LENGTH 50

void initializeInventory(char ***speciesSupplies, int numSpecies, int numSupplies) {
    *speciesSupplies = (char **)malloc(numSpecies * sizeof(char *));
    for (int i = 0; i < numSpecies; i++) {
        (*speciesSupplies)[i] = (char *)malloc(numSupplies * sizeof(char *));
        for (int j = 0; j < numSupplies; j++) {
            (*speciesSupplies)[i][j] = NULL;
        }
    }
}

void addSupplies(char ***speciesSupplies, int speciesIndex, int *numSupplies, int maxSupplies) {
    if (*numSupplies >= maxSupplies) {
        printf("Maximum number of supplies reached for this species.\n");
        return;
    }
    printf("Enter supply name for species %d: ", speciesIndex + 1);
    (*speciesSupplies)[speciesIndex][*numSupplies] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    fgets((*speciesSupplies)[speciesIndex][*numSupplies], MAX_NAME_LENGTH, stdin);
    (*speciesSupplies)[speciesIndex][*numSupplies][strcspn((*speciesSupplies)[speciesIndex][*numSupplies], "\n")] = 0;
    (*numSupplies)++;
}

void updateSupplies(char ***speciesSupplies, int speciesIndex, int supplyIndex) {
    printf("Enter new supply name for species %d, supply %d: ", speciesIndex + 1, supplyIndex + 1);
    fgets((*speciesSupplies)[speciesIndex][supplyIndex], MAX_NAME_LENGTH, stdin);
    (*speciesSupplies)[speciesIndex][supplyIndex][strcspn((*speciesSupplies)[speciesIndex][supplyIndex], "\n")] = 0;
}

void removeSpecies(char ***speciesSupplies, int *numSpecies, int speciesIndex) {
    for (int i = 0; i < MAX_SUPPLIES; i++) {
        free((*speciesSupplies)[speciesIndex][i]);
    }
    free((*speciesSupplies)[speciesIndex]);
    for (int i = speciesIndex; i < (*numSpecies) - 1; i++) {
        (*speciesSupplies)[i] = (*speciesSupplies)[i + 1];
    }
    (*numSpecies)--;
}

void displayInventory(char **speciesSupplies, int numSpecies, int *numSupplies) {
    for (int i = 0; i < numSpecies; i++) {
        printf("Species %d Supplies:\n", i + 1);
        for (int j = 0; j < *numSupplies; j++) {
            if (speciesSupplies[i][j] != NULL) {
                printf("  %s\n", speciesSupplies[i][j]);
            }
        }
    }
}

int main() {
    int numSpecies = 3;
    int numSupplies[MAX_SUPPLIES] = {0};

    char ***speciesSupplies;
    initializeInventory(&speciesSupplies, numSpecies, MAX_SUPPLIES);

    for (int i = 0; i < numSpecies; i++) {
        for (int j = 0; j < 2; j++) {
            speciesSupplies[i][j] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
            snprintf(speciesSupplies[i][j], MAX_NAME_LENGTH, "Supply %d", j + 1);
            numSupplies[i]++;
        }
    }

    int choice;
    do {
        printf("\n1. Add Supplies\n2. Update Supplies\n3. Remove Species\n4. Display Inventory\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int speciesIndex;
            printf("Enter species index (0-%d): ", numSpecies - 1);
            scanf("%d", &speciesIndex);
            getchar();
            addSupplies(&speciesSupplies, speciesIndex, &numSupplies[speciesIndex], MAX_SUPPLIES);
        } else if (choice == 2) {
            int speciesIndex, supplyIndex;
            printf("Enter species index (0-%d): ", numSpecies - 1);
            scanf("%d", &speciesIndex);
            printf("Enter supply index (0-%d): ", numSupplies[speciesIndex] - 1);
            scanf("%d", &supplyIndex);
            getchar();
            updateSupplies(&speciesSupplies, speciesIndex, supplyIndex);
        } else if (choice == 3) {
            int speciesIndex;
            printf("Enter species index to remove (0-%d): ", numSpecies - 1);
            scanf("%d", &speciesIndex);
            getchar();
            removeSpecies(&speciesSupplies, &numSpecies, speciesIndex);
        } else if (choice == 4) {
            displayInventory(speciesSupplies, numSpecies, numSupplies);
        }

    } while (choice != 5);

    return 0;
}
