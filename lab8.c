#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINELENGTH 100

bool isATime(char* string);
bool isADate(char* string);
bool isAPhoneNumber(char* string);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: ./a.out <filename>\n");
		exit(-1);
	}

	FILE* fp = fopen(argv[1], "r");
	if(!fp)
	{
		printf("Could not open %s. Is the file okay?\n", argv[1]);
		exit(-1);
	}

	char* tmp = malloc(sizeof(char)*MAXLINELENGTH);
	while(fgets(tmp, MAXLINELENGTH, fp) != NULL)
	{
//		char* p = tmp;
	//	while(*p != '\n') p++;
	//	*p = '\0';
		if(isATime(tmp))
		{
			printf("%s is a time.\n", tmp);
		}
		if(isADate(tmp))
		{
			printf("%s is a date.\n", tmp);
		}
		if(isAPhoneNumber(tmp))
		{
			printf("%s is a phone number.\n", tmp);
		}
	}

	fclose(fp);
	free(tmp);

	return 0;
}

bool isATime(char* string)
{
	if(string == NULL) {
		return false;
	}
	
	// filter out our a and p also, so we can check for an appending 'm'
	char* delim = ":ap";

	// copy the string so we dont destroy our original
	char* stringcopy = malloc(sizeof(char)*strlen(string));
	strcpy(stringcopy, string);


	char* token = strtok(stringcopy, delim);
	int i = 0; 
	int d = 0;
	int a = 0;

	// check colons, since they're our delim. we only want one
	
	int count = 0;
	for(i = 0; string[i]; i++) {
		count += (string[i] == ':');
	}
	if(count != 1) {
		free(stringcopy);
		return false;
	}

	i = 0;

	// every time should have at least 6 chars. 
	// 1/2 to start, colon, 2 for minutes, then am/pm
	if(strlen(string) < 6) {
		free(stringcopy);
		return false;
	}

	while(token != NULL) {
		d = strlen(token); // get the length of the token

		// first token should be 1-2 digits	
		if(i == 0) {
			if(atoi(token) == 0) {
				free(stringcopy);
				return false;
			}
			if(d < 1 || d > 2) {
				free(stringcopy);
				return false; // only 2 digits
			}
			// now d is the integer of our token, so we can check 1-12
			a = atoi(token);
			if(a < 1 || a > 12) {
				free(stringcopy);
				return false;
			}
		}
		// second token should be 2 digits
		if(i == 1) {
			if(strlen(token) != 2) {
				free(stringcopy);
				return false;
			}

			a = atoi(token);
			if(a < 1 || a > 59) {
				free(stringcopy);
				return false;
			}
		}

		// third token should be an m if time is properly ended
		if(i == 2) {
			if(*token != 'm') {
				free(stringcopy);
				return false;
			}
			// make sure theres just one character (+ terminator) left
			if(strlen(token) != 2) {
				free(stringcopy);
				return false;
			}
		}

		// no fourth token
		if(i >= 3) {
			free(stringcopy);
			return false;
		}


		token = strtok(NULL, delim);
		i++;
	}	
	free(stringcopy);
	return true;
}

bool isADate(char* string)
{
	return false;
}

bool isAPhoneNumber(char* string)
{
	if(string == NULL) {
		return false;
	}

	// dont start with 0
	if(atoi(&string[0]) == 0) {
		return false;
	}
	
	// 12 in length + terminator and dashes
	if(strlen(string) != 13) {
		return false;
	}

	char* stringcopy = malloc(sizeof(char)*strlen(string));
	strcpy(stringcopy, string);
	char* delim = "-";
	char* token = strtok(stringcopy, delim);

	int i = 0;
	while(token != NULL) {
		if(strchr(token, '/') != NULL) {
			free(stringcopy);
			return false;
		}
		// we don't want any 0, and if atoi returns 0 its a char or actually a 0
		if(atoi(token) == 0) {
			free(stringcopy);
			return false;
		}
		// check first 6 numbers are 3 digits long
		if(i == 0 || i == 1) {
			if(strlen(token) != 3) {
				free(stringcopy);
				return false;
			}
		}
		// last 4 digits
		if(i == 2) {
			// 5 because of null terminator
			if(strlen(token) != 5) {
				free(stringcopy);
				return false;
			}
		}
	
		token = strtok(NULL, delim);
		i++;
	}

	free(stringcopy);
	return true;
}

