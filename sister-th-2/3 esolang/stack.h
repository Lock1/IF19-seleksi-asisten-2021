#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 2048
typedef struct {
    char stack[STACK_SIZE];
    int top_ptr;
} Stack;

void push(Stack *st, char val) {
    if (st->top_ptr >= STACK_SIZE) {
        printf("\nError stack overflow\n");
        exit(1);
    }
    st->stack[st->top_ptr++] = val;
}

char pop(Stack *st) {
    if (st->top_ptr <= 0) {
        printf("\nError stack out of bound\n");
        exit(1);
    }
    return st->stack[--st->top_ptr];
}

char peek(Stack *st) {
    if (st->top_ptr <= 0) {
        printf("\nError stack out of bound\n");
        exit(1);
    }
    return st->stack[st->top_ptr - 1];
}
