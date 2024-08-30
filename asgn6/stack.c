#include "stack.h"

#include <stdlib.h>

typedef struct stack {
    uint32_t *items; // Array to hold the stack's content
    uint32_t top; // Index for the top element in the stack
    uint32_t capacity; // Maximum number of items the stack can hold
} Stack;

Stack *stack_create(uint32_t capacity) {
    // Attempt to allocate memory for a stack
    // Cast it to a stack pointer too!
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    // We need enough memory for <capacity> numbers
    s->items = calloc(s->capacity, sizeof(uint32_t));
    // We created our stack, return it!
    return s;
}

void stack_free(Stack **sp) {
    // sp is a double pointer, so we have to check if it,
    // or the pointer it points to is null.
    if (sp != NULL && *sp != NULL) {
        // Of course, we have to remember to free the
        // memory for the array of items first,
        // as that was also dynamically allocated!
        // If we freed the Stack first then we would
        // not be able to access the array to free it.
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        // Free memory allocated for the stack
        free(*sp);
    }
    if (sp != NULL) {
        // Set the pointer to null! This ensures we dont ever do a double free!
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val) {
    // If the stack is full, return false;
    if (stack_full(s)) {
        return false;
    }
    // Set val
    s->items[s->top] = val;
    // Move the top of the stack
    s->top++;
    return true;
}

// Function to pop an element from the stack
bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *val = s->items[s->top];
    return true;
}

// Function to peek at the top element of the stack without removing it
bool stack_peek(const Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[s->top - 1];
    return true;
}

// Function to check if the stack is empty
bool stack_empty(const Stack *s) {
    return s->top == 0;
}

// Function to check if the stack is full
bool stack_full(const Stack *s) {
    return s->top == s->capacity;
}

// Function to get the number of elements in the stack
uint32_t stack_size(const Stack *s) {
    return s->top;
}

// Function to copy elements from one stack to another
void stack_copy(Stack *dst, const Stack *src) {
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top;
}

// Function to print the stack
void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}
