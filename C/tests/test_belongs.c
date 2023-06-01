#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  printf("\n--- Test Belongs ---\n");

  List *k = create_from((int[]){0, 1, 2}, 3);

  Transition transitions[] = {
      create_transition(0, 0, create_from((int[]){1, 2}, 2)),
      create_transition(0, 47, create_from((int[]){1}, 1)),
      create_transition(1, 1, create_from((int[]){2}, 1)),
      create_transition(2, 0, create_from((int[]){2}, 1)),
      create_transition(2, 1, create_from((int[]){2}, 1)),
      {-1, -1, NULL} // sentinel element
  };

  List **delta = get_delta(transitions, 4);

  Automata a = create_automaton(k, create_from((int[]){0, 1}, 2), delta, 0,
                              create_from((int[]){2}, 1));
  print_automaton(a);
  char test_cases[3][6] = {"01", "01111", "010101"};

  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (belongs(a, test_cases[i])) {
      printf("Test case %s passed\n", test_cases[i]);
    } else {
      printf("Test case %s failed\n", test_cases[i]);
      result = 0;
    }
  }

  if (result) {
    printf("\n--- All belongs tests cases passed ---\n");
    return 1;
  } else {
    printf("\n--- Some belongs tests cases failed ---\n");
    return 0;
  }
}