// -- F language instruction --
// Stack operator
// + -> push register to stack
// - -> pop stack and insert to register

// Register operator
// ^ -> increment register
// v -> decrement register

// I/O operator
// o -> getchar(reg)
// * -> putchar(reg)

// Conditional operator
// < -> compare register & top stack, true if register is lower
// > -> True if register is bigger
// = -> True if register equal
// # -> True if register not equal
// T -> Always set _gl_condition = 1
// F -> Always set _gl_condition = 0

// Other operator
// x         -> set register to 0
// { }       -> while (_gl_condition)
// \r \n ' ' -> ignored character
// @         -> Set register = _gl_condition


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define BUFFER_SIZE 8192
#define START_BRACKET '{'
#define END_BRACKET '}'

Stack _gl_stack;

char _gl_int_buffer[8192];
int _gl_int_buf_pt = 0;
char _gl_is_in_loop = 0;
char _gl_lang_reg = 0;
char _gl_condition = 0;


void clear_buffer(char *buf) {
    for (int i = 0; i < BUFFER_SIZE; i++)
        buf[i] = 0;
}

void parse_token(char c) {
    if (c != ' ' && c != '\n' && c != '\r') {
        switch (c) {
            case '+':
                push(&_gl_stack, _gl_lang_reg);
                break;
            case '-':
                _gl_lang_reg = pop(&_gl_stack);
                break;

            case '^':
                _gl_lang_reg++;
                break;
            case 'v':
                _gl_lang_reg--;
                break;

            case 'o':
                _gl_lang_reg = getchar();
                break;
            case '*':
                putchar(_gl_lang_reg);
                break;

            case 'x':
                _gl_lang_reg = 0;
                break;
            case '@':
                _gl_lang_reg = _gl_condition;
                break;

            // Conditional
            case '<':
                _gl_condition = (_gl_lang_reg < peek(&_gl_stack));
                break;
            case '>':
                _gl_condition = (_gl_lang_reg > peek(&_gl_stack));
                break;
            case '=':
                _gl_condition = (_gl_lang_reg == peek(&_gl_stack));
                break;
            case '#':
                _gl_condition = (_gl_lang_reg != peek(&_gl_stack));
                break;
            case 'T':
                _gl_condition = 1;
                break;
            case 'F':
                _gl_condition = 0;
                break;




            case END_BRACKET:
                if (!_gl_condition)
                    _gl_is_in_loop = 0;
                break;

            default:
                printf("Syntax error, unknown token %c\n", c);
                exit(1);
        }
    }
}


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Usage : f <file>\n");
        exit(0);
    }

    FILE *file = fopen(argv[1], "r");
    char c;
    if (file == NULL) {
        printf("File not found!\n");
        exit(1);
    }


    // Executing program
    _gl_stack.top_ptr = 0;
    clear_buffer(_gl_int_buffer);

    while ((c = fgetc(file)) != EOF) {
        if (c != ' ' && c != '\n' && c != '\r') {
            switch (c) {
                case START_BRACKET:
                    if (_gl_stack.top_ptr >= 0) {
                        char is_end_bracket_found = 0;
                        clear_buffer(_gl_int_buffer);
                        _gl_int_buf_pt = 0;

                        while ((c = fgetc(file)) != EOF && !is_end_bracket_found) {
                            if (c != ' ' && c != '\n' && c != '\r') {
                                _gl_int_buffer[_gl_int_buf_pt++] = c;
                                if (c == END_BRACKET)
                                    is_end_bracket_found = 1;
                            }
                        }

                        if (c == EOF && !is_end_bracket_found) {
                            printf("Error, unmatched bracket\n");
                            exit(1);
                        }

                        _gl_is_in_loop = 1;
                        while (_gl_is_in_loop) {
                            for (int i = 0; i < _gl_int_buf_pt; i++)
                                parse_token(_gl_int_buffer[i]);
                        }
                    }
                    else {
                        printf("Stack out of bound error\n");
                        exit(1);
                    }
                    break;

                default:
                    parse_token(c);
            }
        }
    }

    return 0;
}
