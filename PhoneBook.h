#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 11
#define LETTER_COUNT 26
#define MAX_FULLNAME (2 * (MAX_STRING - 1) + 2)

typedef struct Contact{
    char *firstName;
    char *lastName;
    char *PhoneNum;
    struct Contact* next;
} Contact;

void GetFullName(char *firstName, char *lastName, char *fullName);
Contact *FindByNameH(Contact* phonebook[LETTER_COUNT], char name[MAX_STRING]);
Contact *FindByNumberH(Contact* phonebook[LETTER_COUNT], char number[MAX_STRING]);
bool addContactH(Contact* phonebook[LETTER_COUNT], char fullname[MAX_STRING], char number[MAX_STRING]);
void addContact(Contact* phonebook[LETTER_COUNT]);
void freeContact(Contact * Contact);
bool deleteContactH(Contact* phonebook[LETTER_COUNT], char fullname[MAX_STRING]);
void deleteContact(Contact* phonebook[LETTER_COUNT]);
void FindByName(Contact* phonebook[LETTER_COUNT]);
void FindByNumber(Contact* phonebook[LETTER_COUNT]);
void UpdateNumber(Contact* phonebook[LETTER_COUNT]);
void printBook(Contact* phonebook[LETTER_COUNT]);
void freeAll(Contact* phonebook[LETTER_COUNT]);
void GetFullName(char *firstName, char *lastName, char *fullName);
void printOptions();
void caseToFunction(int choice, bool *cont1, bool *cont2, Contact* phonebook[LETTER_COUNT]);
int GetFirstLetterNumber(char *arr);
#endif