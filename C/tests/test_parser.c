#include "../libs/mini_grep.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct test_pair {
    char *regex;
    char **test_strings;
    int num_tests;
} test_pair;

int main(void) {
    test_pair tests[] = {
        {"(a.b)*|b#", (char *[]){"abab", "b", "ab", NULL}, 3},
        {"a.b.c#", (char *[]){"abc", NULL}, 1},
        {"(a|b)#", (char *[]){"a", "b", NULL}, 2},
        {"a*#", (char *[]){"aaaa", "a", "", NULL}, 3},
        {"(a.b)*#", (char *[]){"abab", "ab", NULL}, 2},
        {"(a|b)*#", (char *[]){"abab", "baba", "aaa", "bbbb", NULL}, 4},
        {"(a*|b*)#", (char *[]){"aaa", "bbb", NULL}, 2},
        {"((a.b)|c)#", (char *[]){"ab", "c", NULL}, 2},
        {"(a|b.c)#", (char *[]){"bc", "a", NULL}, 2},
        {"(a.b|c)#", (char *[]){"ab", "c", NULL}, 2},
    };

    int len_tests = sizeof(tests) / sizeof(test_pair);
    int total_num_test = 0;

    for (int i = 0; i < len_tests; i++) {
        char **test_strings = tests[i].test_strings;
        int count = 0;

        while (test_strings[count] != NULL) {
            count++;
        }

        total_num_test += count;
    }
    int count_passed = 0;
    int test = 0;
    printf("--- Test Parser ---\n");
    while (test < len_tests) {
        printf("Test %d\n", test + 1);
        Automata a = parser(tests[test].regex);
        print_automaton(a);

        char **test_strings = tests[test].test_strings;
        int num_tests = tests[test].num_tests;
        int i = 0;
        while (i < num_tests && belongs(a, test_strings[i])) {
            printf("Input: %s\n", test_strings[i]);
            count_passed++;
            i++;
        }

        if (i != num_tests) {
            printf("Failed\n\n");
            break;
        }
        printf("Passed\n\n");

        test++;
    }

    if (count_passed == total_num_test) {
        printf("\n--- Test Parser Passed ---\n");
        return 1;
    }

    printf("\n--- Test %d Failed ---\n", test);
    return 0;
}
