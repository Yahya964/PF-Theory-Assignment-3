#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct WeatherForecast {
    float temperature;
    float rainfall;
    float windSpeed;
};

struct Crop {
    char cropType[50];
    char growthStage[50];
    float expectedYield;
    struct WeatherForecast *forecast; 
};

struct Equipment {
    char toolName[50];
    char status[50];
    float fuelLevel;
    char schedule[100];
};

struct Sensor {
    float soilNutrients;
    float pHLevel;
    float pestActivity;
};

struct Field {
    char fieldName[50];
    float gpsCoordinates[2]; 
    float soilHealth;
    float moistureLevel;
    struct Crop *crops;
    struct Equipment *equipment;  
    struct Sensor *sensors; 
    int numCrops;
    int numEquipment;
    int numSensors;
};

struct RegionalHub {
    struct Field *fields; 
    int numFields;
};

struct CentralServer {
    struct RegionalHub *hubs; 
    int numHubs;
};

void allocateMemoryForField(struct Field *field, int numCrops, int numEquipment, int numSensors) {
    field->crops = (struct Crop *)malloc(numCrops * sizeof(struct Crop));
    field->equipment = (struct Equipment *)malloc(numEquipment * sizeof(struct Equipment));
    field->sensors = (struct Sensor *)malloc(numSensors * sizeof(struct Sensor));
    field->numCrops = numCrops;
    field->numEquipment = numEquipment;
    field->numSensors = numSensors;
}

void addCrop(struct Field *field, int cropIndex, char *cropType, char *growthStage, float expectedYield, struct WeatherForecast *forecast) {
    strcpy(field->crops[cropIndex].cropType, cropType);
    strcpy(field->crops[cropIndex].growthStage, growthStage);
    field->crops[cropIndex].expectedYield = expectedYield;
    field->crops[cropIndex].forecast = forecast;
}

void addEquipment(struct Field *field, int equipmentIndex, char *toolName, char *status, float fuelLevel, char *schedule) {
    strcpy(field->equipment[equipmentIndex].toolName, toolName);
    strcpy(field->equipment[equipmentIndex].status, status);
    field->equipment[equipmentIndex].fuelLevel = fuelLevel;
    strcpy(field->equipment[equipmentIndex].schedule, schedule);
}

void addSensor(struct Field *field, int sensorIndex, float soilNutrients, float pHLevel, float pestActivity) {
    field->sensors[sensorIndex].soilNutrients = soilNutrients;
    field->sensors[sensorIndex].pHLevel = pHLevel;
    field->sensors[sensorIndex].pestActivity = pestActivity;
}

void displayField(struct Field *field) {
    printf("Field Name: %s\n", field->fieldName);
    printf("GPS Coordinates: [%.2f, %.2f]\n", field->gpsCoordinates[0], field->gpsCoordinates[1]);
    printf("Soil Health: %.2f\n", field->soilHealth);
    printf("Moisture Level: %.2f\n", field->moistureLevel);
    
    printf("\nCrops:\n");
    for (int i = 0; i < field->numCrops; i++) {
        printf("  Crop: %s, Growth Stage: %s, Expected Yield: %.2f\n", field->crops[i].cropType, field->crops[i].growthStage, field->crops[i].expectedYield);
    }
    
    printf("\nEquipment:\n");
    for (int i = 0; i < field->numEquipment; i++) {
        printf("  Equipment: %s, Status: %s, Fuel Level: %.2f, Schedule: %s\n", field->equipment[i].toolName, field->equipment[i].status, field->equipment[i].fuelLevel, field->equipment[i].schedule);
    }
    
    printf("\nSensors:\n");
    for (int i = 0; i < field->numSensors; i++) {
        printf("  Soil Nutrients: %.2f, pH Level: %.2f, Pest Activity: %.2f\n", field->sensors[i].soilNutrients, field->sensors[i].pHLevel, field->sensors[i].pestActivity);
    }
}

int main() {
    struct CentralServer server;
    server.numHubs = 1;
    server.hubs = (struct RegionalHub *)malloc(server.numHubs * sizeof(struct RegionalHub));

    struct WeatherForecast forecast = {25.0, 100.0, 15.0};
    
    struct Field field;
    strcpy(field.fieldName, "Field 1");
    field.gpsCoordinates[0] = 11.34;
    field.gpsCoordinates[1] = 52.78;
    field.soilHealth = 60.5;
    field.moistureLevel = 65.0;
    
    allocateMemoryForField(&field, 2, 2, 2);
    
    addCrop(&field, 0, "Wheat", "Vegetative", 500.0, &forecast);
    addCrop(&field, 1, "Corn", "Reproductive", 700.0, &forecast);
    
    addEquipment(&field, 0, "Tractor", "Operational", 80.0, "8 AM - 4 PM");
    addEquipment(&field, 1, "Irrigation System", "Operational", 50.0, "On Demand");
    
    addSensor(&field, 0, 75.5, 6.5, 2.0);
    addSensor(&field, 1, 65.3, 6.8, 1.5);
    
    displayField(&field);
    
    free(field.crops);
    free(field.equipment);
    free(field.sensors);
    free(server.hubs);

    return 0;
}
