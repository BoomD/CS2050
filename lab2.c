// Alexander Gompper
// CS2050 SS16
// Lab 2

#include <stdio.h>
#include <stdlib.h>

typedef struct t_ {
	int ID;
	int ticketsSold;
	int totalTickets;
	float ticketPrice;
	int numDays;
} Record;

Record* readRecords(char* filename);
Record bestPercentageSold(Record* records);
Record bestDailyProfit(Record* records);

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("\nInsufficient arguments.");
		return -1;
	}
	Record* records = readRecords(argv[1]);

	// Quick test to make sure the array gets stuff in it
	/*
	if(records != NULL) {
		printf("\nRead input file successfully.");
	}
	*/

	// some unit testing to make sure we're getting some records read from the file
	/*
	int i;
	for(i = 0; i < 10; i++) {
		printf("\n%d %d %d %.2f %d",
			records[i].ID,
			records[i].ticketsSold,
			records[i].totalTickets,
			records[i].ticketPrice,
			records[i].numDays);
	}
	*/

	// best stuff
	Record bestPercent = bestPercentageSold(records);
	printf("\nID of record w/ best percentage sold: %d", bestPercent.ID);
	Record bestProfit = bestDailyProfit(records);
	printf("\nID of record w/ best daily profit: %d", bestProfit.ID);
	
	free(records);
	return 0;
}

Record* readRecords(char* filename) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("\nUnable to open input file %s .", filename);
		return NULL;
	}
	
	// count the number of lines in the file, check if its 125
	int lines = 0;
	char ch = 0;
	while(!feof(fp)) {
		ch = fgetc(fp);
		if(ch == '\n') {
			lines++;
		}
	}
	rewind(fp);
	if(lines !=  125) {
		printf("\nInput file does not contain 125 records. %d", lines);
	}

	// malloc some space for the records
	Record* records = malloc(sizeof(Record)*lines);
	
	// populate the records array with data from input file	
	int i;
	for(i = 0; i < lines; i++) {
		fscanf(fp, "%d %d %d %f %d",
			&records[i].ID,
			&records[i].ticketsSold,
			&records[i].totalTickets,
			&records[i].ticketPrice,
			&records[i].numDays);
	}
	fclose(fp);

	return records;
}

Record bestPercentageSold(Record* records) {
	float bestPercent = 0.0;
	int bestID = 0;

	int i;
	for(i = 0; i < 125; i++) {
		// pretty liberal with the parenthesis here to ensure proper casting
		if( ( ((double)records[i].ticketsSold)/((double)records[i].totalTickets) ) > bestPercent) {
			bestID = records[i].ID;
			bestPercent = (double)records[i].ticketsSold / (double)records[i].totalTickets;
		}
	}
	return records[bestID];
}

Record bestDailyProfit(Record* records) {
	float bestProfit = 0.0;
	int bestID = 0;

	int i;
	for(i = 0; i < 125; i++) {
		if(  ( (((double)records[i].ticketPrice)*((double)records[i].ticketsSold))/records[i].numDays) > bestProfit) {
			bestID = records[i].ID;
			bestProfit = ((double)records[i].ticketPrice* (double)records[i].ticketsSold)/records[i].numDays;
		}
	}
	return records[bestID];
}


