/* Std includes, u know the drill */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Consts */
#define MAX_LIMIT 60

/* functions */
void menu();
void createEntry();
void readEntries();
void updateEntry();
void deleteEntry();

/* vars */
char option;
char *filename = "database.txt";
char new_entry[MAX_LIMIT];

/* Start the main menu */
void menu(){
    printf("Press (c) to create\n");
    printf("Press (r) to read\n");
    printf("Press (u) to update\n");
    printf("Press (d) to delete\n");

    /* Get user option */
    printf("Option:");
    scanf(" %c", &option); // Added space before %c to consume any leftover newline character

    /* Validation */
    switch (option){

        case 'c':
            createEntry();
            break;

        case 'r':
            readEntries();
            break;

        case 'u':
            updateEntry();
            break;

        case 'd':
            deleteEntry();
            break;

        default:
            printf("Bro, u typed something wrong i did not understand\n");

    }
}

void createEntry() {
    /* Create some entry on the db */
    printf("Type some shit as a new entry:");

    /* File config ma man */
    FILE *fp = fopen(filename, "a"); // Changed to "a" to append to the file

    if (fp == NULL) {
        printf("Error opening the file %s", filename);
        return;
    }

    /* Get the fucking string */
    scanf(" %[^\n]", new_entry); // Changed to read a line of input
    fprintf(fp, "%s\r\n", new_entry);

    printf("Entry added on the db\n");
    fclose(fp); /*close de db */
}

void readEntries() {
    /* Read entries from the db */
    char buffer[MAX_LIMIT];
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening the file %s", filename);
        return;
    }

    printf("Entries in the db:\n");
    while (fgets(buffer, MAX_LIMIT, fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
}

void updateEntry() {
    /* Update an entry in the db */
    char buffer[MAX_LIMIT];
    char updated_entry[MAX_LIMIT];
    char temp_filename[] = "temp.txt";
    int found = 0;

    printf("Type the entry to update:");
    scanf(" %[^\n]", new_entry);

    FILE *fp = fopen(filename, "r");
    FILE *temp_fp = fopen(temp_filename, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening the file\n");
        return;
    }

    while (fgets(buffer, MAX_LIMIT, fp) != NULL) {
        if (strstr(buffer, new_entry) != NULL) {
            found = 1;
            printf("Type the updated entry:");
            scanf(" %[^\n]", updated_entry);
            fprintf(temp_fp, "%s\r\n", updated_entry);
        } else {
            fprintf(temp_fp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(filename);
        rename(temp_filename, filename);
        printf("Entry updated in the db\n");
    } else {
        printf("Entry not found in the db\n");
        remove(temp_filename);
    }
}

void deleteEntry() {
    /* Delete an entry from the db */
    char buffer[MAX_LIMIT];
    char temp_filename[] = "temp.txt";
    int found = 0;

    printf("Type the entry to delete:");
    scanf(" %[^\n]", new_entry);

    FILE *fp = fopen(filename, "r");
    FILE *temp_fp = fopen(temp_filename, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening the file\n");
        return;
    }

    while (fgets(buffer, MAX_LIMIT, fp) != NULL) {
        if (strstr(buffer, new_entry) != NULL) {
            found = 1;
        } else {
            fprintf(temp_fp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(filename);
        rename(temp_filename, filename);
        printf("Entry deleted from the db\n");
    } else {
        printf("Entry not found in the db\n");
        remove(temp_filename);
    }
}

/* Std func, where shit happens */
int main(){

    menu();
    return (0);
}
