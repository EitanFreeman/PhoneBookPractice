#include "PhoneBook.h"

//Let H functions denote helper functions

int GetFirstLetterNumber(char *arr){
    char firstLetter = toupper(arr[0]);
    return (int)firstLetter - (int)'A';
}

Contact *FindByNameH(Contact* phonebook[LETTER_COUNT], char name[MAX_STRING]){
    int fstLetterNum = GetFirstLetterNumber(name);
    Contact *cur = phonebook[fstLetterNum];
    while(cur){
        char fullname[MAX_FULLNAME];
        GetFullName(cur->firstName, cur->lastName, fullname);
        if(!strcmp(name, fullname)){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Contact *FindByNumberH(Contact* phonebook[LETTER_COUNT], char number[MAX_STRING]){
    for(int i = 0; i < LETTER_COUNT; i++){
        Contact *cur = phonebook[i];
        while(cur){
            if (!strcmp(cur->PhoneNum, number)){
                return cur;
            }
            cur = cur->next;
        }
    }
    return NULL;
}

bool addContactH(Contact* phonebook[LETTER_COUNT], char fullname[MAX_STRING], char number[MAX_STRING]){
    Contact *NewContact = (Contact *)malloc(sizeof(Contact));
    if (!NewContact){
        return false;
    }
    NewContact->firstName = (char *)malloc(MAX_STRING * sizeof(char));
    if (!NewContact->firstName){
        free(NewContact);
        return false;
    }
    NewContact->lastName = (char *)malloc(MAX_STRING * sizeof(char));
    if (!NewContact->lastName){
        free(NewContact->firstName);
        free(NewContact);
        return false;
    }
    NewContact->PhoneNum = (char *)malloc(MAX_STRING * sizeof(char));
    if (!NewContact->PhoneNum){
        free(NewContact->firstName);
        free(NewContact->lastName);
        free(NewContact);
        return false;
    }

    char buffer[MAX_FULLNAME];
    strcpy(buffer, fullname);
    strcpy(NewContact->firstName, strtok(buffer, " "));
    strcpy(NewContact->lastName, strtok(NULL, " "));
    strcpy(NewContact->PhoneNum, number);

    int fstLetterNum = GetFirstLetterNumber(fullname);
    Contact *temp = phonebook[fstLetterNum];
    phonebook[fstLetterNum] = NewContact;
    NewContact->next = temp;
    return true;
}

void addContact(Contact* phonebook[LETTER_COUNT]){
    printf("Enter a contact details (<first name> <last name> <phone number>):");
    char firstName[MAX_STRING];
    char lastName[MAX_STRING];
    char number[MAX_STRING];
    scanf("%s %s %s", firstName, lastName, number);

    char fullName[MAX_FULLNAME];
    GetFullName(firstName, lastName, fullName);

    if (FindByNameH(phonebook, fullName)){
        printf("The addition of the contact has failed, since the contact %s already exists!\n", fullName);
        return;
    }
    if (FindByNumberH(phonebook, number)){
        printf("The addition of the contact has failed, since the phone number %s already exists!\n", number);
        return;
    }
    if (!addContactH(phonebook, fullName, number)){
        printf("The addition of the contact has failed!\n");
        return;
    }
    printf("The contact has been added successfully!\n");
}


void freeContact(Contact * Contact){
    free(Contact->lastName);
    free(Contact->firstName);
    free(Contact->PhoneNum);
    free(Contact);
}

bool deleteContactH(Contact* phonebook[LETTER_COUNT], char fullname[MAX_STRING]){
    Contact *ContactToDelete = FindByNameH(phonebook, fullname);
    if (!ContactToDelete){
        return false;
    }
    int fstLetterNum = GetFirstLetterNumber(fullname);
    if (!strcmp(phonebook[fstLetterNum]->PhoneNum, ContactToDelete->PhoneNum )){
        phonebook[fstLetterNum] = ContactToDelete->next;
    } else{
        Contact *cur = phonebook[fstLetterNum];
        while(cur->next){
            if(!strcmp(cur->next->PhoneNum, ContactToDelete->PhoneNum)){
                break;
            }
            cur = cur->next;
        }
        cur->next = ContactToDelete->next;
    }
    freeContact(ContactToDelete);
    return true;
}


void deleteContact(Contact* phonebook[LETTER_COUNT]){
    printf("Enter a contact name (<first name> <last name>):");
    char firstName[MAX_STRING];
    char lastName[MAX_STRING];
    scanf("%s %s", firstName, lastName);

    printf("Are you sure? (y/n)");
    char auth;
    scanf(" %c", &auth);
    if(auth != 'y'){
        printf("The deletion of the contact has been canceled.\n");
        return;
    }

    char fullName[MAX_FULLNAME];
    GetFullName(firstName, lastName, fullName);

    if (!deleteContactH(phonebook, fullName)){
        printf("Contact %s doesn't exist\n", fullName);
        return;
    }
    printf("The contact has been deleted successfully!\n");
}

void FindByName(Contact* phonebook[LETTER_COUNT]){
    printf("Enter a contact name (<first name> <last name>):");
    char firstName[MAX_STRING];
    char lastName[MAX_STRING];
    scanf("%s %s", firstName, lastName);

    char fullName[MAX_FULLNAME];
    GetFullName(firstName, lastName, fullName);

    Contact *ContactFound = FindByNameH(phonebook, fullName);
    if(ContactFound){
        printf("The following contact was found: %s %s %s\n", ContactFound->firstName, ContactFound->lastName, ContactFound->PhoneNum);
    } else{
        printf("No contact with a name %s was found in the phone book\n", fullName);
    }
}

void FindByNumber(Contact* phonebook[LETTER_COUNT]){
    printf("Enter a phone number:");
    char number[MAX_STRING];
    scanf("%s", number);

    Contact *ContactFound = FindByNumberH(phonebook, number);
    if(ContactFound){
        printf("The following contact was found: %s %s %s\n", ContactFound->firstName, ContactFound->lastName, ContactFound->PhoneNum);
    } else{
        printf("No contact with a phone number %s was found in the phone book\n", number);
    }
}

void UpdateNumber(Contact* phonebook[LETTER_COUNT]){
    printf("Enter a contact name (<first name> <last name>):");
    char firstName[MAX_STRING];
    char lastName[MAX_STRING];
    scanf("%s %s", firstName, lastName);

    char fullName[MAX_FULLNAME];
    GetFullName(firstName, lastName, fullName);

    printf("Enter the new phone number:");
    char number[MAX_STRING];
    scanf("%s", number);

    if (FindByNumberH(phonebook, number)){
        printf("The update of the contact has failed, since the phone number %s already exists!\n", number);
        return;
    }

    Contact *ContactFound = FindByNameH(phonebook, fullName);
    if(ContactFound){
        printf("The contact has been updated successfully!\n");
        strcpy(ContactFound->PhoneNum, number);
    } else{
        printf("No contact with a name %s was found in the phone book\n", fullName);
        return;
    }
    
}

void printBook(Contact* phonebook[LETTER_COUNT]){
    for(int i = 0; i < LETTER_COUNT; i++){
        Contact *cur = phonebook[i];
        while(cur){
            printf("%s %s %s\n", cur->firstName, cur->lastName, cur->PhoneNum);
            cur = cur->next;
        }
    }
}

void freeAll(Contact* phonebook[LETTER_COUNT]){
    Contact *temp;
    for(int i = 0; i < LETTER_COUNT; i++){
        Contact *cur = phonebook[i];
        while(cur){
            temp = cur->next;
            freeContact(cur);
            cur = temp;
        }
    }
    printf("Bye!");
}

void GetFullName(char *firstName, char *lastName, char *fullName){
    strcpy(fullName, firstName);
    fullName[strlen(firstName)] = ' ';
    fullName[strlen(firstName) + 1] = '\0';
    strcat(fullName, lastName);
}

void printOptions(){
    printf("Welcome to the phone book manager\n");
    printf("Choose an option:\n");
    printf("1. Add a new contact\n");
    printf("2. Delete a contact\n");
    printf("3. Find a contact by number\n");
    printf("4. Find a contact by name\n");
    printf("5. Update phone number for contact\n");
    printf("6. Print phone book\n");
    printf("7. Exit\n");
}

void caseToFunction(int choice, bool *cont1, bool *cont2, Contact* phonebook[LETTER_COUNT]){
    *cont2 = false;
    switch (choice){
        case 1:
            addContact(phonebook);
            break;
        case 2:
            deleteContact(phonebook);
            break;
        case 3:
            FindByNumber(phonebook);
            break;
        case 4:
            FindByName(phonebook);
            break;
        case 5:
            UpdateNumber(phonebook);
            break;
        case 6:
            printBook(phonebook);
            break;
        case 7:
            *cont1 = false;
            freeAll(phonebook);
            break;
        default:
            *cont2 = true;
            printf("Invalid choice try again:\n");
            break;
    }

}

int main(){
    bool cont1 = 1;
    bool cont2 = 1;
    int choice;
    Contact* phonebook[LETTER_COUNT] = {0};
    while(cont1){
        printOptions();
        while(cont2){
            scanf("%d", &choice);
            caseToFunction(choice, &cont1, &cont2, phonebook);
        }
        cont2 = true;
    }
    return 0;
}