#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf(" -- Test TP2 -- \n");

    Automata AFND = read_automaton_from_dot("AFND_TP2.dot");
    Automata ANFD_2 = read_automaton_from_dot("AFND_TP2.dot");

    printf("Kleene: \n");
    Automata k = kleene_clousure(AFND);
    Automata k2 = kleene_clousure(ANFD_2);

    printf("Union: \n");
    Automata u = compose(k, k2);

    printf("Minimize: \n");
    Automata min = minimize(to_AFD(u));
    write_automaton_to_dot(min, "minimize.dot");

    printf(" -- Test TP2 passed -- \n");
    return 1;
}