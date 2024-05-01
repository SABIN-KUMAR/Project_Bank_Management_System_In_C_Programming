#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct Account
{
    char bname[50];
    char bbranch[20];
    char name[30];
    char address[100];
    int accNo;
    float balance;
};

char fileName[] = "d:\\bank.txt";
struct Account acc;

//function declaration for the various condition.....
void NewAccount();
void Deposit();
void Withdrawn();
void Search();
void Logout();
void ShowOptions();
FILE *fptr;

int main()
{
    char option;
    int accSearch;
    fptr = fopen(fileName, "r+b");

    if (fptr == NULL)
    {
        fptr = fopen(fileName, "w+b");
        if (fptr == NULL)
        {
            printf("File cannot created......\n");
            exit(1);
        }
    }
    while (1)
    {
        printf("\n*********WELCOME TO THE BANK MANAGEMENT SYSTEM *********\n");
        ShowOptions();
        option = getch();
        printf("%c\n", option);
        switch (option)
        {
        case 'n':
            NewAccount();
            break;

        case 'd':
            printf("Account Number in which  you want to deposit: ");
            scanf("%d", &accSearch);
            Deposit(accSearch);
            break;

        case 'w':
            printf("Account Number from which you want to withdrawn:");
            scanf("%d", &accSearch);
            Withdrawn(accSearch);
            break;

        case 's':
            printf("Account Number to be searched:");
            scanf(" %d", &accSearch);
            Search(accSearch);
            break;

        case 'x':
            return 0;

        case 'c':
            system("cls");
            printf("Invalid Option");
            break;

        default:
            printf("Invalid Option\n");
            break;
        }
    }
    fclose(fptr);
    return 0;
}

//function for the selection choosing
void ShowOptions()
{
    printf("Choose Your Option:\n");
    printf("(n) - Create A New Account - \n");
    printf("(d) - Deposit Cash -  \n");
    printf("(w) - Withdraw Cash - \n");
    printf("(s) - Search Account - \n");
    printf("(x) - Exit The Program - \n");
    printf("(c) - Clear The  Screen\n");
}

// Function to create a new account.
void NewAccount()
{
    char bn[20];
    char bbr[20];
    int aNo;
    char add[100];
    float bal = 0;
    fflush(stdin);
    printf("Enter Bank Name : ");
    scanf("%s", bn);
    printf("Enter Branch Name : ");
    scanf("%s", bbr);
    printf("Name Of The Account Holder : ");
    scanf("%s", acc.name);
    printf("Enter Account Number : ");
    scanf("%d", &aNo);
    printf("Address Of Account Holder:");
    fflush(stdin);
    scanf("%s", acc.address);
    strcpy(acc.bname, bn);
    strcpy(acc.bbranch, bbr);
    acc.accNo = aNo;
    acc.balance = bal;
    fseek(fptr, 0, SEEK_END);
    fwrite(&acc, sizeof(acc), 1, fptr);
    printf("New Account Created Successfully!\n");
    printf("\n*****The Information For Your Reference*****\n");
    printf("Bank Name:%s\n", acc.bname);
    printf("Branch Name:%s\n", acc.bbranch);
    printf("Account holder name:%s\n", acc.name);
    printf("Account number:%d\n", acc.accNo);
    printf("Address Of Account Holder:%s\n", acc.address);
    printf("Available Balance Rs.%f\n", acc.balance);
    printf("***********************************************\n\n");
}

// Function to display all the records in file
void Search(int accNoForSearch)
{
    int isFound = 0;
    fseek(fptr, 0, SEEK_SET);
    while (fread(&acc, sizeof(acc), 1, fptr) == 1)
    {
        if (acc.accNo == accNoForSearch)
        {
            printf("\n********Account Information********\n");
            printf("\nName Of Bank: %s \n", acc.bname);
            printf("Branch Name: %s \n", acc.bbranch);
            printf("Account Holder Name: %s \n", acc.name);
            printf("Account number: %d\n", acc.accNo);
            printf("Address Of Account Holder: %s \n", acc.address);
            printf("Balance Available in this account =Rs.%f\n", acc.balance);
            isFound = 1;
            break;
        }
    }
    if (isFound == 0)
        printf("\n Account Number Not Found!!!!!!\n");
}

// Function to modify existing record of a user and deposit money
void Deposit(int accNoForSearch)
{
    int i = 0;
    float dpstAmt;
    fseek(fptr, 0, SEEK_SET);
    while (fread(&acc, sizeof(acc), 1, fptr) == 1)
    {
        i++;
        if (acc.accNo == accNoForSearch)
        {
            printf("\nThe current balance for account %d is %f \n", accNoForSearch, acc.balance);
            printf("\nEnter  the amount to be deposited : ");
            scanf("%f", &dpstAmt);
            acc.balance += dpstAmt;
            fseek(fptr, (i - 1) * sizeof(acc), SEEK_SET);
            fwrite(&acc, sizeof(acc), 1, fptr);
            printf("\nThe Balance for account %d is %f \n", accNoForSearch, acc.balance);
            break;
        }
    }
}

// Function to search an account and withdraw money from account
void Withdrawn(int accNoForSearch)
{
    float wAmt;
    int i = 0;
    fseek(fptr, 0, SEEK_SET);
    while (fread(&acc, sizeof(acc), 1, fptr) == 1)
    {
        i++;
        if (acc.accNo == accNoForSearch)
        {
            printf("\nThe current balance for account %d is %f \n", accNoForSearch, acc.balance);
            printf("\nAmount you want to withdraw from account:");
            scanf("%f", &wAmt);
            if (wAmt <= acc.balance)
            {
                acc.balance -= wAmt;
                fseek(fptr, (i - 1) * sizeof(acc), SEEK_SET);
                fwrite(&acc, sizeof(acc), 1, fptr);
                printf("Your new balance for account %d is %f\n", accNoForSearch, acc.balance);
            }
            else
            {
                printf("Insufficient balance\n");
            }
            break;
        }
    }
}

/*This Project Might  Be Used In Future For Banking System To Manage Accounts Of Customers
*/