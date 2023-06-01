#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test AFND to AFD ---\n");
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
  printf("Original Automata(AFND): \n");
  print_automaton(a);

  printf("Transformed Automata(AFD): \n");
  print_automaton(to_AFD(a));

  printf("\n--- Test AFND to AFD Passed ---\n");
  return 1;
}