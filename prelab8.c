#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//You want the age to be greater than the floor
//but less than the ceiling for it to be a match
#define TARGETCEILING 100
#define TARGETFLOOR 80

//Match this year
#define TARGETYEAR 2005

int inRange(char* string);
int inYear(char* string);

int main(void)
{
	//Technically an okay way to initialize strings, but is not 
	//good practice unless you have predetermined strings like here. 
	char a[] = "NAME:John | AGE:83 | DATE:12/13/2014";
	char b[] = "NAME:Sebastion | AGE:4 | DATE:8/2/2005";
	char c[] = "NAME:Steven | AGE:81 | DATE:9/9/2010";
	char d[] = "NAME:Bob | AGE:99 | DATE:3/14/2005";

	//This is me being fancy.
	char* ptr[4]; 
	ptr[0] = a;
	ptr[1] = b;
	ptr[2] = c;
	ptr[3] = d;

	//I am continuing to be fancy.
	int i;
	for(i = 0; i < 4; i++)
	{

		//Look at the output to make sure you are doing things right. 
		//If the output matches what you know to be the correct output,
		//then you're done. 
		printf("String %d ", i+1);
		inRange(ptr[i]) == 1 ? printf("has age.\n") : printf("does not have age.\n");
		printf("String %d ", i+1);
		inYear(ptr[i]) == 1 ? printf("has year.\n") : printf("does not have year.\n");

		printf("\n");
	}

	//For the ones who want more, you can test for strings that 
	//don't match the pattern. They should be denoted as bugs in the data.
	//char e[] = "NAME:joe DATE: 2/2/2014 AGE:30"
	//char f[] = "NAMEasdfyewjrfyokjnxcbvuigerdgf"
	//char g[] = ""
	//char h[] = "NAME:34 DATE:AGE joe:30"

	return 0;
}

//For the following two functinons, test to see if the string 
//contains target values based on the defines at the top of this program.
//You are welcome to use any method you wish (don't shortcut it though).
//There are infinite ways to do this, some messy, some not so messy.

//Even though I say not to shortcut it, you should abuse the fact that
//you know the patterns in the string. That is not shortcutting. For our
//purposes, you can assume there are no outliers to the patterns 
//(but you can try to account for that).


//This function is for the age value in the string.  
//Return the following:
//	1 if the string does have an age in the target range
//	0 if it does not. 
int inRange(char* string)
{
    // the characters to separate our tokens
    char* delim = " |:";
    
    // set up the token pointer, this gets advanced every time we call
    // strtok(). Make a copy of our string so that strtok() doesn't destroy it
    char* stringcpy = malloc(sizeof(char)*strlen(string));
    strcpy(stringcpy, string);
    char* token = strtok(stringcpy, delim);
    
    // iterator
    int i = 0;
    
    int age = 0;
    int ceiling = TARGETCEILING;
    int floor = TARGETFLOOR;
    
    while(token != NULL) {
        // we need to check our 3rd token
        if(i == 3) {
            age = atoi(token);
            if(age <= ceiling && age >= floor){
                free(stringcpy);
                return 1;
            }
        }
        token = strtok(NULL, delim);
        i++;
    }
    free(stringcpy);
	return 0;
}

//This is for the year in the date. 
//Return the following:
//	1 if the string does have the date in the target year
//	0 if it does not. 
int inYear(char* string)
{
    char* delim = " |:/";
    char* stringcpy = malloc(sizeof(char)*strlen(string));
    strcpy(stringcpy, string);
    char* token = strtok(stringcpy, delim);
    
    int year = 0;
    int i = 0;
    int target = TARGETYEAR;
    
    while(token != NULL) {
        // we need to check our 3rd token
        if(i == 7) {
            year = atoi(token);
            if(year == target){
                free(stringcpy);
                return 1;
            }
        }
        token = strtok(NULL, delim);
        i++;
    }
    free(stringcpy);
	return 0;
}
