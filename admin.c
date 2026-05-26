#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "framework.h"

/* ==============================
   VIEW USERS
============================== */

void viewUsers()
{
    FILE *fp;

    int id;
    char name[100];
    char email[100];
    char password[100];
    char role[20];

    fp = fopen("users.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] users.txt not found!\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("                         ALL USERS\n");
    printf("===============================================================\n");

    printf("%-10s %-20s %-30s %-10s\n",
           "ID",
           "NAME",
           "EMAIL",
           "ROLE");

    printf("---------------------------------------------------------------\n");

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &id,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        printf("%-10d %-20s %-30s %-10s\n",
               id,
               name,
               email,
               role);
    }

    fclose(fp);
}

/* ==============================
   MAKE USER ADMIN
============================== */

void makeAdmin()
{
    FILE *fp;
    FILE *temp;

    int targetId;
    int id;
    int found = 0;

    char name[100];
    char email[100];
    char password[100];
    char role[20];

    printf("\nEnter User ID to Promote : ");

    if (scanf("%d", &targetId) != 1)
    {
        printf("\n[ERROR] ID must be numeric only!\n");

        while (getchar() != '\n');
        return;
    }

    fp = fopen("users.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\n[ERROR] File error!\n");
        return;
    }

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &id,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        if (id == targetId)
        {
            strcpy(role, "admin");
            found = 1;
        }

        fprintf(temp,
                "%d,%s,%s,%s,%s\n",
                id,
                name,
                email,
                password,
                role);
    }

    fclose(fp);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
    {
        printf("\n[SUCCESS] User promoted to ADMIN.\n");
    }
    else
    {
        printf("\n[ERROR] User not found.\n");
    }
}

/* ==============================
   DELETE USER
============================== */

void deleteUser()
{
    FILE *fp;
    FILE *temp;

    int targetId;
    int id;
    int found = 0;

    char name[100];
    char email[100];
    char password[100];
    char role[20];

    printf("\nEnter User ID to Delete : ");

    if (scanf("%d", &targetId) != 1)
    {
        printf("\n[ERROR] ID must be numeric only!\n");

        while (getchar() != '\n');
        return;
    }

    if (targetId == 1000)
    {
        printf("\n[ERROR] Default admin cannot be deleted!\n");
        return;
    }

    fp = fopen("users.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\n[ERROR] File open error!\n");
        return;
    }

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%99[^,],%19[^\n]\n",
                  &id,
                  name,
                  email,
                  password,
                  role) == 5)
    {
        if (id == targetId)
        {
            found = 1;
            continue;
        }

        fprintf(temp,
                "%d,%s,%s,%s,%s\n",
                id,
                name,
                email,
                password,
                role);
    }

    fclose(fp);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
    {
        printf("\n[SUCCESS] User deleted.\n");
    }
    else
    {
        printf("\n[ERROR] User not found.\n");
    }
}

/* ==============================
   CHANGE ADMIN PASSWORD
============================== */

void changeAdminPassword()
{
    FILE *fp;

    int id;
    char name[100];
    char oldPassword[100];
    char newPassword[100];
    char confirmPassword[100];

    fp = fopen("admin.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] admin.txt not found!\n");
        return;
    }

    fscanf(fp,
           "%d,%99[^,],%99[^\n]",
           &id,
           name,
           oldPassword);

    fclose(fp);

    printf("\nEnter New Password : ");
    inputPassword(newPassword);

    printf("\nConfirm Password : ");
    inputPassword(confirmPassword);

    printf("\n");

    if (strcmp(newPassword,
               confirmPassword) != 0)
    {
        printf("\n[ERROR] Password mismatch!\n");
        return;
    }

    if (!validatePassword(newPassword))
    {
        return;
    }

    fp = fopen("admin.txt", "w");

    fprintf(fp,
            "%d,%s,%s",
            id,
            name,
            newPassword);

    fclose(fp);

    printf("\n[SUCCESS] Admin password changed!\n");
}

/* ==============================
   READ FILE
============================== */

void readFile()
{
    FILE *fp;
    char filename[300];
    char line[500];

    printf("\nEnter filename : ");
    scanf("%299s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open file.\n");
        return;
    }

    printf("\n========== FILE CONTENT ==========\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

/* ==============================
   MODIFY FILE
============================== */

void modifyFile()
{
    FILE *fp;

    char filename[300];
    char text[500];

    printf("\nEnter filename : ");
    scanf("%299s", filename);

    fp = fopen(filename, "a");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open file.\n");
        return;
    }

    getchar();

    printf("Enter text to append:\n");
    fgets(text, sizeof(text), stdin);

    fprintf(fp, "%s", text);

    fclose(fp);

    printf("\n[SUCCESS] File updated.\n");
}

/* ==============================
   DELETE FILE
============================== */

void deleteFile()
{
    char filename[300];

    printf("\nEnter filename to delete : ");
    scanf("%299s", filename);

    if (remove(filename) == 0)
    {
        printf("\n[SUCCESS] File deleted.\n");
    }
    else
    {
        printf("\n[ERROR] File deletion failed.\n");
    }
}

/* ==============================
   VIEW REPORTS
============================== */

void viewReports()
{
    FILE *fp;
    char line[500];

    fp = fopen("report.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] report.txt not found!\n");
        return;
    }

    printf("\n========== REPORTS ==========\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

/* ==============================
   VIEW ACTIVITY LOGS
============================== */

void viewActivityLogs()
{
    FILE *fp;
    char line[500];

    fp = fopen("activity_log.txt", "r");

    if (fp == NULL)
    {
        printf("\n[ERROR] activity_log.txt not found!\n");
        return;
    }

    printf("\n========== ACTIVITY LOGS ==========\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

/* ==============================
   ADMIN PANEL
============================== */

void adminPanel(int id,
                char name[])
{
    int choice;

    do
    {
        printf("\n=====================================================\n");
        printf("                    ADMIN PANEL\n");
        printf("=====================================================\n");

        printf("Admin : %s (ID: %d)\n",
               name,
               id);

        printf("\n1. View Users\n");
        printf("2. Make User Admin\n");
        printf("3. Delete User\n");
        printf("4. Read File\n");
        printf("5. Modify File\n");
        printf("6. Delete File\n");
        printf("7. Change Admin Password\n");
        printf("8. View Reports\n");
        printf("9. View Activity Logs\n");
        printf("10. Logout\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Invalid input!\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            viewUsers();
            break;

        case 2:
            makeAdmin();
            break;

        case 3:
            deleteUser();
            break;

        case 4:
            readFile();
            break;

        case 5:
            modifyFile();
            break;

        case 6:
            deleteFile();
            break;

        case 7:
            changeAdminPassword();
            break;

        case 8:
            viewReports();
            break;

        case 9:
            viewActivityLogs();
            break;

        case 10:
            printf("\nLogging out...\n");
            break;

        default:
            printf("\n[ERROR] Invalid choice!\n");
        }

    } while (choice != 10);
}