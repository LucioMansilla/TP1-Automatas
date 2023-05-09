#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test AFND to AFD ---\n");
  List *k = createFrom((int[]){0, 1, 2}, 3);

  Transition transitions[] = {
      createTransition(0, 0, createFrom((int[]){1, 2}, 2)),
      createTransition(0, 26, createFrom((int[]){1}, 1)),
      createTransition(1, 1, createFrom((int[]){2}, 1)),
      {-1, -1, NULL} // Elemento sentinela
  };

  List **delta = getDelta(transitions, 4);

  Automata a = createAutomata(k, createFrom((int[]){0, 1}, 2), delta, 0,
                              createFrom((int[]){2}, 1));
  printf("Original Automata(AFND): \n");
  printAutomata(a);

  printf("Transformed Automata(AFD): \n");
  printAutomata(transformAFNDtoAFD(a));

  printf("\n--- Test AFND to AFD Passed ---\n");
  return 1;
}