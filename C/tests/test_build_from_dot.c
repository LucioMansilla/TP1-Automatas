#include <stdio.h>
#include <string.h>

#include "../libs/automata.h"
#include "../libs/linked_list.h"

int main(int argc, char *argv[]) {
    printf("--- Test Build from DOT ---\n");
    Automata a = read_automaton_from_dot("AFND.dot");
    print_automaton(a);

    if (a.k != NULL && a.initial_state == 0 && a.delta != NULL && a.alphabet != NULL && a.final_states != NULL) {
        printf("\n--- Test Build from dot Passed ---\n");
        return 1;
    } else {
        printf("\n--- Test Build from dot Failed ---\n");
        return 0;
    }
}
