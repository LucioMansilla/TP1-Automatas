#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    printf("\n--- Test STRING BELONGS ---\n");

    List *k = create_from((int[]){0, 1, 2}, 3);

    Transition transitions[] = {
        create_transition(0, ord('a'), create_from((int[]){1, 2}, 2)),
        create_transition(0, ord('_'), create_from((int[]){1}, 1)),
        create_transition(1, ord('b'), create_from((int[]){2}, 1)),
        create_transition(2, ord('a'), create_from((int[]){2}, 1)),
        create_transition(2, ord('b'), create_from((int[]){2}, 1)),
        {-1, -1, NULL} // sentinel element
    };

    List **delta = get_delta(transitions, 4);

    Automata a = create_automaton(k, create_from((int[]){0, 1}, 2), delta, 0, create_from((int[]){2}, 1));
    print_automaton(a);
    char test_cases[3][6] = {"ab", "abbbb", "ababab"};

    int result = 1;
    for (int i = 0; i < 3; i++) {
        if (belongs(a, test_cases[i])) {
            printf("Test case %s passed\n", test_cases[i]);
            fflush(stdout);

        } else {
            printf("Test case %s failed\n", test_cases[i]);
            result = 0;
        }
    }

    if (result) {
        printf("\n--- All string belongs tests cases passed ---\n");
        return 1;
    } else {
        printf("\n--- Some string belongs tests cases failed ---\n");
        return 0;
    }
}