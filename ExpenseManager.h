#ifndef EXPENSEMANAGER_H_INCLUDED
#define EXPENSEMANAGER_H_INCLUDED

struct expense
{
    char date[20];
    float amount;
    char description[150];
    char category[50];
    int expense_id;
    struct expense* next;
};

typedef struct ExpenseTracker {
    int expense_id_counter;
    struct expense* expense_head;
} ExpenseTracker;
#endif // EXPENSEMANAGER_H_INCLUDED
