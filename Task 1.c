#include <stdio.h>
#include <string.h>

typedef struct {
    int employee_code;
    char employee_name[40];
    int dateOfJoining;
} employee;

void employeeDetails(employee E[4]) {
    for (int i = 0; i < 4; i++) {
        printf("Enter details for employee %d:\n", i + 1);

        printf("Enter employee code: ");
        scanf("%d", &E[i].employee_code);

        printf("Enter employee name: ");
        getchar();
        fgets(E[i].employee_name, sizeof(E[i].employee_name), stdin);

        size_t len = strlen(E[i].employee_name);
        if (len > 0 && E[i].employee_name[len - 1] == '\n') {
            E[i].employee_name[len - 1] = '\0';
        }

        printf("Enter date of joining (DDMMYY): ");
        scanf("%d", &E[i].dateOfJoining);
    }
}

void displayTenure(employee E[4]) {
    int currentDate, currentYear, currentMonth, currentDay;
    int count = 0;

    printf("Enter current date (DDMMYY): ");
    scanf("%d", &currentDate);

    currentDay = currentDate / 10000;
    currentMonth = (currentDate / 100) % 100;
    currentYear = currentDate % 100;

    printf("\nEmployees with tenure more than 3 years:\n");

    for (int i = 0; i < 4; i++) {
        int joinDay = E[i].dateOfJoining / 10000;
        int joinMonth = (E[i].dateOfJoining / 100) % 100;
        int joinYear = E[i].dateOfJoining % 100;

        int tenureYears = (currentYear - joinYear);
        if (currentMonth < joinMonth || (currentMonth == joinMonth && currentDay < joinDay)) {
            tenureYears--;
        }

        if (tenureYears > 3) {
            count++;
            printf("\nEmployee Code: %d\n", E[i].employee_code);
            printf("Employee Name: %s\n", E[i].employee_name);
            printf("Date of Joining: %02d-%02d-%02d\n", joinDay, joinMonth, joinYear);
        }
    }

    if (count == 0) {
        printf("\nNo employees have a tenure of more than 3 years.\n");
    } else {
        printf("\nTotal employees with tenure more than 3 years: %d\n", count);
    }
}

int main() {
    employee E[4];

    employeeDetails(E);

    displayTenure(E);

    return 0;
}
