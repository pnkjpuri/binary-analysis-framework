#include <stdio.h>
#include "framework.h"

void showBanner()
{
    printf("=====================================================\n");
    printf("   BINARY ANALYSIS & REVERSE ENGINEERING FRAMEWORK\n");
    printf("=====================================================\n");
    printf("     ROLE BASED ACCESS CONTROL SYSTEM (RBAC)\n");
    printf("=====================================================\n");
    printf("      ADMIN + USER AUTHENTICATION SYSTEM\n");
    printf("=====================================================\n");
}

int main()
{
    int choice;

    do
    {
        showBanner();

        printf("\n================= MAIN MENU =================\n");
        printf("1. Register User\n");
        printf("2. User Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");

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
            registerUser();
            break;

        case 2:
            loginUser();
            break;

        case 3:
            adminLogin();
            break;

        case 4:
            printf("\nExiting Framework...\n");
            break;

        default:
            printf("\n[ERROR] Invalid Choice!\n");
        }

    } while (choice != 4);

    return 0;
}