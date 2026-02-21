# PhoneBook Manager

A simple command-line phone book application written in C that allows you to manage contacts with first name, last name, and phone number.

## Features

- Add new contacts
- Delete existing contacts
- Search contacts by name
- Search contacts by phone number
- Update a contact's phone number
- Print all contacts

## Data Structure

Contacts are stored in an array of 26 singly linked lists, one per letter of the alphabet, indexed by the first letter of the contact's first name. This allows for efficient lookups by name.

## Getting Started

### Prerequisites

- A C compiler (e.g. `gcc`)

### Compilation

```bash
gcc -o phonebook PhoneBook.c
```

### Running

```bash
./phonebook
```

## Usage

On launch, the program displays a menu with the following options:

```
1. Add a new contact        — Enter first name, last name, and phone number
2. Delete a contact         — Enter a name and confirm deletion
3. Find a contact by number — Enter a phone number to look up
4. Find a contact by name   — Enter a full name to look up
5. Update phone number      — Enter a name and provide a new phone number
6. Print phone book         — Display all contacts
7. Exit                     — Free all memory and quit
```

### Constraints

- No two contacts can share the same full name.
- No two contacts can share the same phone number.
- Names and numbers are capped at `MAX_STRING` (11 characters, i.e. 10 usable + null terminator); full names at `MAX_FULLNAME` (22 characters: `2 * (MAX_STRING - 1) + 2`).
- The phonebook array has exactly `LETTER_COUNT` (26) buckets, one per letter of the alphabet.

## Project Structure

```
├── PhoneBook.h   # Header file: struct definition, constants, and all declarations
└── PhoneBook.c   # Implementation of all phonebook operations and main()
```

## Constants (from `PhoneBook.h`)

| Constant | Value | Description |
|---|---|---|
| `MAX_STRING` | 11 | Max buffer size for first name, last name, or phone number (10 chars + `\0`) |
| `MAX_FULLNAME` | 22 | Max buffer size for a full name (`2 * (MAX_STRING - 1) + 2`) |
| `LETTER_COUNT` | 26 | Number of linked list buckets (one per alphabet letter) |

## Key Functions

| Function | Description |
|---|---|
| `addContact` | Prompts the user and adds a new contact |
| `deleteContact` | Prompts the user and removes a contact |
| `FindByName` | Searches for a contact by full name |
| `FindByNumber` | Searches for a contact by phone number |
| `UpdateNumber` | Updates the phone number for an existing contact |
| `printBook` | Prints all contacts in alphabetical bucket order |
| `freeAll` | Frees all allocated memory on exit |
