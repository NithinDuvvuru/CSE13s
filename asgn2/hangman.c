//#include "hangman_helpers.c"
#include "hangman_helpers.h"

#include <stdio.h>

bool checkWinner(char *guessed, char *secret);

void printSecret(char *guessed, char *secret);

void printEliminated(char *guessed, char *secret);

int compareChars(const void *a, const void *b);
int main(int arg, char **input) {
    (void) arg;

    if (arg != 2) {
        printf("wrong number of arguments\nusage: ./hangman <secret word or phrase>\nif the secret "
               "is multiple words, you must quote it\n");
    }

    char guessed[30] = "0";
    char *secret = input[1];
    char guess;
    if (strlen(secret) > 256) {
        printf("the secret phrase is over 256 characters\n");
        return 1;
    }
    bool check = validate_secret(secret);
    if (check == false) {
        return 1;
    }
    int lives = LOSING_MISTAKE;
    while (checkWinner(guessed, secret) == false && lives > 0) {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[LOSING_MISTAKE - lives]);
        printSecret(guessed, secret);
        printEliminated(guessed, secret);
        guess = read_letter();
        while (string_contains_character(guessed, guess) == true
               || is_lowercase_letter(guess) == false) {
            guess = read_letter();
        }
        guessed[strlen(guessed)] = guess;
        if (string_contains_character(secret, guess) == false) {
            lives--;
        }
        qsort(guessed, strlen(guessed), sizeof(char), compareChars);
    }

    printf(CLEAR_SCREEN);
    printf("%s\n\n", arts[LOSING_MISTAKE - lives]);
    printSecret(guessed, secret);
    printEliminated(guessed, secret);

    if (lives == 0) {
        printf("You lose! The secret phrase was: %s\n", secret);
        return 0;
    }

    printf("You win! The secret phrase was: %s\n", secret);

    return 0;
}

void printEliminated(char guessed[], char *secret) {
    printf("Eliminated: ");
    for (int i = 0; i < (int) strlen(guessed); i++) {
        if (string_contains_character(secret, guessed[i]) == false && guessed[i] != '0') {
            printf("%c", guessed[i]);
        }
    }
    printf("\n\n");
}

void printSecret(char *guessed, char *secret) {
    printf("    Phrase: ");
    for (int i = 0; i < (int) strlen(secret); i++) {
        if (string_contains_character(guessed, secret[i]) == false && secret[i] != '-'
            && secret[i] != ' ' && secret[i] != '\'') {
            printf("_");
        } else {
            printf("%c", secret[i]);
        }
    }
    printf("\n");
}

bool checkWinner(char *guessed, char *secret) {
    for (int i = 0; i < (int) strlen(secret); i++) {
        if (string_contains_character(guessed, secret[i]) == false && secret[i] != '-'
            && secret[i] != ' ' && secret[i] != '\'') {
            return false;
        }
    }
    return true;
}

int compareChars(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}
