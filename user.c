#include <stdio.h>
#include <string.h>
#include <time.h>
#include "framework.h"

void myProfile(int id)
{
    FILE *fp;

    int fileId;
    char name[100];
    char email[100];
    char password[100];
    char role[20];

    fp = fopen("users.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open users.txt\n");
        return;
    }

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &fileId,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        if (fileId == id)
        {
            printf("\n=====================================================\n");
            printf("                    MY PROFILE\n");
            printf("=====================================================\n");

            printf("ID      : %d\n", fileId);
            printf("Name    : %s\n", name);
            printf("Email   : %s\n", email);
            printf("Role    : %s\n", role);

            printf("=====================================================\n");
            break;
        }
    }

    fclose(fp);
}

/* Auto Activity Logging */
void logActivity(int userId,
                 const char *userName,
                 const char *action,
                 const char *filename)
{
    FILE *fp;
    time_t now;
    struct tm *timeInfo;

    fp = fopen("activity_log.txt", "a");

    if (fp == NULL)
    {
        return;
    }

    time(&now);
    timeInfo = localtime(&now);

    fprintf(fp,
            "\n=====================================================\n");

    fprintf(fp,
            "DATE : %02d-%02d-%04d\n",
            timeInfo->tm_mday,
            timeInfo->tm_mon + 1,
            timeInfo->tm_year + 1900);

    fprintf(fp,
            "TIME : %02d:%02d:%02d\n",
            timeInfo->tm_hour,
            timeInfo->tm_min,
            timeInfo->tm_sec);

    fprintf(fp,
            "USER ID : %d\n",
            userId);

    fprintf(fp,
            "NAME : %s\n",
            userName);

    fprintf(fp,
            "ACTION : %s\n",
            action);

    if (filename != NULL)
    {
        fprintf(fp,
                "FILE : %s\n",
                filename);
    }

    fprintf(fp,
            "=====================================================\n");

    fclose(fp);
}

/* Auto Report Ownership */
void logReport(int userId,
               const char *userName,
               const char *action,
               const char *filename)
{
    FILE *fp;
    time_t now;
    struct tm *timeInfo;

    fp = fopen("report.txt", "a");

    if (fp == NULL)
    {
        return;
    }

    time(&now);
    timeInfo = localtime(&now);

    fprintf(fp,
            "\n=====================================================\n");

    fprintf(fp,
            "REPORT OWNER DETAILS\n");

    fprintf(fp,
            "=====================================================\n");

    fprintf(fp,
            "USER ID : %d\n",
            userId);

    fprintf(fp,
            "NAME : %s\n",
            userName);

    fprintf(fp,
            "ACTION : %s\n",
            action);

    fprintf(fp,
            "FILE : %s\n",
            filename);

    fprintf(fp,
            "DATE : %02d-%02d-%04d\n",
            timeInfo->tm_mday,
            timeInfo->tm_mon + 1,
            timeInfo->tm_year + 1900);

    fprintf(fp,
            "TIME : %02d:%02d:%02d\n",
            timeInfo->tm_hour,
            timeInfo->tm_min,
            timeInfo->tm_sec);

    fprintf(fp,
            "=====================================================\n");

    fclose(fp);
}

void uploadAndAnalyzeFile(int id,
                          char name[])
{
    char filename[300];
    int choice;

    printf("\nEnter File Name / Path: ");
    scanf("%299s", filename);

    do
    {
        printf("\n=====================================================\n");
        printf("                FILE ANALYSIS PANEL\n");
        printf("=====================================================\n");

        printf("User : %s (ID: %d)\n",
               name,
               id);

        printf("\n1. File Information\n");
        printf("2. Hex Dump\n");
        printf("3. Extract Strings\n");
        printf("4. Pattern Scan\n");
        printf("5. Full Analysis\n");
        printf("6. Back\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fileInfo(filename);

            logActivity(id,
                        name,
                        "File Information",
                        filename);

            logReport(id,
                      name,
                      "File Information",
                      filename);
            break;

        case 2:
            hexDump(filename);

            logActivity(id,
                        name,
                        "Hex Dump",
                        filename);

            logReport(id,
                      name,
                      "Hex Dump",
                      filename);
            break;

        case 3:
            extractStrings(filename);

            logActivity(id,
                        name,
                        "String Extraction",
                        filename);

            logReport(id,
                      name,
                      "String Extraction",
                      filename);
            break;

        case 4:
            patternScan(filename);

            logActivity(id,
                        name,
                        "Pattern Scan",
                        filename);

            logReport(id,
                      name,
                      "Pattern Scan",
                      filename);
            break;

        case 5:
            fullAnalysis(filename);

            logActivity(id,
                        name,
                        "Full Analysis",
                        filename);

            logReport(id,
                      name,
                      "Full Analysis",
                      filename);
            break;

        case 6:
            break;

        default:
            printf("\n[ERROR] Invalid choice!\n");
        }

    } while (choice != 6);
}

void userPanel(int id,
               char name[])
{
    int choice;

    do
    {
        printf("\n=====================================================\n");
        printf("                    USER PANEL\n");
        printf("=====================================================\n");

        printf("Welcome : %s (ID: %d)\n",
               name,
               id);

        printf("\n1. Upload & Analyze File\n");
        printf("2. My Profile\n");
        printf("3. Logout\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            uploadAndAnalyzeFile(id,
                                  name);
            break;

        case 2:
            myProfile(id);
            break;

        case 3:
            printf("\nLogging out...\n");
            break;

        default:
            printf("\n[ERROR] Invalid choice!\n");
        }

    } while (choice != 3);
}