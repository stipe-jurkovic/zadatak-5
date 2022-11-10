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


Position PrevEl(Position P, float F);
Position EndOfList(Position P);

int NewElAfter(Position P, float F);
int NewElEnd(Position P, float F);
int PrintEl(Position P);
int PrintList(Position P);

int ReadFromFile(char nameOfFile[MAX_FILE_NAME], Position Pozn, int line);

int Add(Position P);
int Sub(Position P);
int DelNextEl(Position P);
int DelAll(Position P);

int main() {




}

Position EndOfList(Position P) {

	while (P->Next != NULL) {
		P = P->Next;
	}
	return P;
}
Position PrevEl(Position P, float F) {

	while (P->Next != NULL && P->Next->f != F)
	{
		P = P->Next;
	}
	return P;
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
		}
		printf("\n");
	}
	return PROGRAM_SUCCESS;
}

int ReadFromFile(char nameOfFile[MAX_FILE_NAME], Position Poz, int line)
{
	FILE* file = NULL;
	int  n, r, i;
	file = fopen(nameOfFile, "r");
	char buffer[MAX_LINE] = { 0 };
	char* P = buffer;
	char c = '';
	float F = 0.0;
	n = 0; r = 0; i = 0;

	if (file == NULL) {
		printf("\n\nNemoguce otvoriti datoteku.\n\n");
		return PROGRAM_FAILED;
	}
	while (i < line) {
		fgets(buffer, MAX_LINE, file);
		i++;
	}

	while (strlen(buffer) > 0) {

		r = sscanf(P, " %f %n", &F, &n);
		if (r != 1) {
			sscanf(P, " %c %n", &F, &n);
			switch (r)
			{
			default:
				break;
			}
			
			
			
			
			break; 
		}
		P += n * sizeof(char);
		NewElAfter(Poz, F);
	}

	//printf("\n\nKraj liste.\n\n");
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
	printf("Deleted list! Deleted %i entries.\n", i);
	return PROGRAM_SUCCESS;
}