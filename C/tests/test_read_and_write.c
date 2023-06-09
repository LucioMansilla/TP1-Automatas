#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("--- Test Read and Write ---\n");
    Automata a = read_automaton_from_dot("AFND.dot");
    print_automaton(a);

    write_automaton_to_dot(a, "testWriteAFND.dot");

    FILE *file;
    file = fopen("testWriteAFND.dot", "r");
    if (file == NULL) {
        printf("\n--- Test Read and Write Failed ---\n");
        return 0;
    } else {
        printf("\n--- Test Read and Write Passed ---\n");
        return 1;
    }

    return 0;
}
