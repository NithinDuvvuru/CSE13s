#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return c >= 'a' && c <= 'z' ? true : false;
}

bool validate_secret(const char *secret) {
    for (int i = 0; i < (int) strlen(secret); i++) {
        if (is_lowercase_letter(secret[i]) == false && secret[i] != '\'' && secret[i] != ' '
            && secret[i] != '-') {
            printf("invalid character: '%c'\n", secret[i]);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    for (int i = 0; i < (int) strlen(s); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

char read_letter(void) {
    char ch;

    printf("Guess a letter: ");
    scanf("%c", &ch);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return ch;
}
