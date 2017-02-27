#include <stdio.h>
// Changed this from  "stdlb.h" to "stdlib.h"
#include <stdlib.h>

#define NUMACCOUNTS 8
#define MAXNAMELENGTH 15

// Added  "struct" here
typedef struct b_
{
	char* firstName;
	char* lastName;
	int ID;
	float balance;
} Account;

Account* loadBank(char* filename);
Account* findAccount(Account* bank, int input);
void printOptions();
void withdrawMoney(Account* account);
void depositMoney(Account* account);
void changeInfo(Account* account);
void writeBackInfo(char* filename, Account* bank);
// Added freeBank() declaration
void freeBank(Account* bank);

int main(int argc, char** argv)
{
	// Declared the int input for use later 
	int input;
	
	if(argc != 2)
	{
		printf("Usage: ./a.out <account record file>\n");
		return -1;
	}
	
	// Made bank a Account* not Account
	Account* bank = loadBank(argv[1]);

	if(bank == NULL)
	{
		printf("Error reading account record file. Try again.\n");
		return -1;
	}

	while(1)
	{

		printf("Please login with your account ID (-1 to exit):\n");
		printf(">");
		scanf("%d", &input);
		
		if(input == -1)
		{
			break;
		}

		int isZero = 0;
		// Removed excess Account* declarations and int... this was a weird error
		Account* ptr = findAccount(bank, input);

		if(ptr == NULL)
		{
			printf("\nError: account not found.\n\n");
			continue;
		}
		
		printf("Welcome %s %s.\n", ptr->firstName, ptr->lastName);

		while(isZero == 0)
		{
			// Changed ptr.balance to ptr->balance
			printf("Your balance: $%.2f\n", ptr->balance);
			printOptions();
			int selection;
			scanf("%d", &selection);
			switch(selection)
			{
				case 1:
					withdrawMoney(ptr);
					break;
				case 2:
					depositMoney(ptr);
					break;
				case 3:
					changeInfo(ptr);
					break;
				case -1:
					printf("Successfully logged out.\n");
					isZero = 1;
					break;
				default:
					printf("Invalid selection, try again: \n");		
					printf(">");
			}

			writeBackInfo(argv[1], bank);
		
		}
	}

	
	freeBank(bank);

	printf("Come again soon.\n");

	return 0;
}

Account* findAccount(Account* bank, int login)
{
	int i;
	for(i = 0; i < NUMACCOUNTS; i++)
	{
		if(bank[i].ID == login)
		{
			return &bank[i];
		}
	}

	return NULL;
}

void printOptions()
{
	printf("--------Main Menu--------\n");
	printf("1: Withdrawl\n");
	printf("2: Deposit\n");
	printf("3: Change name on account\n");
	printf("-1: logout\n");
	printf(">");
}

void withdrawMoney(Account* account)
{
	printf("How much money are you taking out (-1: Back to main menu)?\n");
	printf(">");
	float amount = 0.0;
	scanf("%f", &amount);

	while(1)
	{
		// Changed || to &&
		if(amount <= 0 && amount != -1)
		{
			printf("Error: invalid amount entered.\n");
		}
		else if(amount > account->balance - .01)
		{
			printf("Error: account must have at least $0.01 in it.\n");
		}
		else
		{
			break;
		}
		printf("Please try again: \n");
		printf(">");
		// Passed scanf the address
		scanf("%f", &amount);
	}

	if(amount == -1)
	{
		return;
	}
	// Changed addition to subtraction
	account->balance -= amount;
	printf("Subtracting $%.2f from your account. Your balance is now $%.2f.\n", amount, account->balance);
}

void depositMoney(Account* account)
{
	printf("How much money are you depositing (-1: Back to main menu)?\n");
	printf(">");
	float amount;
	scanf("%f", &amount);
	// Changed || to &&
	while(amount <= 0 && amount != -1)
	{
		printf("Error: invalid amount.\n");
		printf("Please try again:\n");
		printf(">");
		scanf("%f", &amount);
	}
	// Comparison operator not assignment
	if(amount == -1)
	{
		return;
	}

	account->balance += amount;
	printf("Adding $%.2f to your account. Your balance is now $%.2f.\n", amount, account->balance);
}

void changeInfo(Account* account)
{
	printf("What would you like to change?\n");
	printf("1: First name\n");
	printf("2: Last name\n");
	printf("-1: Back to main menu\n");

	printf(">");
	int selection;
	scanf("%d", &selection);
	
	while(selection != 1 && selection != 2 && selection != -1)
	{
		printf("Invalid selection, choose again: \n");
		printf(">");
		scanf("%d", &selection);
	}

	switch(selection)
	{
		case 1:
			printf("Put in new name: \n");
			printf(">");
			scanf("%s", account->firstName);
			// Added break statement
			break;
		case 2:
			printf("Put in new name: \n");
			printf(">");
			scanf("%s", account->lastName);
			break;
		case -1:
			return;
	}

	printf("Name has been changed.\n");
}

// Changed capitalization of function name
void writeBackInfo(char* filename, Account* bank)
{
	FILE* fp = fopen(filename, "w");
	int i;
	for(i = 0; i < NUMACCOUNTS; i++)
	{
		fprintf(fp, "%s\n", bank[i].firstName);
		fprintf(fp, "%s\n", bank[i].lastName);
		fprintf(fp, "%d %.2f\n", bank[i].ID, bank[i].balance);
	}
	fclose(fp);
}

Account* loadBank(char* filename)
{
	// Changed sizeof from int to account
	Account* bank = (Account*)malloc(sizeof(Account)*NUMACCOUNTS); 

	FILE* fp = fopen(filename, "r");
	int i;
	// Changed <= to <
	for(i = 0; i < NUMACCOUNTS; i++)
	{
		bank[i].firstName = malloc(sizeof(char)*MAXNAMELENGTH);
		bank[i].lastName = malloc(sizeof(char)*MAXNAMELENGTH);
		fscanf(fp, "%s", bank[i].firstName);
		fscanf(fp, "%s", bank[i].lastName);
		fscanf(fp, "%d %f", &bank[i].ID, &bank[i].balance);
	
	}

	fclose(fp);

	return bank;
}


void freeBank(Account* bank)
{
	int i;
	for(i = 0; i < NUMACCOUNTS; i++)
	{
		free(bank[i].firstName);
		free(bank[i].lastName);
	}

	free(bank);
}


