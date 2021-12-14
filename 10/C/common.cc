#include <stdio.h>
#include "common.h"

const int BUF_SIZE = 201;
char buf[BUF_SIZE];
char stack[BUF_SIZE];
char* stack_end;

/* Returns positive value for task 1
    and negative for task 2.  */
long long get_score() {
    scanf("%s", buf);
    stack_end = stack;
    long long res;
    for (char* cur = buf; *cur; ++cur) {
        char c = *cur;
        if (c == '(' || c == '{' || c == '[' || c == '<') {
            *stack_end++ = c;
        } else {
            if (stack_end != stack) {
                char open = stack_end[-1];
                if (open == '(' && c == ')' ||
                    open == '{' && c == '}' ||
                    open == '[' && c == ']' ||
                    open == '<' && c == '>'
                ) {
                    --stack_end;
                } else {
                    goto SYNTAX_ERROR;
                }
            } else {
SYNTAX_ERROR:
                return (c == ')' ? 3 :
                    c == ']' ? 57 :
                    c == '}' ? 1197 :
                    25137);
            }
        }
    }
    res = 0;
    for (--stack_end; stack_end >= stack; --stack_end) {
        char c = *stack_end;
        res = res * 5 + (c == '(' ? 1 :
            c == '[' ? 2 :
            c == '{' ? 3 :
            4);
    }
    return -res;
}
