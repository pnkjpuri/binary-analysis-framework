#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include "framework.h"

int validatePassword(char password[])
{
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;
    int length = strlen(password);

    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isupper(password[i]))
            upper = 1;
        else if (islower(password[i]))
            lower = 1;
        else if (isdigit(password[i]))
            digit = 1;
        else
            special = 1;

        if (password[i] == ' ')
        {
            printf("\n[ERROR] Spaces are not allowed in password.\n");
            return 0;
        }
    }

    if (length < 8)
    {
        printf("\n[ERROR] Password must be at least 8 characters.\n");
        return 0;
    }

    if (!upper)
    {
        printf("[ERROR] Password must contain at least one UPPERCASE letter.\n");
        return 0;
    }

    if (!lower)
    {
        printf("[ERROR] Password must contain at least one lowercase letter.\n");
        return 0;
    }

    if (!digit)
    {
        printf("[ERROR] Password must contain at least one number.\n");
        return 0;
    }

    if (!special)
    {
        printf("[ERROR] Password must contain at least one special character.\n");
        return 0;
    }

    return 1;
}

/* Password masking */
void inputPassword(char password[])
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();

        if (ch == 13)
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (i < 99)
        {
            password[i++] = ch;
            printf("*");
        }
    }
}

void registerUser()
{
    FILE *fp;
    FILE *activity;

    int id = 1001;
    int tempId;

    char name[100];
    char email[100];
    char password[100];
    char confirmPassword[100];
    char role[20] = "user";

    time_t now;
    struct tm *timeInfo;

    fp = fopen("users.txt", "a+");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open users file.\n");
        return;
    }

    rewind(fp);

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &tempId,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        id = tempId + 1;
    }

    printf("\n=========================================\n");
    printf("          USER REGISTRATION\n");
    printf("=========================================\n");

    printf("Generated Unique ID : %d\n", id);

    printf("Enter Name : ");
    scanf(" %[^\n]", name);

    printf("Enter Email : ");
    scanf("%99s", email);

    while (1)
    {
        printf("\nPassword Rules:\n");
        printf("- Minimum 8 characters\n");
        printf("- One uppercase letter\n");
        printf("- One lowercase letter\n");
        printf("- One digit\n");
        printf("- One special character\n");

        printf("\nEnter Password : ");
        inputPassword(password);

        printf("\n");

        if (!validatePassword(password))
        {
            printf("\nPlease try again.\n");
            continue;
        }

        printf("Confirm Password : ");
        inputPassword(confirmPassword);

        printf("\n");

        if (strcmp(password, confirmPassword) != 0)
        {
            printf("\n[ERROR] Password mismatch!\n");
            continue;
        }

        break;
    }

    fprintf(fp,
            "%d,%s,%s,%s,%s\n",
            id,
            name,
            email,
            password,
            role);

    fclose(fp);

    /* Activity logging */
    activity = fopen("activity_log.txt", "a");

    if (activity != NULL)
    {
        time(&now);
        timeInfo = localtime(&now);

        fprintf(activity,
                "\n[%02d-%02d-%04d %02d:%02d:%02d]\n",
                timeInfo->tm_mday,
                timeInfo->tm_mon + 1,
                timeInfo->tm_year + 1900,
                timeInfo->tm_hour,
                timeInfo->tm_min,
                timeInfo->tm_sec);

        fprintf(activity,
                "User ID : %d\n",
                id);

        fprintf(activity,
                "Name    : %s\n",
                name);

        fprintf(activity,
                "Action  : Registered Account\n");

        fprintf(activity,
                "----------------------------------------\n");

        fclose(activity);
    }

    printf("\n[SUCCESS] Registration completed!\n");
    printf("Your User ID : %d\n", id);
    printf("Role         : USER\n");
}