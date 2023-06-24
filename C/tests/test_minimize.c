#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    Automata AFND = read_automaton_from_dot("AFND_TP2.dot");
    Automata AFD = to_AFD(AFND);

    printf("--- Test Minimize: ---\n");
    Automata min = minimize(AFD);

    printf("Minimize: \n");
    print_automaton(min);

    write_automaton_to_dot(min, "minimize.dot");
    printf("Test Minimize Passed\n");

    return 1;
}
