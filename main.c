#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ExpenseManager.h"
#include <time.h>
int main()
{

    printf("Hello and welcome to Expense Manager!\n");
    int loggedIn = 0;
    while (!loggedIn)
    {
        loggedIn = login();
        if (!loggedIn)
        {
            printf("Invalid username or password. Please try again.\n");
        }
    }
    printf("You made it in!\n");
    expense* head = NULL;
    int menu_option;
    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &menu_option);
        getchar();

        switch (menu_option)
        {
        case 1:
        {
            int expense_id;
            printf("Enter the expense ID: ");
            scanf("%d", &expense_id);

            expense* expense_to_edit = find_expense(head, expense_id);
            if (expense_to_edit == NULL)
            {
                printf("Expense not found. Creating a new expense...\n");

                char date[20];
                printf("Enter the date: ");
                scanf("%s", date);

                float amount;
                printf("Enter the amount: ");
                scanf("%f", &amount);

                char description[100];
                printf("Enter the description: ");
                scanf(" %[^\n]", description);

                char category[50];
                printf("Enter the category: ");
                scanf(" %[^\n]", category);

                // Validate the expense input
                if (!validate_expense_input(date, amount, description, category))
                {
                    printf("Invalid expense input. Please try again.\n");
                    break;
                }

                // Generate a new ID for the expense
                int new_id = generate_new_id(head);

                // Create a new expense
                expense* new_expense = createExpense(new_id, date, amount, description, category);

                // Insert the new expense into the list
                insert_expense(&head, new_expense);

                printf("New expense created with ID: %d\n", new_id);

            }
            else
            {
                printf("Expense ID already exists. Please try again.\n");
            }

            break;
        }
        case 2:
{
    char date[20];
    float amount;
    char description[150];
    char category[50];

    printf("Enter the date: ");
    scanf("%s", date);

    printf("Enter the amount: ");
    scanf("%f", &amount);
    getchar(); // Consume the newline character

    printf("Enter the description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = '\0';

    printf("Enter the category: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0';

    add_expense(head, amount, description, category);
    saveExpensesToFile(head);

    printf("Expense with ID %d added successfully.\n", head->expense_id);
    break;
}

        case 3:
        {
            int expense_id;
            printf("Enter the expense ID to delete: ");
            scanf("%d", &expense_id);
            delete_expense(head, expense_id);
            break;
        }
        case 4:
        {
            display_expenses(head);
            break;
        }
        case 5:
        {
            char category_name[50];
            printf("Enter the name of the category: ");
            scanf("%s", category_name);

            add_category(&category_head, category_name);
            printf("Category created successfully.\n");
            break;
        }
        case 6:
        {
            char category_name[50];
            printf("Enter the name of the category to delete: ");
            scanf("%s", category_name);

            delete_category(&category_head, category_name);
            break;
        }
        case 7:
        {
            int expense_id;
            printf("Enter the expense ID to edit: ");
            scanf("%d", &expense_id);
            edit_expense(head, expense_id);
            break;
        }
        case 8:
        {
            int option;
            int year;
            int month;

            printf("Generate Report:\n");
            printf("1. Yearly Report\n");
            printf("2. Monthly Report\n");
            printf("Select an option: ");
            scanf("%d", &option);

            switch (option)
            {
            case 1:
                printf("Enter the year: ");
                scanf("%d", &year);
                generate_report(head, year, 0);
                break;

            case 2:
                printf("Enter the year: ");
                scanf("%d", &year);
                printf("Enter the month: ");
                scanf("%d", &month);
                generate_report(head, year, month);
                break;

            default:
                printf("Invalid option.\n");
                break;
            }
        }
        case 9:
        {
            char backup_file_name[100];
            printf("Enter the name of the backup file: ");
            scanf("%s", backup_file_name);

            expense* expenses = restore_data(backup_file_name);
            if (expenses == NULL)
            {
                printf("Failed to restore data from the backup file.\n");
            }
            else
            {
                printf("Expense data restored successfully.\n");
                display_expenses(expenses); // Display the restored expenses
                free_expenses(expenses); // Free the allocated memory for the expenses
            }
            break;
        }

        case 0:
        {
            printf("Logging out...\n");
            loggedIn = 0; // Set loggedIn to 0 to prompt for login again
            break;
        }

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    }
    while(menu_option!= 0);
    free_expenses(head);
    printf("Thank you for using Expense Manager. Goodbye!\n");

    return 0;
}

