#include "../libs/mini_grep.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    struct {
        char *regex;
        char *line;
        bool expected;
    } tests[] = {
        {"a.b*", "ab", true},  {"a.b*", "abb", true},    {"a.b*", "abbb", true},    {"a.b*", "bbb", false},
        {"a.b*", "c", false},  {"(a.b)*", "abab", true}, {"(a.b)*", "babbc", true}, {"(a.b)*", "aba", true},
        {"(a|b)*", "a", true}, {"(a|b)*", "b", true},    {"(a|b)*", "c", true},     {"a*", "aaaa", true},
        {"a*", "b", true},
    };
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int test;

    printf("--- Test Mini-Grep ---\n");
    for (test = 0; test < numTests; test++) {

        printf("Test %d = expr: %s, line: %s, expected: %s \n", test + 1, tests[test].regex, tests[test].line,
               tests[test].expected ? "true" : "false");

        bool result = minigrep(tests[test].regex, tests[test].line);
        if (!(result == tests[test].expected)) {
            printf("Expected: %d\n", tests[test].expected);
            printf("Got: %d\n", result);
            break;
        }

        printf("PASSED\n");
    }

    if (test == numTests) {
        printf("\n--- Test Mini-Grep Passed ---\n");
        return 1;
    }

    printf("\n--- Test %d Failed ---\n", test);
    return 0;
}