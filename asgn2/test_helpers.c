#include "hangman_helpers.c"

int main(void) {
    char *secret = "ABC";

    if (validate_secret(secret) == false) {
        printf("Passed validate secret test 1\n");
    } else {
        printf("Failed validate secret test 1\n");
    }

    secret = "-' lm1";

    if (validate_secret(secret) == false) {
        printf("Passed validate secret test 2\n");
    } else {
        printf("Failed validate secret test 2\n");
    }

    if (is_lowercase_letter('A') == false) {
        printf("Passed is lower case test 1\n");
    } else {
        printf("Failed is lower case test 1\n");
    }

    if (is_lowercase_letter('z') == true) {
        printf("Passed is lower case test 2\n");
    } else {
        printf("Failed is lower case test 2\n");
    }

    if (string_contains_character(secret, 'l') == true) {
        printf("Passed contains character test 1\n");
    } else {
        printf("Failed is lower case test 1\n");
    }

    if (string_contains_character(secret, 'z') == false) {
        printf("Passed contains character test 2\n");
    } else {
        printf("Failed is lower case test 2\n");
    }

    printf("Enter 'a'\n");
    char letter = read_letter();
    if (letter == 'a') {
        printf("Passed read letter test\n");
    } else {
        printf("Failed read letter test\n");
    }

    return 0;
}