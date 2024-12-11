#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int* ratings;     // Dynamically allocated array to store ratings
    int totalScore;   // Total score across all periods
};

void inputEmployees(struct Employee* employees, int numEmployees, int numPeriods) {
    for (int i = 0; i < numEmployees; i++) {
        printf("Enter ratings for Employee %d across %d periods:\n", i + 1, numPeriods);
        for (int j = 0; j < numPeriods; j++) {
            do {
                printf("Period %d rating (1-10): ", j + 1);
                scanf("%d", &employees[i].ratings[j]);
                if (employees[i].ratings[j] < 1 || employees[i].ratings[j] > 10) {
                    printf("Invalid input. Please enter a rating between 1 and 10.\n");
                }
            } while (employees[i].ratings[j] < 1 || employees[i].ratings[j] > 10);
        }
    }
}

void displayPerformance(struct Employee* employees, int numEmployees, int numPeriods) {
    printf("\nPerformance Ratings:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee %d: ", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            printf("%d ", employees[i].ratings[j]);
        }
        printf("\n");
    }
}

int findEmployeeOfTheYear(struct Employee* employees, int numEmployees, int numPeriods) {
    int bestEmployeeIndex = 0;
    float bestAverage = 0.0;

    for (int i = 0; i < numEmployees; i++) {
        int totalScore = 0;
        for (int j = 0; j < numPeriods; j++) {
            totalScore += employees[i].ratings[j];
        }
        float average = (float)totalScore / numPeriods;
        if (average > bestAverage) {
            bestAverage = average;
            bestEmployeeIndex = i;
        }
    }
    return bestEmployeeIndex;
}

int findHighestRatedPeriod(struct Employee* employees, int numEmployees, int numPeriods) {
    int bestPeriodIndex = 0;
    float bestPeriodAverage = 0.0;

    for (int j = 0; j < numPeriods; j++) {
        int totalScore = 0;
        for (int i = 0; i < numEmployees; i++) {
            totalScore += employees[i].ratings[j];
        }
        float average = (float)totalScore / numEmployees;
        if (average > bestPeriodAverage) {
            bestPeriodAverage = average;
            bestPeriodIndex = j;
        }
    }
    return bestPeriodIndex;
}

int findWorstPerformingEmployee(struct Employee* employees, int numEmployees, int numPeriods) {
    int worstEmployeeIndex = 0;
    float worstAverage = 10.0;

    for (int i = 0; i < numEmployees; i++) {
        int totalScore = 0;
        for (int j = 0; j < numPeriods; j++) {
            totalScore += employees[i].ratings[j];
        }
        float average = (float)totalScore / numPeriods;
        if (average < worstAverage) {
            worstAverage = average;
            worstEmployeeIndex = i;
        }
    }
    return worstEmployeeIndex;
}

int main() {
    int numEmployees, numPeriods;

    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);
    printf("Enter the number of evaluation periods: ");
    scanf("%d", &numPeriods);

    struct Employee* employees = (struct Employee*)malloc(numEmployees * sizeof(struct Employee));
    if (employees == NULL) {
        printf("Memory allocation failed for employees array!\n");
        return 1;
    }

    for (int i = 0; i < numEmployees; i++) {
        employees[i].ratings = (int*)malloc(numPeriods * sizeof(int));
        if (employees[i].ratings == NULL) {
            printf("Memory allocation failed for employee %d ratings!\n", i + 1);
            return 1;
        }
    }

    inputEmployees(employees, numEmployees, numPeriods);
    displayPerformance(employees, numEmployees, numPeriods);

    int employeeOfTheYear = findEmployeeOfTheYear(employees, numEmployees, numPeriods);
    printf("\nTop performing employee is: Employee %d\n", employeeOfTheYear + 1);

    int highestRatedPeriod = findHighestRatedPeriod(employees, numEmployees, numPeriods);
    printf("Highest Rated Period: Period %d\n", highestRatedPeriod + 1);

    int worstPerformingEmployee = findWorstPerformingEmployee(employees, numEmployees, numPeriods);
    printf("Worst Performing Employee is: Employee %d\n", worstPerformingEmployee + 1);

    for (int i = 0; i < numEmployees; i++) {
        free(employees[i].ratings);
    }
    free(employees);

    return 0;
}
