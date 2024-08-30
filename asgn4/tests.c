#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    bool check;
    stack_push(1);
    check = stack_push(2);
    //checking functionality of stack_push
    if (check == false || stack_size != 2) {
        fprintf(stderr, "Failed test push\n");
        return 1;
    }

    double item;
    check = stack_peek(&item);
    //checking functionality of stack_peek
    if (item != 2 || check == false) {
        fprintf(stderr, "Failed test peek\n");
        return 1;
    }
    double pop;
    check = stack_pop(&pop);
    //checking functionality of stack_pop
    if (item != 2 || check == false || stack_size != 1) {
        fprintf(stderr, "Failed test pop\n");
        return 1;
    }
    double value = 21;
    //checking functionality of multiply
    if (operator_mul(3, 7) != value) {
        fprintf(stderr, "Failed test mul\n");
        return 1;
    }
    //checking functionality of add
    if (operator_add(20, 1) != value) {
        fprintf(stderr, "Failed test add\n");
        return 1;
    }
    //checking functionality of subtract
    if (operator_sub(24, 3) != value) {
        fprintf(stderr, "Failed test sub\n");
        return 1;
    }
    //checking functionality of division
    if (operator_div(63, 3) != value) {
        fprintf(stderr, "Failed test div\n");
        return 1;
    }
    //checking functionality of sin
    if (Sin(0) != 0) {
        fprintf(stderr, "Failed test Sin\n");
        return 1;
    }
    //checking functionality of cos
    if (Cos(0) != 1) {
        fprintf(stderr, "Failed test Cos\n");
        return 1;
    }
    //checking functionality of tan
    if (Tan(0) != 0) {
        fprintf(stderr, "Failed test Tan\n");
        return 1;
    }
    return 0;
}
