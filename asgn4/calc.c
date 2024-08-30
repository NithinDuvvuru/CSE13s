#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "mh"
#define M_PI    3.14159265358979323846

int main(int argc, char **argv) {
    int opt;
    bool libm = false;
    //checking for command line argument
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'm': libm = true; break;
        case 'h': printf(USAGE, "calc"); break;
        default: fprintf(stderr, "invalid arguments\n"); return 1;
        }
    }
    //initalizing buffer and making two strings containing all of calculators operators
    int size = 1024;
    char expr[size];
    char *binary = "+-*/%";
    char *unary = "sctar";
    bool error = false;
    fprintf(stderr, "> ");
    //parsing through input
    while (fgets(expr, size, stdin) != NULL) {
        expr[strcspn(expr, "\n")] = '\0';
        if (expr[0] == '\n' && strlen(expr) == 1) {
            break;
        }
        // saveptr is a variable that strtok_r will use to track its state as we
        // call it multiple times
        char *saveptr;
        // you can set error to true to stop trying to parse the rest of the expression
        error = false;
        // strtok_r splits the input string (expr) on any delimiter character in a
        // sequence (for us, only spaces)
        // it stores its own state in saveptr
        // it returns a pointer to the next token, or NULL if we have processed the entire string
        const char *token = strtok_r(expr, " ", &saveptr);
        // loop until we finish parsing the string or we encounter an error
        while (token != NULL && !error) {
            // process token
            double number = -1;
            bool check = parse_double(token, &number);
            // possibly set error to true
            if (check == false && strchr(binary, *token) == NULL && strchr(unary, *token) == NULL) {
                error = true;
                fprintf(stderr, ERROR_BAD_CHAR, *token);
                break;
            }
            // then, at the very end of your loop...
            bool test = true;
            if (strlen(token) > 2 && number == -1) {
                fprintf(stderr, ERROR_BAD_STRING, token);
                error = true;
                break;
            } else if (strchr(binary, *token) != NULL && strlen(token) == 1) {
                test = apply_binary_operator(binary_operators[(int) *token]);
                if (test == false) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    error = true;
                    break;
                }
            } else if (strchr(unary, *token) != NULL) {
                if (libm == false) {
                    test = apply_unary_operator(my_unary_operators[(int) *token]);
                } else {
                    test = apply_unary_operator(libm_unary_operators[(int) *token]);
                }
                if (test == false) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            } else {
                bool stackTest = stack_push(number);
                if (stackTest == false) {
                    fprintf(stderr, ERROR_NO_SPACE, number);
                    error = true;
                }
            }
            if (error == true) {
                break;
            }
            // (note that we pass NULL instead of expr to indicate we are still processing the same string)
            token = strtok_r(NULL, " ", &saveptr);
        }
        if (error != true) {
            stack_print();
            printf("\n");
        }
        stack_clear();
        fprintf(stderr, "> ");
    }
    return 0;
}
