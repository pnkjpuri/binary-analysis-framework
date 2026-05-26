#include <stdio.h>
#include <string.h>
#include <time.h>
#include "framework.h"

/* ==============================
   USER LOGIN
============================== */

void loginUser()
{
    FILE *fp;
    FILE *activity;

    int enteredId;
    int fileId;
    int found = 0;

    char enteredPassword[100];

    char name[100];
    char email[100];
    char password[100];
    char role[20];

    time_t now;
    struct tm *timeInfo;

    fp = fopen("users.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] users.txt not found!\n");
        return;
    }

    printf("\n=========================================\n");
    printf("              USER LOGIN\n");
    printf("=========================================\n");

    printf("Enter Unique ID : ");

    if (scanf("%d", &enteredId) != 1)
    {
        printf("\n[ERROR] Unique ID must contain numbers only!\n");

        while (getchar() != '\n');

        fclose(fp);
        return;
    }

    printf("Enter Password : ");
    inputPassword(enteredPassword);
    printf("\n");

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &fileId,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        if (enteredId == fileId &&
            strcmp(enteredPassword,
                   password) == 0)
        {
            found = 1;

            printf("\n[SUCCESS] Login Successful!\n");
            printf("Welcome %s\n",
                   name);

            /* Activity Logging */
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
                        fileId);

                fprintf(activity,
                        "Name : %s\n",
                        name);

                fprintf(activity,
                        "Action : User Login\n");

                fprintf(activity,
                        "----------------------------------\n");

                fclose(activity);
            }

            fclose(fp);

            if (strcmp(role, "admin") == 0)
            {
                adminPanel(fileId,
                           name);
            }
            else
            {
                userPanel(fileId,
                          name);
            }

            return;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\n[ERROR] Invalid User ID or Password!\n");
    }
}

/* ==============================
   ADMIN LOGIN
============================== */

void adminLogin()
{
    FILE *fp;
    FILE *activity;

    int enteredId;
    int adminId;

    char enteredPassword[100];
    char adminName[100];
    char adminPassword[100];

    time_t now;
    struct tm *timeInfo;

    fp = fopen("admin.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] admin.txt not found!\n");
        return;
    }

    printf("\n=========================================\n");
    printf("              ADMIN LOGIN\n");
    printf("=========================================\n");

    printf("Enter Admin ID : ");

    if (scanf("%d", &enteredId) != 1)
    {
        printf("\n[ERROR] Admin ID must be numeric only!\n");

        while (getchar() != '\n');

        fclose(fp);
        return;
    }

    printf("Enter Password : ");
    inputPassword(enteredPassword);
    printf("\n");

    /* Read admin details from admin.txt */
    if (fscanf(fp,
               "%d,%99[^,],%99s",
               &adminId,
               adminName,
               adminPassword) != 3)
    {
        printf("\n[ERROR] Failed to read admin file!\n");

        fclose(fp);
        return;
    }

    fclose(fp);

    if (enteredId == adminId &&
        strcmp(enteredPassword,
               adminPassword) == 0)
    {
        printf("\n[SUCCESS] Admin Login Successful!\n");

        /* Activity Logging */
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
                    adminId);

            fprintf(activity,
                    "Name : %s\n",
                    adminName);

            fprintf(activity,
                    "Action : Admin Login\n");

            fprintf(activity,
                    "----------------------------------\n");

            fclose(activity);
        }

        adminPanel(adminId,
                   adminName);
    }
    else
    {
        printf("\n[ERROR] Invalid Admin ID or Password!\n");
    }
}