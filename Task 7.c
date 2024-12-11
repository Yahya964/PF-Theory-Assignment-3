#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ContentMetadata {
    char title[100];
    float rating;
    int runtime;  
    char encodingFormats[50];
};

double** createEngagementMatrix(int numUsers, int numCategories) {
    double **matrix = (double**)malloc(numUsers * sizeof(double*));
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (double*)malloc(numCategories * sizeof(double));
        for (int j = 0; j < numCategories; j++) {
            matrix[i][j] = 0.0; 
        }
    }
    return matrix;
}

int** createDeviceMatrix(int numUsers, int numDevices) {
    int **matrix = (int**)malloc(numUsers * sizeof(int*));
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (int*)malloc(numDevices * sizeof(int));  
        for (int j = 0; j < numDevices; j++) {
            matrix[i][j] = 0;  
        }
    }
    return matrix;
}

struct ContentMetadata*** createContentMetadataMatrix(int numCategories, int numContents) {
    struct ContentMetadata ***matrix = (struct ContentMetadata***)malloc(numCategories * sizeof(struct ContentMetadata**));
    for (int i = 0; i < numCategories; i++) {
        matrix[i] = (struct ContentMetadata**)malloc(numContents * sizeof(struct ContentMetadata*));
        for (int j = 0; j < numContents; j++) {
            matrix[i][j] = (struct ContentMetadata*)malloc(sizeof(struct ContentMetadata));
            strcpy(matrix[i][j]->title, "");
            matrix[i][j]->rating = 0.0;
            matrix[i][j]->runtime = 0;
            strcpy(matrix[i][j]->encodingFormats, "");
        }
    }
    return matrix;
}

void updateEngagement(double** engagementMatrix, int userIndex, int categoryIndex, double score) {
    engagementMatrix[userIndex][categoryIndex] = score;
}

void updateDevicePreferences(int** deviceMatrix, int userIndex, int deviceIndex, int preference) {
    deviceMatrix[userIndex][deviceIndex] = preference;
}

void updateContentMetadata(struct ContentMetadata*** contentMatrix, int categoryIndex, int contentIndex, char* title, float rating, int runtime, char* encodingFormats) {
    strcpy(contentMatrix[categoryIndex][contentIndex]->title, title);
    contentMatrix[categoryIndex][contentIndex]->rating = rating;
    contentMatrix[categoryIndex][contentIndex]->runtime = runtime;
    strcpy(contentMatrix[categoryIndex][contentIndex]->encodingFormats, encodingFormats);
}

void displayEngagementMatrix(double** engagementMatrix, int numUsers, int numCategories) {
    for (int i = 0; i < numUsers; i++) {
        printf("User %d Engagement: ", i + 1);
        for (int j = 0; j < numCategories; j++) {
            printf("Category %d: %.2f  ", j + 1, engagementMatrix[i][j]);
        }
        printf("\n");
    }
}

void displayDeviceMatrix(int** deviceMatrix, int numUsers, int numDevices) {
    for (int i = 0; i < numUsers; i++) {
        printf("User %d Device Preferences: ", i + 1);
        for (int j = 0; j < numDevices; j++) {
            printf("Device %d: %d  ", j + 1, deviceMatrix[i][j]);
        }
        printf("\n");
    }
}

void displayContentMetadataMatrix(struct ContentMetadata*** contentMatrix, int numCategories, int numContents) {
    for (int i = 0; i < numCategories; i++) {
        printf("Category %d:\n", i + 1);
        for (int j = 0; j < numContents; j++) {
            printf("  Content %d - Title: %s, Rating: %.2f, Runtime: %d mins, Formats: %s\n", j + 1,
                   contentMatrix[i][j]->title, contentMatrix[i][j]->rating, contentMatrix[i][j]->runtime,
                   contentMatrix[i][j]->encodingFormats);
        }
    }
}

int main() {
    int numUsers = 3, numCategories = 5, numDevices = 3, numContents = 4;
    
    double** engagementMatrix = createEngagementMatrix(numUsers, numCategories);
    int** deviceMatrix = createDeviceMatrix(numUsers, numDevices);
    struct ContentMetadata*** contentMatrix = createContentMetadataMatrix(numCategories, numContents);
    
    updateEngagement(engagementMatrix, 0, 1, 8.5);
    
    updateDevicePreferences(deviceMatrix, 0, 0, 1080);  
    
    updateContentMetadata(contentMatrix, 1, 2, "Action Movie", 8.7, 120, "HD, Dolby");
    
    displayEngagementMatrix(engagementMatrix, numUsers, numCategories);
    displayDeviceMatrix(deviceMatrix, numUsers, numDevices);
    displayContentMetadataMatrix(contentMatrix, numCategories, numContents);
    
    for (int i = 0; i < numUsers; i++) {
        free(engagementMatrix[i]);
        free(deviceMatrix[i]);
    }
    free(engagementMatrix);
    free(deviceMatrix);
    
    for (int i = 0; i < numCategories; i++) {
        for (int j = 0; j < numContents; j++) {
            free(contentMatrix[i][j]);
        }
        free(contentMatrix[i]);
    }
    free(contentMatrix);
    
    return 0;
}
