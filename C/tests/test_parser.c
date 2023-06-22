#include "../libs/mini_grep.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    char* tests[] = {
        "(a.b)*|(b.c)#", // Expresión regular compleja
        "a.b.c#",        // Concatenación de caracteres
        "(a|b)#",        // Unión de caracteres
        "a*#",           // Cierre de Kleene sobre un solo carácter
        "(a.b)*#",       // Cierre de Kleene sobre una concatenación
        "(a|b)*#",       // Cierre de Kleene sobre una unión
        "(a*|b*)#",      // Cierre de Kleene en ambos lados de una unión
        "((a.b)|c)#",    // Agrupación con paréntesis
        "(a|b.c)#",      // Concatenación y unión juntas
        "(a.b|c)#",      // Concatenación y unión juntas en otro orden
    };
    int numTests = sizeof(tests) / sizeof(char*);

    for (int i = 0; i < numTests; i++) {
        printf("Test %d\n", i + 1);
        char * input = tests[i];
        Automata a = parser(input);
        printf("\n");
    }
    printf("%d tests passed\n", numTests);
    return 0;
}
