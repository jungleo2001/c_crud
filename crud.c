/* Std includes, u know the drill */
#include <stdio.h>
#include <stdlib.h>

/* Consts */
#define MAX_LIMIT 60

/* functions */
void menu();

/* vars */
char option;
char *filename = "database.txt";
char new_entry[MAX_LIMIT];

/* Start the main menu */
void menu(){
    printf("Press (c) to create\n");
    printf("Press (r) to remove\n");
    printf("Press (u) to update\n");
    printf("Press (d) to delete\n");

    /* Get user option */
    printf("Option:");
    scanf("%c", &option);

    /* Validation */
    switch (option){

        case 'c':
            /* Create some entry on the db */
            printf("Type some shit as a new entry:");

            /* File config ma man */
            FILE *fp = fopen(filename, "w");

            fgets(new_entry, MAX_LIMIT, stdin);
            fprintf(fp,"%s\n",new_entry);

            printf("Entry added on the db\n");
            fclose(fp); /*close de db */
            break;

        case 'r':
            printf("U choose r\n");
            break;

        case 'u':
            printf("U choose u\n");
            break;

        case 'd':
            printf("U choose d\n");
            break;

        default:
            printf("Bro, u typed something wrong i did not understand\n");

            }
    }

/* Std func, where shit happens */
int main(){

    /* File config ma man */
    FILE *fp = fopen(filename, "w");

    if (fp == NULL){
        printf("Error opening the file %s", filename);
        return -1;

    }
    menu();
    return (0);
}
