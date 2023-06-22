#include "../libs/mini_grep.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TestPair {
    char *regex;
    char *test_string;
} TestPair;

int main(void) {
    
    TestPair tests[] = {
        {"(a.b)*|(b.c)#", "abab"}, // Expresión regular compleja
        {"a.b.c#", "abc"},         // Concatenación de caracteres
        {"(a|b)#", "a"},           // Unión de caracteres
        {"a*#", "aaaa"},           // Clausura de Kleene sobre un solo carácter
        {"(a.b)*#", "abab"},       // Clausura de Kleene sobre una concatenación
        {"(a|b)*#", "abab"},       // Clausura de Kleene sobre una unión
        {"(a*|b*)#", "aaa"},       // Clausura de Kleene en ambos lados de una unión
        {"((a.b)|c)#", "ab"},      // Agrupación con paréntesis
        {"(a|b.c)#", "bc"},        // Concatenación y unión juntas
        {"(a.b|c)#", "ab"},        // Concatenación y unión juntas en otro orden
    };

    int numTests = sizeof(tests) / sizeof(TestPair);
    int test;
    printf("--- Test Parser ---\n");
    for (test = 0; test < numTests; test++) {
        printf("Test %d\n", test + 1);
        Automata a = parser(tests[test].regex);
        print_automaton(a);
        if (!belongs(a, tests[test].test_string)) break;

        printf("\n");
    }

    if (test == numTests){
        printf("\n--- Test Parser Passed ---\n");
        return 1;
    }
    
        printf("\n--- Test %d Failed ---\n", test);
        return 0;
}
