#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	float gpa;
	int creditHoursRemaining;
} Student;

Student* readFile(char* filename);
int closestToGraduate(Student* students);

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("\nInsufficient arguments.");
		return -1;
	}
	
	Student* students = readFile(argv[1]);

	// unit testing to make sure the input file is read correctly
	
	int i;
	printf("\nInput file contents: \n");
	for(i = 0; i < 3; i++) {
		printf("\nID: %d GPA: %.2f Credits Remaining: %d",
			students[i].id,
			students[i].gpa,
			students[i].creditHoursRemaining);
	}

	printf("\nClosest ID to graduate: \n");
	printf("%d", closestToGraduate(students));

	

	return 0;
}

Student* readFile(char* filename) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("\nUnable to open input file");
		exit(1);
	}

	// count lines in file so we can allocate for the array of students
	int lines = 0;
	char ch = 0;
	while(!feof(fp)) {
		ch = fgetc(fp);
		if(ch == '\n') {
			lines++;
		}
	}
	rewind(fp);

	Student* students = malloc(sizeof(Student)*lines);
	
	int i;
	for(i = 0; i < lines; i++) {
		fscanf(fp, "%d %f %d",
			&students[i].id,
			&students[i].gpa,
			&students[i].creditHoursRemaining);
	}
	
	fclose(fp);

	return students;
}

int closestToGraduate(Student* students) {
	int idClosest = students[0].id;
	int minGradHours = students[0].creditHoursRemaining;
	
	int numStudents = 3;
	char ch = 0;
	while(!feof(fp
	
	int i;
	for(i = 0; i < numStudents; i++) {
		if(students[i].creditHoursRemaining < minGradHours) {
			idClosest = students[i].id;
		}	
	}

	return id;
}

