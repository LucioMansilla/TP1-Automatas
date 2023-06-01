#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Build ---\n");

  List *k = create_from((int[]){0, 1, 2}, 3);

  Transition transitions[] = {
      create_transition(0, 0, create_from((int[]){1, 2}, 2)),
      create_transition(0, 26, create_from((int[]){1}, 1)),
      create_transition(1, 1, create_from((int[]){2}, 1)),
      {-1, -1, NULL} // Elemento sentinela
  };

  List **delta = get_delta(transitions, 4);

  Automata a = create_automaton(k, create_from((int[]){0, 1}, 2), delta, 0,
                              create_from((int[]){2}, 1));
  if (a.k != NULL && a.initial_state == 0 && a.delta != NULL &&
      a.alphabet != NULL && a.final_states != NULL) {
    printf("Automata: \n");
    print_automaton(a);
    printf("\n--- Test Build Passed ---\n");
    return 1;
  } else {
    printf("\n--- Test Build Failed ---\n");
    return 0;
  }
}