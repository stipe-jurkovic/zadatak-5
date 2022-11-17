#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROGRAM_SUCCESS 0
#define PROGRAM_FAILED 1
#define MAX_NAME 500
#define MAX_LASTNAME 500
#define MAX_FILE_NAME 50
#define MAX_LINE 100
#define true 1

typedef struct Cvor* Position;
typedef struct Cvor {

	float f;
	Position Next;

} Cvor;

Position EndOfList(Position P);
int ProgramDescription();
int ProgramEndnote();
int NewElAfter(Position P, float F);
int NewElEnd(Position P, float F);
int PrintEl(Position P);
int PrintList(Position P);

int ProcessFile(char nameOfFile[MAX_FILE_NAME], Position Pozn, int line);

int Add(Position P);
int Sub(Position P);
int Div(Position P);
int Mult(Position P);
int DelNextEl(Position P);
int DelAll(Position P);

int main() {
	Position head;
	char imeDatoteke[MAX_FILE_NAME];
	int s;
	s = 0;
	memset(imeDatoteke, "0", MAX_FILE_NAME);

	ProgramDescription();
	printf("\n Enter filename (in form example.txt): ");
	s=scanf(" %s", &imeDatoteke);
	
	if (s == 0) { return PROGRAM_FAILED; }
	head = malloc(sizeof(Cvor));
	if (head == NULL) {
		printf("Memory allocation fail");
		return PROGRAM_FAILED;
	}
	
	head->f = 0.0;
	head->Next = NULL;
	
	ProcessFile(imeDatoteke, head, 1); 
	
	printf("\n\nResult: ");
	PrintList(head);
	printf("\n");
	
	DelAll(head);
	ProgramEndnote();
	return PROGRAM_SUCCESS;
}

Position EndOfList(Position P) {

	while (P->Next != NULL) {
		P = P->Next;
	}
	return P;
}
int ProgramDescription() {

	printf(" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" \n");
	printf(" This is a program for calculating postfix expression.\n");
	printf(" The values are loaded from a file.\n");
	printf(" \n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n\n");
	return PROGRAM_SUCCESS;
}
int ProgramEndnote() {

	printf("\n\n #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" \n");
	printf(" End of program.\n");
	printf(" \n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n\n");
	return PROGRAM_SUCCESS;
}
int NewElAfter(Position P, float F) {

	Position Q = malloc(sizeof(struct Cvor));

	if (Q == NULL)
	{
		printf("\n\nMemory allocation unsuccessful.\n\n\n");
		return PROGRAM_FAILED;
	}

	Q->f = F;

	Q->Next = P->Next;
	P->Next = Q;

	return PROGRAM_SUCCESS;
}
int NewElEnd(Position P, float F) {
	P = EndOfList(P);
	NewElAfter(P, F);
	printf("\n\nNew element created!\n\n\n");
}
int PrintEl(Position P) {
	//P = P->Next;
	printf("%f ", P->f);
	return PROGRAM_SUCCESS;
}
int PrintList(Position P) {

	P = P->Next;

	if (P == NULL) {

		printf("\nList is empty!!\n");
		return PROGRAM_SUCCESS;
	}
	else {
		while (P != NULL) {
			PrintEl(P);
			P = P->Next;
		}

		printf("\n");
	}
	return PROGRAM_SUCCESS;
}

int ProcessFile(char nameOfFile[MAX_FILE_NAME], Position Poz, int line)
{
	FILE* file = NULL;
	int  n, r, i,x ;
	file = fopen(nameOfFile, "r");
	char buffer[MAX_LINE] = { 0 };
	char* P = buffer;
	char c = ' ';
	float F = 0.0, f=0;
	n = 1; r = 1; i = 0;

	if (file == NULL) {
		printf("\n\nNemoguce otvoriti datoteku.\n\n");
		return PROGRAM_FAILED;
	}
	while (i < line) {
		fgets(buffer, MAX_LINE, file);
		i++;
	}
	while (r!=-1) {


		r = sscanf(P, " %f %n", &F, &n);

		if (r == 1) {
			NewElAfter(Poz, F);
		}
		else if (sscanf(P, " %c %n", &c, &n) == 1)
			{
				switch (c)
				{
				case '+':
					Add(Poz);
					break;
				case '-':
					Sub(Poz);
					break;
				case '*':
					Mult(Poz);
					break;
				case '/':
					Div(Poz);
					break;
				default:
					break;
				}
			}
		P += n * sizeof(char);
	}
	fclose(file);
	return PROGRAM_SUCCESS;
}

int Add(Position P) {

	P->Next->Next->f += P->Next->f;
	DelNextEl(P);
	return PROGRAM_SUCCESS;

}
int Sub(Position P) {

	P->Next->Next->f -= P->Next->f;
	DelNextEl(P);
	return PROGRAM_SUCCESS;

}
int Mult(Position P) {

	P->Next->Next->f *= P->Next->f;
	DelNextEl(P);
	return PROGRAM_SUCCESS;

}
int Div(Position P) {
	
	if (P->Next->f == 0)
	{
		printf("Division by zero is not allowed!!");
		return PROGRAM_FAILED;
	}

	P->Next->Next->f /= P->Next->f;
	DelNextEl(P);
	return PROGRAM_SUCCESS;

}
int DelNextEl(Position P) {

	Position temp = NULL;

	if (P->Next == NULL) {

		printf("\nElement was not found!\n");
		return PROGRAM_FAILED;
	}
	temp = P->Next;
	P->Next = P->Next->Next;

	free(temp);
	//printf("\nDeleted 1 element!\n");
	return PROGRAM_SUCCESS;
}
int DelAll(Position P) {

	int i = 0;
	if (P->Next == NULL)
	{
		printf("List is empty!! Success?\n");
		return PROGRAM_SUCCESS;
	}
	while (P->Next != NULL) {
		DelNextEl(P);
		i++;
	}
	if (i = 1) {
		printf("Deleted list! Deleted %i entry.\n", i);
	}
	else {
		printf("Deleted list! Deleted %i entries.\n", i);
	}
	   
	return PROGRAM_SUCCESS;
}
