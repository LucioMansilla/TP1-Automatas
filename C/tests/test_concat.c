#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("--- Test Concat ---\n");

    Automata AFND = read_automaton_from_dot("AFND_TP2.dot");
    Automata AFND2 = read_automaton_from_dot("AFND_TP2.dot");

    printf("Concat: \n");
    Automata u = concat(AFND, AFND2);
    write_automaton_to_dot(u, "concat.dot");

    printf("\n--- Test Concat Passed ---\n");
    return 1;
}