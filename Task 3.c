#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateEmail(char* email) 
{
    int atSymbol = 0;
    int dot = 0;
    int i;

    if (email[0] == '\0') {
        return 0;
    }

    for (i = 0; email[i] != '\0'; i++) 
    {
        if (email[i] == '@')
        {
            atSymbol++;
        } else if (email[i] == '.' && atSymbol > 0) 
        {
            dot = 1;
        }
    }

    if (atSymbol == 1 && dot) 
    {
        return 1;
    } else 
    {
        return 0;
    }
}

int main() {
    char *email = NULL;
    int maxLength = 50;

    printf("Enter email address: ");
    
    email = (char*)malloc(maxLength * sizeof(char));
    if (email == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (fgets(email, maxLength, stdin) != NULL) 
    {
        email[strcspn(email, "\n")] = '\0';
    } else 
    {
        printf("Error reading input!\n");
        free(email);
        return 1;
    }

    if (validateEmail(email)) 
    {
        printf("Valid Email\n");
    } else 
    {
        printf("Invalid Email\n");
    }

    free(email);

    return 0;
}
